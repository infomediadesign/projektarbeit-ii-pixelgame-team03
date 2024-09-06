//
// Created by Josi on 02.09.2024.
//

#ifndef HIVE_ABILITY_H
#define HIVE_ABILITY_H
#include "event_management/actors/MovableActor.h"

namespace CoreLogic::EventManagement::Object
{
    class Ability : public Actors::MovableActor
    {
        public:
        enum AbilityType{
            CLEANING,
            PUSH,
            JUMP,
            BARREL
        };

        Ability(Vector2 pa_position, Rectangle pa_hitbox, int pa_id, CollisionType pa_collisionType, Vector2
        pa_size, bool pa_visible, int pa_elevation, AbilityType pa_abilityType);

        AbilityType getAbilityType() const;
        void setAbilityType(AbilityType pa_abilityType);

    protected:
        AbilityType abilityType_;

    };
}

#endif //HIVE_ABILITY_H
