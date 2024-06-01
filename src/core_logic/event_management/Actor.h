//
// Created by keanu on 5/23/2024.
//

#ifndef RAYLIBSTARTER_ACTOR_H
#define RAYLIBSTARTER_ACTOR_H


#include <vector>
#include <memory>
#include "Trigger.h"


namespace CoreLogic::EventManagement
{
    class Actor
    {
    public:
        Actor(int spriteCoordinates);

    protected:
        int spriteCoordinates_;
        int mapLayerID_;
        std::unique_ptr<std::vector<CoreLogic::EventManagement::Trigger>> po_eventTriggers_;
        std::unique_ptr<std::vector<CoreLogic::EventManagement::Trigger>> po_actionTriggers_;
        bool visible_;
        bool moves_;
        bool collidable_;
        bool interactable_;
    };
}



#endif //RAYLIBSTARTER_ACTOR_H
