//
// Created by Josi on 12.06.2024.
//

#ifndef HIVE_SCOUT_H
#define HIVE_SCOUT_H

#include "event_management/actors/Drone.h"

namespace CoreLogic::EventManagement::Actors
{

    class Scout : public Drone
    {
    public:
        Scout(Vector2 pa_position, Rectangle pa_hitbox, int pa_id, Vector2 pa_size,
                int pa_elevation);
    protected:
        void checkAbility() override;
    };

}

#endif //HIVE_SCOUT_H
