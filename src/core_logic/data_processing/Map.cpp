//
// Created by keanu on 5/22/2024.
//

#include "Map.h"
#include "data_processing/Store.h"
#include "event_management/actors/Drone.h"
#include "event_management/actors/drones/Worker.h"
#include "event_management/actors/objects/Uplink.h"


CoreLogic::DataProcessing::Map::Map(std::string pa_filename)
{

    auto po_mapUnique = DataProcessing::tileson.parse(pa_filename);
    po_map_ = std::move(po_mapUnique);
    auto& map = *po_map_;
    if (map.getStatus() != tson::ParseStatus::OK)
    {
        throw std::runtime_error("Failed to parse map");
    }

    bgColor_.a = 255;
    bgColor_.r = map.getBackgroundColor().r;
    bgColor_.g = map.getBackgroundColor().g;
    bgColor_.b = map.getBackgroundColor().b;


    /**@note: old Layer saving*/
    /*po_layers_ = std::make_shared<std::vector<tson::Layer>>(map.getLayers());
    auto& layers = *po_layers_;*/

    std::vector<tson::Layer> loadedLayers = map.getLayers();
    std::map<int, std::vector<tson::Layer>> tempLayerMap;
    std::map<int, std::vector<tson::Object>> tempObjMap;


    elevationLevels_ = map.getProp("elevation_levels")->getValue<int>();

    /**
     *@note: new Parser automatically adds Layer and Object-Vectors to their respective elevation value within their std::map
     **/
    for (int i = 0; i < elevationLevels_; i++)
    {
        std::vector<tson::Layer> elevationVector = {};
        for (auto &layer: loadedLayers)
        {
            /**
             * @todo: in Tiled: save elevation as int property of each layer or a Map
             **/
            if (layer.getProp("elevation")->getValue<int>() == i)
            {
                elevationVector.push_back(layer);
                if (layer.getType() == tson::LayerType::ObjectGroup)
                {
                    if (tempObjMap.find(i) != tempObjMap.end())
                    {
                        std::vector<tson::Object> insertVector = layer.getObjects();
                        tempObjMap[i].insert(tempObjMap[i].end(), insertVector.begin(), insertVector.end());
                    } else {
                        tempObjMap.insert({i, layer.getObjects()});
                    }
                }
            }
        }
        if(elevationVector.empty()) continue;
        tempLayerMap.insert({i, elevationVector});
    }

    po_layers_ = std::make_shared<std::map<int, std::vector<tson::Layer>>>(tempLayerMap);
    po_objects_ = std::make_shared<std::map<int, std::vector<tson::Object>>>(tempObjMap);
    initializeLists();
    loadObjects();

}

std::shared_ptr<tson::Map> CoreLogic::DataProcessing::Map::getMap()
{
    return po_map_;
}

std::shared_ptr<std::map<int, std::vector<tson::Layer>>> CoreLogic::DataProcessing::Map::getLayers()
{
    return po_layers_;
}

std::shared_ptr<std::map<int, std::vector<tson::Object>>> CoreLogic::DataProcessing::Map::getObjects()
{
    return po_objects_;
}

Color CoreLogic::DataProcessing::Map::getBgColor()
{
    return bgColor_;
}

void CoreLogic::DataProcessing::Map::loadObjects()
{
    std::shared_ptr<EventManagement::Actor> actor = nullptr;

    for (auto &pair: *po_objects_)
    {
        int objectElevation = pair.first;

        for (auto &object: pair.second)
        {
            int objectId = object.getId();
            std::string objectClass = object.getClassType();

            Vector2 objectPosition = {(float) object.getPosition().x, (float) object.getPosition().y};

            Rectangle objectHitbox;
            if (object.getObjectType() == tson::ObjectType::Rectangle)
            {
                objectHitbox = {objectPosition.x, objectPosition.y, (float) (object.getSize().x),
                        (float) (object.getSize().y)};
            }

            Vector2 objectSize = {objectHitbox.width, objectHitbox.height};

            tson::PropertyCollection objectProperties = object.getProperties();

            //-------------------------------------------------------------------------------------------------------//

            if (objectClass == "collidable")
            {
                bool objectVisible = object.isVisible();

                actor = std::make_shared<EventManagement::Object::Barrier>(EventManagement::Object::Barrier
                        (objectPosition, objectHitbox,objectId, objectSize, objectVisible, objectElevation));
                ActorStorage::addActorByType(objectElevation, actor);
            } else if (objectClass == "rubble")
            {
                    actor = std::make_shared<EventManagement::Object::Rubble>(EventManagement::Object::Rubble(objectPosition,
                            objectHitbox, objectId, objectSize, objectElevation));
                ActorStorage::addActorByType(objectElevation, actor);
            } else if (objectClass == "pushable")
            {
                actor = std::make_shared<EventManagement::Object::Boulder>(EventManagement::Object::Boulder(objectPosition,
                        objectHitbox, objectId, objectSize, objectElevation));
                ActorStorage::addActorByType(objectElevation, actor);
            } else if (objectClass == "vines")
            {
                Vector2 objectCoordinates = {(float)objectProperties.getProperty("x_dest")->getValue<int>(),
                        (float) objectProperties.getProperty("y_dest")->getValue<int>()};

                actor = std::make_shared<EventManagement::Object::Vine>(EventManagement::Object::Vine(objectPosition,
                        objectHitbox, objectId, objectSize,objectElevation, objectCoordinates));
                ActorStorage::addActorByType(objectElevation, actor);
            } else if (objectClass == "water")
            {
                actor = std::make_shared<EventManagement::Object::Cliff>(EventManagement::Object::Cliff(objectPosition,
                        objectHitbox, objectId, objectSize, objectElevation, 0));
                ActorStorage::addActorByType(objectElevation, actor);
            } else if (objectClass == "jump_point")
            {
                Vector2 objectDestination = {(float)objectProperties.getProperty("x_dest")->getValue<int>(), (float)
                        objectProperties.getProperty("y_dest")->getValue<int>()};

                actor = std::make_shared<EventManagement::Object::JumpPoint>(EventManagement::Object::JumpPoint
                        (objectPosition, objectHitbox, objectId, objectSize, objectElevation, objectDestination));
                ActorStorage::addActorByType(objectElevation, actor);
            } else if (objectClass == "colonist")
            {
                bool objectClockwise = objectProperties.getProperty("clockwise")->getValue<bool>();
                int direction = objectProperties.getProperty("direction")->getValue<int>();
                CoreLogic::UserInterface::Direction objectStartingDirection;

                switch (direction)
                {
                case 0:
                    objectStartingDirection = UserInterface::Direction::UP;
                    break;
                case 1:
                    objectStartingDirection = UserInterface::Direction::RIGHT;
                    break;
                case 2:
                    objectStartingDirection = UserInterface::Direction::DOWN;
                    break;
                case 3:
                    objectStartingDirection = UserInterface::Direction::LEFT;
                    break;
                }

                int intervalEast = objectProperties.getProperty("interval_e")->getValue<int>();
                int intervalNorth = objectProperties.getProperty("interval_n")->getValue<int>();
                int intervalSouth = objectProperties.getProperty("interval_s")->getValue<int>();
                int intervalWest = objectProperties.getProperty("interval_w")->getValue<int>();

                std::map<CoreLogic::UserInterface::Direction, std::pair<int, int>> objectTurnCycle = {
                        {CoreLogic::UserInterface::Direction::UP, {intervalNorth, 0}},
                        {CoreLogic::UserInterface::Direction::DOWN, {intervalSouth, 0}},
                        {CoreLogic::UserInterface::Direction::LEFT, {intervalWest, 0}},
                        {CoreLogic::UserInterface::Direction::RIGHT, {intervalEast, 0}}};

                if (intervalEast == 0 && intervalNorth == 0 && intervalSouth == 0 && intervalWest == 0) objectTurnCycle.at(objectStartingDirection).first = INT_MAX;

                actor = std::make_shared<EventManagement::Actors::Colonist>(CoreLogic::EventManagement::Actors::Colonist
                        (objectPosition, objectHitbox,objectId,objectSize, objectElevation, objectClockwise, objectStartingDirection,  objectTurnCycle));
                ActorStorage::addActorByType(objectElevation, actor);
            } else if (objectClass == "cliffs")
            {
                int objectFallHeight = objectProperties.getProperty("height")->getValue<int>();

                actor = std::make_shared<EventManagement::Object::Cliff>(
                        EventManagement::Object::Cliff(objectPosition, objectHitbox, objectId, objectSize,
                                objectElevation, objectFallHeight));
                ActorStorage::addActorByType(objectElevation, actor);
            } else if (objectClass == "explosive_barrel")
            {
                int objectFallHeight = objectProperties.getProperty("height")->getValue<int>();
                int direction = objectProperties.getProperty("direction")->getValue<int>();

                UserInterface::Direction objectDirection;

                switch (direction)
                {
                case 0:
                    objectDirection = UserInterface::Direction::UP;
                    break;
                case 1:
                    objectDirection = UserInterface::Direction::RIGHT;
                    break;
                case 2:
                    objectDirection = UserInterface::Direction::DOWN;
                    break;
                case 3:
                    objectDirection = UserInterface::Direction::LEFT;
                    break;
                }

                actor = std::make_shared<EventManagement::Object::Barrel>(EventManagement::Object::Barrel
                        (objectPosition, objectHitbox, objectId, objectSize, objectElevation, objectFallHeight, objectDirection));

                ActorStorage::addActorByType(objectElevation, actor);
            }else if (objectClass == "textbox")
            {
                std::string objectText = objectProperties.getProperty("textbox_text")->getValue<std::string>();

                actor = std::make_shared<EventManagement::Object::TutorialBox>(EventManagement::Object::TutorialBox(objectPosition, objectHitbox, objectId, objectSize, objectElevation, objectText));
                ActorStorage::addActorByType(objectElevation, actor);
            } else if (objectClass == "lore_item")
            {
                std::string objectText = objectProperties.getProperty("lore_item_text")->getValue<std::string>();

                actor = std::make_shared<EventManagement::Object::Note>(EventManagement::Object::Note(objectPosition,
                        objectHitbox, objectId, objectSize, objectElevation, objectText));
                ActorStorage::addActorByType(objectElevation, actor);
            }else if (objectClass == "level_switch")
            {
                int objectLevelID = objectProperties.getProperty("level_switch")->getValue<int>();

                actor = std::make_shared<EventManagement::Object::LevelSwitch>(EventManagement::Object::LevelSwitch
                        (objectPosition, objectHitbox, objectId, objectSize, objectElevation, objectLevelID));
                ActorStorage::addActorByType(objectElevation, actor);
            } else if (objectClass == "mech")
            {

            } else if (objectClass == "uplink")
            {
                actor = std::make_shared<EventManagement::Object::Uplink>(EventManagement::Object::Uplink
                        (objectPosition, objectHitbox, objectId, objectSize, objectElevation));
                ActorStorage::addActorByType(objectElevation, actor);
            }else if (objectClass == "spawn_point")
            {
                actor = std::make_shared<EventManagement::Object::DroneRespawnPoint>(EventManagement::Object::DroneRespawnPoint
                        (objectPosition, objectHitbox, objectId, objectSize, objectElevation));
                ActorStorage::addActorByType(objectElevation, actor);
            }
        }
    }
}



#include <type_traits>

// Base template for regular types (e.g., tson::Layer)
template <typename T>
typename std::enable_if<!std::is_pointer<T>::value && !std::is_same<T, std::shared_ptr<typename std::remove_reference<T>::type>>::value,
        std::shared_ptr<std::map<int, std::vector<T>>>>::type
CoreLogic::DataProcessing::Map::initializeSpecificLists()
{
    auto list = std::make_shared<std::map<int, std::vector<T>>>();

    for (int i = 0; i < elevationLevels_; ++i)
    {
        (*list)[i] = std::vector<T>();  // Initialize with an empty vector of type T
    }

    return list;
}

// Specialized template for shared_ptr types
template <typename T>
typename std::enable_if<std::is_same<T, std::shared_ptr<typename std::remove_reference<T>::type>>::value,
        std::shared_ptr<std::map<int, std::vector<T>>>>::type
CoreLogic::DataProcessing::Map::initializeSpecificLists()
{
    auto list = std::make_shared<std::map<int, std::vector<T>>>();

    for (int i = 0; i < elevationLevels_; ++i)
    {
        (*list)[i] = std::vector<T>();  // Initialize with an empty vector of shared_ptr<T>
    }

    return list;
}

// Example usage
void CoreLogic::DataProcessing::Map::initializeLists()
{
    DataProcessing::ActorStorage::setLayers(initializeSpecificLists<tson::Layer>());
    DataProcessing::ActorStorage::setActors(initializeSpecificLists<std::shared_ptr<EventManagement::Actor>>());
    DataProcessing::ActorStorage::setCollidables(initializeSpecificLists<std::shared_ptr<EventManagement::Actor>>());
    DataProcessing::ActorStorage::setVisibles(initializeSpecificLists<std::shared_ptr<EventManagement::Actor>>());
    DataProcessing::ActorStorage::setAbilities(initializeSpecificLists<std::shared_ptr<EventManagement::Object::Ability>>());
    DataProcessing::ActorStorage::setWorkerAbilities(initializeSpecificLists<std::shared_ptr<EventManagement::Object::Ability>>());
    DataProcessing::ActorStorage::setScoutAbilities(initializeSpecificLists<std::shared_ptr<EventManagement::Object::Ability>>());
    DataProcessing::ActorStorage::setInteractions
    (initializeSpecificLists<std::shared_ptr<EventManagement::Object::Interaction>>());
    DataProcessing::ActorStorage::setEnemies(initializeSpecificLists<std::shared_ptr<EventManagement::Actors::Enemy>>());
    DataProcessing::ActorStorage::setBarriers(initializeSpecificLists<std::shared_ptr<EventManagement::Object::Barrier>>());
    DataProcessing::ActorStorage::setRubbles(initializeSpecificLists<std::shared_ptr<EventManagement::Object::Rubble>>());
    DataProcessing::ActorStorage::setBoulders(initializeSpecificLists<std::shared_ptr<EventManagement::Object::Boulder>>());
    DataProcessing::ActorStorage::setVines(initializeSpecificLists<std::shared_ptr<EventManagement::Object::Vine>>());
    DataProcessing::ActorStorage::setJumpPoints
    (initializeSpecificLists<std::shared_ptr<EventManagement::Object::JumpPoint>>());
    DataProcessing::ActorStorage::setColonists(initializeSpecificLists<std::shared_ptr<EventManagement::Actors::Colonist>>());
    DataProcessing::ActorStorage::setMechs(initializeSpecificLists<std::shared_ptr<EventManagement::Actors::Mech>>());
    DataProcessing::ActorStorage::setCliffs(initializeSpecificLists<std::shared_ptr<EventManagement::Object::Cliff>>());
    DataProcessing::ActorStorage::setBarrels(initializeSpecificLists<std::shared_ptr<EventManagement::Object::Barrel>>());
    DataProcessing::ActorStorage::setTutorialBoxes(initializeSpecificLists<std::shared_ptr<EventManagement::Object::TutorialBox>>());
    DataProcessing::ActorStorage::setNotes(initializeSpecificLists<std::shared_ptr<EventManagement::Object::Note>>());
    DataProcessing::ActorStorage::setLevelSwitches(initializeSpecificLists<std::shared_ptr<EventManagement::Object::LevelSwitch>>());
    DataProcessing::ActorStorage::setUplinks(initializeSpecificLists<std::shared_ptr<EventManagement::Object::Uplink>>());
}



