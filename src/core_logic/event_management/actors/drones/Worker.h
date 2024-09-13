//
// Created by Josi on 12.06.2024.
//

#ifndef HIVE_WORKER_H
#define HIVE_WORKER_H

#include "event_management/actors/Drone.h"

namespace CoreLogic::EventManagement::Actors
{

    class Worker : public Drone
    {
    public:
        Worker(Vector2 pa_position, Rectangle pa_hitbox, int pa_id, Vector2 pa_size,
                int pa_elevation);
        Worker(Vector2 pa_position, Rectangle pa_hitbox, int pa_id, Vector2 pa_size,
                int pa_elevation, int pa_maxHealth, int pa_currentHealth);

        void shiftFrame(int pa_frameShift) override;
    protected:
        void checkAbility() override;
    };

}

#endif //HIVE_WORKER_H
