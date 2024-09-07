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

    ActorStorage::Initialize();
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
                std::string objectText = objectProperties.getProperty("text")->getValue<std::string>();

                actor = std::make_shared<EventManagement::Object::TutorialBox>(EventManagement::Object::TutorialBox(objectPosition, objectHitbox, objectId, objectSize, objectElevation, objectText));
                ActorStorage::addActorByType(objectElevation, actor);
            } else if (objectClass == "lore_item")
            {
                std::string objectText = objectProperties.getProperty("text")->getValue<std::string>();

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

/*
void CoreLogic::DataProcessing::Map::loadObjects()
{
    auto drone = std::make_shared<EventManagement::Actors::Drone>(Vector2{100, 100}, Rectangle{100,
                                                                                               100, 38, 38}, 0,
                                                                        EventManagement::Actor::CollisionType::NONE,
                                                                        Vector2{38, 38}, true, 0);
    ActorStorage::setPlayer(drone);

    int objectId = 1;

    for (auto &pair: *po_objects_)
    {
        for (auto &object: pair.second)
        {
            std::string klasse = object.getClassType();

            Vector2 objectPosition = {(float) object.getPosition().x, (float) object.getPosition().y};

            tson::PropertyCollection props = object.getProperties();

            EventManagement::Actor::CollisionType objectCollisionType = static_cast<EventManagement::Actor::CollisionType>(props.getProperty(
                    "collisionType")->getValue<int>());

            bool objectVisible = object.isVisible();
            Vector2 objectSize = {0, 0};

            try
            {
                if (props.hasProperty("actualSizeX") && props.hasProperty("actualSizeY"))
                {

                    objectSize = {
                            props.getProperty("actualSizeX")->getValue<float>(), props.getProperty
                                    ("actualSizeY")->getValue<float>()
                    };
                } else if (object.getSize().x != 0 && object.getSize().y != 0) {
                    objectSize = {
                            static_cast<float>(object.getSize().x), static_cast<float>(object.getSize().y)
                    };
                }
            } catch (const std::exception &e)
            {
                TraceLog(LOG_INFO, "No actualSize Variable");
            }


            Rectangle objectHitbox;
            if (object.getObjectType() == tson::ObjectType::Rectangle)
            {
                objectHitbox = {objectPosition.x, objectPosition.y, (float) (object.getSize().x),
                                          (float) (object.getSize().y)};
            }

            std::shared_ptr<EventManagement::Actor> actor = nullptr;

            if (klasse == "Wall")
            {
                actor = std::make_shared<EventManagement::Actor>(
                        EventManagement::Actor(objectPosition, objectHitbox, objectId, objectCollisionType, objectSize, objectVisible, pair.first));
            }

            if (klasse == "Colonist")
            {
                actor = std::make_shared<EventManagement::Actors::Colonist>(
                        EventManagement::Actors::Colonist(objectPosition, objectHitbox, objectId,
                                                          objectCollisionType,
                                                          objectSize, objectVisible, pair.first));
            } else if (klasse == "Hazmat")
            {
                actor = std::make_shared<EventManagement::Actors::Hazmat>(
                        EventManagement::Actors::Hazmat(objectPosition, objectHitbox, objectId, objectCollisionType,
                                                        objectSize, objectVisible, pair.first));
            } else if (klasse == "Mech")
            {
                actor = std::make_shared<EventManagement::Actors::Mech>(
                        EventManagement::Actors::Mech(objectPosition, objectHitbox, objectId, objectCollisionType,
                                                      objectSize, objectVisible, pair.first));
            }


            if (actor != nullptr)
            {
                ActorStorage::addActor(pair.first, actor);
            }


            objectId++;
        }
    }

}
 */


