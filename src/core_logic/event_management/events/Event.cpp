//
// Created by keanu on 6/10/2024.
//

#include "Event.h"


CoreLogic::EventManagement::EventEnum CoreLogic::EventManagement::Event::getID() {return id_;}

CoreLogic::EventManagement::Event::Event(CoreLogic::EventManagement::EventEnum pa_ID): id_(pa_ID){}
