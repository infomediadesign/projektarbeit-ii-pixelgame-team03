//
// Created by Josi on 15.06.2024.
//

#ifndef HIVE_COLONIST_H
#define HIVE_COLONIST_H

#include <map>
#include "event_management/actors/Enemy.h"

namespace CoreLogic::EventManagement::Actors {

            class Colonist : public Enemy {

            public:
                Colonist(Vector2 pa_position, Rectangle pa_hitbox, int pa_objectId, Vector2 pa_objectSize, int pa_objectElevation, bool pa_objectClockwise,
                        CoreLogic::UserInterface::Direction pa_objectStartingDirection, std::map<CoreLogic::UserInterface::Direction, std::pair<int, int>> pa_objectTurnCycle);
            };

}

#endif //HIVE_COLONIST_H
