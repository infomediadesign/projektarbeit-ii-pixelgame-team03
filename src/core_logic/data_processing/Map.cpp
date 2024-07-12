//
// Created by keanu on 5/22/2024.
//

#include "Map.h"
#include "Store.h"
#include "../event_management/actor/Drone.h"



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
    for (int i = 0; i <= elevationLevels_; i++)
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

    /** @note: old obj parser */
    /*for (int i = 0; i < layers.size(); i++)
    {
        if (layers[i].getType() == tson::LayerType::ObjectGroup)
        {
            tempObjMap.insert({i, layers[i].getObjects()});
        }

    }*/


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

void CoreLogic::DataProcessing::Map::loadObjectsExample()
{
    /**
     *@note: Example for object attribute reading for Josi
     **/
    int elev = 1;
    for (auto &object: po_objects_ ->at(elev))
    {
        tson::PropertyCollection props = object.getProperties();
        Vector2 position = {(float)object.getPosition().x, (float)object.getPosition().y};
        std::string klasse = object.getClassType();
        bool visible = object.isVisible();
        int id = object.getId();
        std::string name = object.getName();
        std::string toolTip = props.getProperty("tooltip")->getValue<std::string>();
        bool pushable = props.getProperty("pushable")->getValue<bool>();
        int hitboxWidth = props.getProperty("hitbox_width")->getValue<int>();
        int hitboxHeight = props.getProperty("hitbox_height")->getValue<int>();
    }
}

void CoreLogic::DataProcessing::Map::loadObjects()
{
    auto drone = std::make_shared<EventManagement::Actors::Drone>(Vector2{24, 24}, Rectangle{0, 0, 32, 32}, 0,
                                                                        EventManagement::Actor::CollisionType::NONE,
                                                                        Vector2{32, 32}, true, 1);
    ActorStorage::setPlayer(drone);

    int objectId = 1;

    for (int elev = 1; elev <= elevationLevels_; elev++)
    {
        for (auto &object: po_objects_->at(elev))
        {
            std::string klasse = object.getClassType();

            Vector2 objectPosition = {(float) object.getPosition().x, (float) object.getPosition().y};

            tson::PropertyCollection props = object.getProperties();

            EventManagement::Actor::CollisionType objectCollisionType = props.getProperty(
                    "collisionType")->getValue<EventManagement::Actor::CollisionType>();

            bool objectVisible = object.isVisible();

            Vector2 objectSize = {props.getProperty("actualSizeX")->getValue<float>(), props.getProperty
                    ("actualSizeY")->getValue<float>()};

            Rectangle objectHitbox;
            if (object.getObjectType() == tson::ObjectType::Rectangle)
            {
                objectHitbox = {objectPosition.x, objectPosition.y, (float) (object.getSize().x),
                                          (float) (object.getSize().y)};
            }

            std::shared_ptr<EventManagement::Actor> actor = nullptr;

            if (klasse == "Colonist")
            {
                actor = std::make_shared<EventManagement::Actors::Colonist>(
                        EventManagement::Actors::Colonist(objectPosition, objectHitbox, objectId,
                                                          objectCollisionType,
                                                          objectSize, objectVisible, elev));
            } else if (klasse == "Hazmat")
            {
                actor = std::make_shared<EventManagement::Actors::Hazmat>(
                        EventManagement::Actors::Hazmat(objectPosition, objectHitbox, objectId, objectCollisionType,
                                                        objectSize, objectVisible, elev));
            } else if (klasse == "Mech")
            {
                actor = std::make_shared<EventManagement::Actors::Mech>(
                        EventManagement::Actors::Mech(objectPosition, objectHitbox, objectId, objectCollisionType,
                                                      objectSize, objectVisible, elev));
            }


            if (actor != nullptr)
            {
                ActorStorage::addActor(elev, actor);
            }


            objectId++;
        }
    }
}


