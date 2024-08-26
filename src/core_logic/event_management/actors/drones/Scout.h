//
// Created by Josi on 12.06.2024.
//

#ifndef HIVE_SCOUT_H
#define HIVE_SCOUT_H

#include "actors/Drone.h"

namespace CoreLogic::EventManagement::Actors
{

    class Scout : public Drone
    {
    public:
    protected:
        void checkAbility() override;
    };

}

#endif //HIVE_SCOUT_H
