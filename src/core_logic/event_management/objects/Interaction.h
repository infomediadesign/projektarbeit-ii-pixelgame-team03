//
// Created by Josi on 02.09.2024.
//

#ifndef HIVE_INTERACTION_H
#define HIVE_INTERACTION_H

#include "Actor.h"

namespace CoreLogic::EventManagement::Object
{
    class Interaction : public Actor
    {
    public:
        enum InteractionType
        {
            CLIMBING, NOTE, CHECKPOINT
        };

        InteractionType getType() const;

    protected:
        InteractionType type_;
    };
}

#endif //HIVE_INTERACTION_H
