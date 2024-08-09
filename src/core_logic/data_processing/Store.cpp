//
// Created by keanu on 6/1/2024.
//
#include "Store.h"
#include "raylib.h"

std::shared_ptr<Texture2D> CoreLogic::DataProcessing::TileMap::po_tileMap_ = nullptr;
std::shared_ptr<Texture2D> CoreLogic::DataProcessing::TileMap::getTileMap() {return po_tileMap_;}

std::shared_ptr<CoreLogic::EventManagement::Actors::Drone> CoreLogic::DataProcessing::ActorStorage::po_player_;
std::shared_ptr<std::map<int, std::vector<std::shared_ptr<CoreLogic::EventManagement::Actor>>>>
        CoreLogic::DataProcessing::ActorStorage::po_actors_;
std::shared_ptr<std::map<int, std::vector<tson::Layer>>> CoreLogic::DataProcessing::ActorStorage::po_layers_;

void CoreLogic::DataProcessing::TileMap::Initialize()
{
    if (po_tileMap_ == nullptr)
    {
        po_tileMap_ = std::make_shared<Texture2D>(LoadTexture("assets/graphics/hive_ARTI_TileAtlas.png"));
    }

}


void CoreLogic::DataProcessing::ActorStorage::Initialize()
{
        ActorStorage::po_player_ = {};

        std::map<int, std::vector<std::shared_ptr<EventManagement::Actor>>> actors = {};
        ActorStorage::po_actors_ = std::make_shared<std::map<int, std::vector<std::shared_ptr<EventManagement::Actor>>>>(actors);

        std::map<int, std::vector<tson::Layer>> layers = {};
        ActorStorage::po_layers_ = std::make_shared<std::map<int, std::vector<tson::Layer>>>(layers);

}


std::shared_ptr<CoreLogic::EventManagement::Actors::Drone> CoreLogic::DataProcessing::ActorStorage::getPlayer() {return po_player_;}

std::shared_ptr<std::map<int, std::vector<std::shared_ptr<CoreLogic::EventManagement::Actor>>>> CoreLogic::DataProcessing::ActorStorage::getActors() {return po_actors_;}

std::shared_ptr<std::map<int, std::vector<tson::Layer>>> CoreLogic::DataProcessing::ActorStorage::getLayers() {return po_layers_;}

/**
 * @brief: Zum hinzufügen von Actors, die als tson::Object's aus der Map geladen werden
 **/
void CoreLogic::DataProcessing::ActorStorage::setActors(
        std::shared_ptr<std::map<int, std::vector<std::shared_ptr<EventManagement::Actor>>>> pa_actors)
{
    po_actors_ = pa_actors;
}

/**
 * @brief: Zum hinzufügen von Actors, die während des laufenden Spiels erzeugt werden
 **/
void CoreLogic::DataProcessing::ActorStorage::addActor(int pa_elevation, std::shared_ptr<EventManagement::Actor> pa_actor)
{
    if (!po_actors_.get()->empty())
    {
        auto it = po_actors_->find(pa_elevation);
        if (it != po_actors_->end())
        {
            it->second.push_back(pa_actor);
        }
    } else
    {
        po_actors_->insert({pa_elevation, {pa_actor}});
    }
}

void CoreLogic::DataProcessing::ActorStorage::setLayers(std::shared_ptr<std::map<int, std::vector<tson::Layer>>> pa_layers)
{
    po_layers_ = pa_layers;
}

void CoreLogic::DataProcessing::ActorStorage::setPlayer(std::shared_ptr<EventManagement::Actors::Drone> pa_player) {
    po_player_ = pa_player;
}

std::shared_ptr<CoreLogic::EventManagement::Actor> CoreLogic::DataProcessing::ActorStorage::getActorByID(int pa_actorID)
{
    for (auto &pair: *po_actors_)
    {
        for (auto &actor: pair.second)
        {
            if (actor->getId() == pa_actorID)
            {
                return actor;
            }
        }
    }
    return nullptr;
}
