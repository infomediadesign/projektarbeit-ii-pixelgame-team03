//
// Created by keanu on 6/10/2024.
//

#include "Event.h"


CoreLogic::EventManagement::EventEnum Event::getID() {return id_;}

Event::Event(CoreLogic::EventManagement::EventEnum pa_ID): id_(pa_ID){}
