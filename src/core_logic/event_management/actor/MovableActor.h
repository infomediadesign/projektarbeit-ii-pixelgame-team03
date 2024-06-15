//
// Created by Josi on 12.06.2024.
//

#ifndef HIVE_MOVABLEACTOR_H
#define HIVE_MOVABLEACTOR_H

#include "AnimatedActor.h"

namespace CoreLogic::EventManagement::Actors {

        class MovableActor : public AnimatedActor{
        public:
            void update();
            void draw();
        };

}
#endif //HIVE_MOVABLEACTOR_H
