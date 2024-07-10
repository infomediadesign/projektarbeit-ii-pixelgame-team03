//
// Created by Josi on 12.06.2024.
//

#include "MovableActor.h"

namespace CoreLogic::EventManagement::Actors {

    void MovableActor::updateHitbox()
    {
        hitbox_.x = position_.x;
        hitbox_.y = position_.y;
    }
}