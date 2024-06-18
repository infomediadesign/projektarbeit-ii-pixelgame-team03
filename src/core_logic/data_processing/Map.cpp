//
// Created by keanu on 5/22/2024.
//

#include "Map.h"

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

    po_layers_ = std::make_shared<std::vector<tson::Layer>>(map.getLayers());
    auto& layers = *po_layers_;

    std::map<int, std::vector<tson::Object>> tempObjMap;
    for (int i = 0; i < layers.size(); i++)
    {
        if (layers[i].getType() == tson::LayerType::ObjectGroup)
        {
            tempObjMap.insert({i, layers[i].getObjects()});
        }
    }
    po_objects_ = std::make_shared<std::map<int, std::vector<tson::Object>>>(tempObjMap);

}

std::shared_ptr<tson::Map> CoreLogic::DataProcessing::Map::getMap()
{
    return po_map_;
}

std::shared_ptr<std::vector<tson::Layer>> CoreLogic::DataProcessing::Map::getLayers()
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


