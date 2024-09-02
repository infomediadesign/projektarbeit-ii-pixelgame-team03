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
