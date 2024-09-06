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
        Enemy(Vector2 pa_position, Rectangle pa_hitbox, int pa_objectId, Vector2 pa_objectSize, int pa_objectElevation, bool pa_objectClockwise,
              CoreLogic::UserInterface::Direction pa_objectStartingDirection, std::map<CoreLogic::UserInterface::Direction, std::pair<int, int>> pa_objectTurnCycle,
              Vector2 pa_visionPoint);
        void update();
        void forceTurn(Vector2 pa_triggerPoint);
        void die(){dead_=true;}
        [[nodiscard]] bool getVisionConnected()const{return visionConnected_;}
        [[nodiscard]] bool getDead()const{return dead_;}
    protected:
        void checkVision();
        bool visionConnected_ = false;
        const Vector2 visionOrigin_;
        bool clockwise_;
        std::map<CoreLogic::UserInterface::Direction, std::pair<int, int>> turnCyles_;
        bool checkVisionCollisionObjects(Ray *pa_visionRays, bool *pa_visionCollisions);
        void updateTurnCycle();
        void turn();
        bool dead_ = false;
        

    };
}

#endif //HIVE_ENEMY_H
