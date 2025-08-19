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
        JumpPoint(Vector2 pa_position, Rectangle pa_hitbox, int pa_id, Vector2 pa_size, int pa_elevation, Vector2 pa_destination);

        Vector2 getJumpPosition() const;
        void setJumpPosition(Vector2 pa_position);

        void setGlowing() override{};
        void resetGlowing() override{};
    protected:
        Vector2 coordinates_;
    };
}

#endif //HIVE_JUMPPOINT_H
