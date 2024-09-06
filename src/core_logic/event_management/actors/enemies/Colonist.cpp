//
// Created by Josi on 15.06.2024.
//

#include "Colonist.h"
#include "Store.h"

namespace CoreLogic::EventManagement::Actors
{


    Colonist::Colonist(Vector2 pa_position, Rectangle pa_hitbox, int pa_objectId, Vector2 pa_objectSize,
            int pa_objectElevation, bool pa_objectClockwise,
            CoreLogic::UserInterface::Direction pa_objectStartingDirection,
            std::map<CoreLogic::UserInterface::Direction, std::pair<int, int>> pa_objectTurnCycle) :
            Enemy(pa_position, pa_hitbox, pa_objectId, pa_objectSize, pa_objectElevation, pa_objectClockwise,
                    pa_objectStartingDirection, pa_objectTurnCycle, {12, 12})
    {
        sprite_ = DataProcessing::SpriteStorage::getSprite(DataProcessing::SpriteStorage::COLONIST);
    }
}