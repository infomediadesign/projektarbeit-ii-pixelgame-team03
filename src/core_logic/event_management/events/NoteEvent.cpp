//
// Created by keanu on 9/5/2024.
//

#include "NoteEvent.h"
#include "SoundHandler.h"


namespace CoreLogic::EventManagement
{
    NoteEvent::NoteEvent(std::shared_ptr<Object::Note> pa_note) : InteractionEvent(NOTE)
    {
        auto &soundHandler = CoreLogic::EventManagement::SoundHandler::getInstance();
        soundHandler.playSound(SoundHandler::NOTE);
        pa_note->setVisible(true);
        CoreLogic::DataProcessing::ActorStorage::setActiveNote(pa_note);
        CoreLogic::DataProcessing::StateMachine::changeState(DataProcessing::NOTE);
    } // CoreLogic
}
// EventManagement