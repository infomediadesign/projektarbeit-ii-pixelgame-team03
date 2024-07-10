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

    void MovableActor::adjustOutOfBounds()
    {
        if (position_.x < 0)
        {
            position_.x = 0;
        }
        if (position_.y < 0)
        {
            position_.y = 0;
        }
        if (position_.x + 32 > 1534)
        {
            position_.x = 1536 - 33;

        }
        if (position_.y +32 > 862)
        {
            position_.y = 864-33;
        }
    }
}