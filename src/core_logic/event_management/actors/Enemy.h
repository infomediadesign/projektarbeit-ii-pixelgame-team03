//
// Created by Josi on 12.06.2024.
//

#ifndef HIVE_ENEMY_H
#define HIVE_ENEMY_H

#include <map>
#include "Actor.h"

namespace CoreLogic::EventManagement::Actors {

    class Enemy : public Actor{
    public:
        bool checkVision();
        void update();
    protected:
        bool visionConnected_ = false;
        std::map<CoreLogic::UserInterface::Direction, std::pair<int, int>> visionMap_;
        

    };
}

#endif //HIVE_ENEMY_H
