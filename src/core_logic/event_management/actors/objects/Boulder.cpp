//
// Created by Josi on 03.09.2024.
//

#include "Boulder.h"

int CoreLogic::EventManagement::Object::Boulder::getFallHeight()
{
    if (cliff_ != nullptr)
    {
        return cliff_ -> getFallHeight();
    }else{
        return 0;
    }
}

int CoreLogic::EventManagement::Object::Boulder::getNewElevation()
{
    if (cliff_ != nullptr)
    {
        int currentElevation = cliff_ -> getElevation();
        int fallHeight = cliff_ -> getFallHeight();
        return currentElevation - (fallHeight/2);
    }else{
        return -1;
    }
}

CoreLogic::EventManagement::Object::Boulder::Boulder(Vector2 pa_position, Rectangle pa_hitbox, int pa_id,
        Vector2 pa_size, int pa_elevation) :
        Ability(pa_position, pa_hitbox, pa_id, CollisionType::COLLISION, pa_size, true, pa_elevation, PUSH)
{

}


