//
// Created by Josi on 12.06.2024.
//

#ifndef HIVE_ENEMY_H
#define HIVE_ENEMY_H

#include <map>
#include "Actor.h"

namespace CoreLogic::EventManagement::Actors {

    class Enemy : public Actor
    {
    public:
        void update();
        void forceTurn(CoreLogic::UserInterface::Direction pa_newDirection, int pa_turnFrames);
    protected:
        void checkVision();
        bool visionConnected_ = false;
        const Vector2 visionOrigin_;
        std::map<CoreLogic::UserInterface::Direction, std::pair<int, int>> visionMap_;
        bool checkVisionCollisionObjects(Ray *pa_visionRays, bool *pa_visionCollisions);
        void turn();
        

    };
}

#endif //HIVE_ENEMY_H
