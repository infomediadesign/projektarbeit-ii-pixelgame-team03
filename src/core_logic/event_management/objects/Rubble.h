//
// Created by Josi on 02.09.2024.
//

#ifndef HIVE_RUBBLE_H
#define HIVE_RUBBLE_H

#include "Ability.h"

namespace CoreLogic::EventManagement::Object
{
    class Rubble : public Ability
    {
        public:
        void setCleaned();
    };
}

#endif //HIVE_RUBBLE_H
