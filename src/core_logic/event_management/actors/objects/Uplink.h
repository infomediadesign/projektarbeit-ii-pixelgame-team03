//
// Created by Josi on 05.09.2024.
//

#ifndef HIVE_UPLINK_H
#define HIVE_UPLINK_H

#include "Actor.h"
#include "Interaction.h"

namespace CoreLogic::EventManagement::Object
{
    class Uplink : public Interaction
    {
    public:
        Uplink(Vector2 pa_position, Rectangle pa_hitbox, int pa_id, Vector2 pa_size, int pa_elevation);
    };
}

#endif //HIVE_UPLINK_H
