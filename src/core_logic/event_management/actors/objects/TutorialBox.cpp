//
// Created by Josi on 03.09.2024.
//

#include "TutorialBox.h"

std::string CoreLogic::EventManagement::Object::TutorialBox::getText()
{
    return text_;
}

CoreLogic::EventManagement::Object::TutorialBox::TutorialBox(Vector2 pa_position, Rectangle pa_hitbox, int pa_id,
        Vector2 pa_size, int pa_elevation, std::string pa_text) :
        text_(pa_text),
        Actor(pa_position, pa_hitbox, pa_id, CollisionType::WALKABLE, pa_size, false, pa_elevation)
{

}

void CoreLogic::EventManagement::Object::TutorialBox::setText(std::string pa_text)
{
text_ = pa_text;
}
