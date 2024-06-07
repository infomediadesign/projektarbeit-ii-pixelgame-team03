//
// Created by keanu on 5/26/2024.
//

#ifndef RAYLIBSTARTER_STORE_H
#define RAYLIBSTARTER_STORE_H

#include <memory>
#include <mutex>
#include "raylib.h"


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
        TileMap();
        static TileMap* po_instance_;
        static std::mutex mutex_;
        std::shared_ptr<Texture2D> tileMap_;
    public:
        static TileMap* getInstance();
        std::shared_ptr<Texture2D> getTileMap();

    };
}




#endif //RAYLIBSTARTER_STORE_H
