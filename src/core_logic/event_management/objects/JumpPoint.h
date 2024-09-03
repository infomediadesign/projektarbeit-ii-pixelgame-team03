//
// Created by Josi on 03.09.2024.
//

#ifndef HIVE_JUMPPOINT_H
#define HIVE_JUMPPOINT_H

#include "Ability.h"

namespace CoreLogic::EventManagement::Object
{
    class JumpPoint : public Ability
    {
    public:
        Vector2 getJumpPosition() const;
    protected:
        Vector2 coordinates_;
    };
}

#endif //HIVE_JUMPPOINT_H
