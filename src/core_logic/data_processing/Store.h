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
        ActorStorage();
        ~ActorStorage();
        static std::shared_ptr<std::map<int, std::vector<EventManagement::Actor>>> actors_;
    public:
        static std::shared_ptr<std::map<int, std::vector<EventManagement::Actor>>> getActors();
    };
}




#endif //RAYLIBSTARTER_STORE_H
