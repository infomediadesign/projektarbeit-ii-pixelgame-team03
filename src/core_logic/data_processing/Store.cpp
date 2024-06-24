//
// Created by keanu on 6/1/2024.
//
#include "Store.h"

std::shared_ptr<Texture2D> CoreLogic::DataProcessing::TileMap::tileMap_ = std::make_shared<Texture2D>(LoadTexture("assets/graphics/Tile_Atlas.png"));
std::shared_ptr<Texture2D> CoreLogic::DataProcessing::TileMap::getTileMap() {return tileMap_;}

std::shared_ptr<CoreLogic::EventManagement::Actors::Drone> CoreLogic::DataProcessing::ActorStorage::po_player_ = std::make_shared<EventManagement::Actors::Drone>(
        EventManagement::Actors::Drone({0, 0}, {0, 0, 0, 0}, 0, {32,32})
        );

std::shared_ptr<CoreLogic::EventManagement::Actors::Drone> CoreLogic::DataProcessing::ActorStorage::getPlayer() {return po_player_;}

std::shared_ptr<std::map<int, std::vector<CoreLogic::EventManagement::Actor>>> CoreLogic::DataProcessing::ActorStorage::getActors() {return po_actors_;}

std::shared_ptr<std::map<int, std::vector<tson::Layer>>> CoreLogic::DataProcessing::ActorStorage::getLayers() {return po_layers_;}

/**
 * @brief: Zum hinzufügen von Actors, die als tson::Object's aus der Map geladen werden
 **/
void CoreLogic::DataProcessing::ActorStorage::setActors(std::map<int, std::vector<tson::Object>> &pa_objects)
{

}

/**
 * @brief: Zum hinzufügen von Actors, die während des laufenden Spiels erzeugt werden
 **/
void CoreLogic::DataProcessing::ActorStorage::addActor(EventManagement::Actor &pa_actor)
{

}

void CoreLogic::DataProcessing::ActorStorage::setLayers(std::shared_ptr<std::map<int, std::vector<tson::Layer>>> pa_layers)
{
    po_layers_ = pa_layers;
}
