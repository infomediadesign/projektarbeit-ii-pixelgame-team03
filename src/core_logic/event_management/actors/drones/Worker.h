//
// Created by Josi on 12.06.2024.
//

#ifndef HIVE_WORKER_H
#define HIVE_WORKER_H

#include "actors/Drone.h"

namespace CoreLogic::EventManagement::Actors
{

    class Worker : public Drone
    {
    public:
    protected:
        void checkAbility() override;
    };

}

#endif //HIVE_WORKER_H
