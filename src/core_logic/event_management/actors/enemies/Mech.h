//
// Created by Josi on 15.06.2024.
//

#ifndef HIVE_MECH_H
#define HIVE_MECH_H

#include "event_management/Actor.h"
#include "event_management/actors/Enemy.h"

namespace CoreLogic::EventManagement::Actors {

            class Mech : public Enemy{

            public:
                Mech(Vector2 pa_position, Rectangle pa_hitbox, int pa_objectId, Vector2 pa_objectSize, int pa_objectElevation, bool pa_objectClockwise,
                        CoreLogic::UserInterface::Direction pa_objectStartingDirection, std::map<CoreLogic::UserInterface::Direction, std::pair<int, int>> pa_objectTurnCycle);

            };
}

#endif //HIVE_MECH_H
