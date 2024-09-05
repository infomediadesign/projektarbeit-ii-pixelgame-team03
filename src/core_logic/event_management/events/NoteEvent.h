//
// Created by keanu on 9/5/2024.
//

#ifndef HIVE_NOTEEVENT_H
#define HIVE_NOTEEVENT_H


#include "InteractionEvent.h"
#include "actors/objects/Note.h"

namespace CoreLogic::EventManagement
{

    class NoteEvent : InteractionEvent
    {
    public:
        NoteEvent(std::shared_ptr<Object::Note> pa_note);
    };

} // CoreLogic
// EventManagement

#endif //HIVE_NOTEEVENT_H
