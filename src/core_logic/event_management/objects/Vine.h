//
// Created by Josi on 03.09.2024.
//

#ifndef HIVE_VINE_H
#define HIVE_VINE_H

#include "Actor.h"

namespace CoreLogic::EventManagement::Object
{
    class Vine : public Actor
    {
public:
        Vector2 getCoordinates() const;
        int getElevationChange() const;

    protected:
        Vector2 coordinates_;
        int elevationChange_;


    };
}

#endif //HIVE_VINE_H
