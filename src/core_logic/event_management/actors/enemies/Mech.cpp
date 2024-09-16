//
// Created by Josi on 15.06.2024.
//

#include "Mech.h"
#include "data_processing/Store.h"

namespace CoreLogic::EventManagement::Actors
{

    Mech::Mech(Vector2 pa_position, Rectangle pa_hitbox, int pa_objectId, Vector2 pa_objectSize, int pa_objectElevation,
            bool pa_objectClockwise, CoreLogic::UserInterface::Direction pa_objectStartingDirection,
            std::map<CoreLogic::UserInterface::Direction, std::pair<int, int>> pa_objectTurnCycle) :
            Enemy(pa_position, pa_hitbox, pa_objectId, pa_objectSize, pa_objectElevation, pa_objectClockwise, pa_objectStartingDirection, pa_objectTurnCycle, {pa_position.x +24, pa_position.y + 12}, MECH)
    {
        sprite_ = DataProcessing::SpriteStorage::getSprite(DataProcessing::SpriteStorage::MECH);
    }
}