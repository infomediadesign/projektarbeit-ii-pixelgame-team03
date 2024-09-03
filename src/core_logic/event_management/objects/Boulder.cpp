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
