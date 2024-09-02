//
// Created by Josi on 02.09.2024.
//

#ifndef HIVE_BARREL_H
#define HIVE_BARREL_H

#include "Ability.h"
#include "Cliff.h"

namespace CoreLogic::EventManagement::Object
{
class Barrel :public Ability, public Cliff
    {
    public:
        int getNewElevation() const;
    protected:
        int newElevation_ = 0;
    };
}

#endif //HIVE_BARREL_H
