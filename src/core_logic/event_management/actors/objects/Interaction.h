//
// Created by Josi on 02.09.2024.
//

#ifndef HIVE_INTERACTION_H
#define HIVE_INTERACTION_H

#include "event_management/Actor.h"

namespace CoreLogic::EventManagement::Object
{
    class Interaction : public Actor
    {
    public:
        enum InteractionType
        {
            CLIMBING, NOTE, CHECKPOINT, UPLINK
        };

        Interaction(Vector2 pa_position, Rectangle pa_hitbox, int pa_id, CollisionType pa_collidable, Vector2 pa_size, bool pa_visible, int pa_elevation, InteractionType pa_type);

        InteractionType getType() const;
void setType(InteractionType pa_type);
    protected:
        InteractionType type_;
    };
}

#endif //HIVE_INTERACTION_H
