//
// Created by Josi on 12.06.2024.
//

#ifndef HIVE_WORKER_H
#define HIVE_WORKER_H

#include "actors/Drone.h"

namespace CoreLogic::EventManagement::Actors
{

    class Worker : public Drone
    {
    public:
        Worker(Vector2 pa_position, Rectangle pa_hitbox, int pa_id,
                CollisionType pa_collisionType, Vector2 pa_size, bool pa_visible,
                int pa_elevation);
        void shiftFrame(int pa_frameShift) override;
    protected:
        void checkAbility() override;
    };

}

#endif //HIVE_WORKER_H
