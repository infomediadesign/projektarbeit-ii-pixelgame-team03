//
// Created by Josi on 15.06.2024.
//

#ifndef HIVE_COLONIST_H
#define HIVE_COLONIST_H

#include <map>
#include "../../Actor.h"

namespace CoreLogic::EventManagement::Actors {

            class Colonist : public EventManagement::Actor{

            public:
                Colonist(Vector2 pa_position, Rectangle pa_hitbox, int pa_id, Vector2 pa_size, int pa_elevation, bool pa_clockwise, CoreLogic::UserInterface::Direction pa_startingDirection, std::map<CoreLogic::UserInterface::Direction, std::pair<int, int>> pa_turnCycle);

            };

}

#endif //HIVE_COLONIST_H
