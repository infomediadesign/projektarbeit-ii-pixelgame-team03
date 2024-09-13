//
// Created by Josi on 05.09.2024.
//

#include "Uplink.h"
#include "data_processing/Store.h"

CoreLogic::EventManagement::Object::Uplink::Uplink(Vector2 pa_position, Rectangle pa_hitbox, int pa_id, Vector2 pa_size,
        int pa_elevation) :
        Interaction(pa_position, pa_hitbox, pa_id, Actor::CollisionType::COLLISION, pa_size, false, pa_elevation, UPLINK)
{
    sprite_ = DataProcessing::SpriteStorage::getSprite(DataProcessing::SpriteStorage::UPLINK);
}
