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
        private:
            static std::shared_ptr<EventManagement::Actors::Drone> po_player_;
            static std::shared_ptr<std::vector<std::shared_ptr<EventManagement::Actor>>> po_actors_;
        public:
            static std::shared_ptr<EventManagement::Actors::Drone> getPlayer();
        //static void newDrone(//DroneType);
    };

}




#endif //RAYLIBSTARTER_STORE_H
