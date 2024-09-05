//
// Created by Josi on 15.06.2024.
//

#include "Colonist.h"

namespace CoreLogic::EventManagement::Actors
{

    Colonist::Colonist(Vector2 pa_position, Rectangle pa_hitbox, int pa_id, Vector2 pa_size, int pa_elevation, bool pa_clockwise, CoreLogic::UserInterface::Direction pa_startingDirection, std::map<CoreLogic::UserInterface::Direction, std::pair<int, int>> pa_turnCycle) :
            clockwise_(pa_clockwise), startingDirection_(pa_startingDirection), turnCycle_(pa_turnCycle),
            EventManagement::Actor(pa_position, pa_hitbox, pa_id, Actor::CollisionType::COLLISION, pa_size, true,
                    pa_elevation)
    {

    }

    bool Colonist::getClockwise() const
    {
        return clockwise_;
    }

    CoreLogic::UserInterface::Direction Colonist::getStartingDirection() const
    {
        return startingDirection_;
    }

    std::map<CoreLogic::UserInterface::Direction, std::pair<int, int>> Colonist::getTurnCycle() const
    {
        return turnCycle_;
    }
}