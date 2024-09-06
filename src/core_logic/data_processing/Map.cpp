//
// Created by keanu on 5/22/2024.
//

#include "Map.h"
#include "Store.h"
#include "../event_management/actors/Drone.h"



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
            if (objectId == 424) {
                std::cout << "fick dich doch" << std::endl;
            }
            std::string klasse = object.getClassType();

            Vector2 objectPosition = {(float) object.getPosition().x, (float) object.getPosition().y};

            tson::PropertyCollection props = object.getProperties();

            EventManagement::Actor::CollisionType objectCollisionType;

            if (props.hasProperty("collisionType"))
            {
                objectCollisionType = static_cast<EventManagement::Actor::CollisionType>(props.getProperty(
                        "collisionType")->getValue<int>());
            } else {
                objectCollisionType = EventManagement::Actor::CollisionType::NONE;
            }

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

            if (klasse == "collidable")
            {
                actor = std::make_shared<EventManagement::Actor>(
                        EventManagement::Actor(objectPosition, objectHitbox, objectId, objectCollisionType, objectSize, objectVisible, pair.first));
            }

            if (klasse == "LevelChange")
            {
                actor = std::make_shared<EventManagement::Actor>(
                        EventManagement::Actor(objectPosition, objectHitbox, objectId, static_cast<EventManagement::Actor::CollisionType>(4), objectSize, objectVisible, pair.first));
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

            std::cout << objectId << std::endl;
            objectId++;
        }
    }
}


