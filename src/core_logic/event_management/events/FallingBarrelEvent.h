//
// Created by keanu on 9/1/2024.
//

#ifndef HIVE_FALLINGBARRELEVENT_H
#define HIVE_FALLINGBARRELEVENT_H


#include "FallingEvent.h"
#include "objects/Barrel.h"

namespace CoreLogic::EventManagement
{

    class FallingBarrelEvent: public FallingEvent
    {

    public:
        FallingBarrelEvent(std::shared_ptr<Object::Barrel> pa_barrel);
    protected:
        void destroy() override;

    };

} // CoreLogic
// EventManagement

#endif //HIVE_FALLINGBARRELEVENT_H
