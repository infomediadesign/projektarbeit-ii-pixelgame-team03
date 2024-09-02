//
// Created by Josi on 02.09.2024.
//

#ifndef HIVE_ABILITY_H
#define HIVE_ABILITY_H
#include "../actors/MovableActor.h"

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

        AbilityType getAbilityType() const;

    protected:
        AbilityType abilityType_;

    };
}

#endif //HIVE_ABILITY_H
