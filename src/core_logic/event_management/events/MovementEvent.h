//
// Created by keanu on 6/10/2024.
//

#ifndef HIVE_MOVEMENTEVENT_H
#define HIVE_MOVEMENTEVENT_H


#include "Event.h"

class MovementEvent: public Event
{
public:
    void update() override;
    void startMove(EventEnum pa_Event);
private:
    void checkStillPressed();
    void updateAxis();
};


#endif //HIVE_MOVEMENTEVENT_H
