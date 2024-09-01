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
        if (position_.x + size_.x > 1534)
        {
            position_.x = 1536 - (size_.x + 1);

        }
        if (position_.y +size_.y > 862)
        {
            position_.y = 864 - (size_.y + 1);
        }
    }



    void MovableActor::setPosition(Vector2 pa_position)
    {
        position_ = pa_position;
        updateHitbox();
        adjustOutOfBounds();
    }
}