//
// Created by Josi on 03.09.2024.
//

#include "Note.h"

std::string CoreLogic::EventManagement::Object::Note::getText()
{
    return text_;
}

CoreLogic::EventManagement::Object::Note::Note(Vector2 pa_position, Rectangle pa_hitbox, int pa_id, Vector2 pa_size, int pa_elevation, std::string pa_text) :
        text_(pa_text),
        Interaction(pa_position, pa_hitbox, pa_id, Actor::CollisionType::NONE, pa_size, true, pa_elevation, NOTE)
{

}

void CoreLogic::EventManagement::Object::Note::setText(std::string pa_text)
{
text_ = pa_text;
}
