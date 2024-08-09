//
// Created by Josi on 12.06.2024.
//

#ifndef HIVE_ENEMY_H
#define HIVE_ENEMY_H

#include "MovableActor.h"

namespace CoreLogic::EventManagement::Actors {

    class Enemy : public MovableActor{
    public:
        bool checkVision();
    };
}

#endif //HIVE_ENEMY_H
