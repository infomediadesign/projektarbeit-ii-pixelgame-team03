//
// Created by Josi on 03.09.2024.
//

#ifndef HIVE_CLIFF_H
#define HIVE_CLIFF_H

#include "Actor.h"

namespace CoreLogic::EventManagement::Object
{
    class Cliff : virtual public Actor
    {
    public:
        int getElevation() const;
        int getFallHeight() const;
    protected:
        int elevation_ = 0;
        int fallHeight_ = 0;
    };
}

#endif //HIVE_CLIFF_H
