//
// Created by keanu on 5/26/2024.
//

#ifndef RAYLIBSTARTER_STORE_H
#define RAYLIBSTARTER_STORE_H

#include <memory>
#include <mutex>
#include <vector>
#include <map>
#include "raylib.h"
#include "event_management/Actor.h"
#include "event_management/actor/Drone.h"
#include "../../tileson.h"


namespace CoreLogic::DataProcessing
{
    enum GameState
    {
        MainMenu = 0,
        InGame = 1,
        Pause = 2,
        Settings = 3
    };
    inline long long int ticks = 1;
    const int tileSize = 24;

    struct TileMap
    {
    private:
        static std::shared_ptr<Texture2D> tileMap_;
    public:
        static std::shared_ptr<Texture2D> getTileMap();
    };

    struct ActorStorage
    {
    /**
     * @todo: actual implementaion for po_actors_(convert Objects from map Class)
     * @note: possibly also get std::map<int, vector<Layer>> po_layers_ as to not have to make the Map klass static
     **/
    private:
        static std::shared_ptr<EventManagement::Actors::Drone> po_player_;
        static std::shared_ptr<std::map<int, std::vector<std::shared_ptr<EventManagement::Actor>>>> po_actors_;
        static std::shared_ptr<std::map<int, std::vector<tson::Layer>>> po_layers_;
    public:
        static std::shared_ptr<EventManagement::Actors::Drone> getPlayer();
        static void setPlayer(std::shared_ptr<EventManagement::Actors::Drone> pa_player);

        static std::shared_ptr<std::map<int, std::vector<std::shared_ptr<EventManagement::Actor>>>> getActors();
        static void setActors(std::map<int, std::vector<EventManagement::Actor>> &pa_actors);
        static void addActor(EventManagement::Actor &pa_actor);

        static std::shared_ptr<std::map<int, std::vector<tson::Layer>>> getLayers();
        static void setLayers(std::shared_ptr<std::map<int, std::vector<tson::Layer>>> pa_layers);
        //static void newDrone(//DroneType);
    };

}




#endif //RAYLIBSTARTER_STORE_H
