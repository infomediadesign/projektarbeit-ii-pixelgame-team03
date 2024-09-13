//
// Created by Josi on 03.09.2024.
//

#include "TutorialBox.h"

std::string CoreLogic::EventManagement::Object::TutorialBox::getText()
{
    return text_;
}

CoreLogic::EventManagement::Object::TutorialBox::TutorialBox(Vector2 pa_position, Rectangle pa_hitbox, int pa_id,
        Vector2 pa_size, int pa_elevation, std::string pa_text, int pa_fontSize, int pa_spacing, Vector2 pa_anchor) :
        text_(pa_text), fontSize_(pa_fontSize), spacing_(pa_spacing), anchor_(pa_anchor),
        Actor(pa_position, pa_hitbox, pa_id, CollisionType::WALKABLE, pa_size, false, pa_elevation)
{

}

void CoreLogic::EventManagement::Object::TutorialBox::setText(std::string pa_text)
{
text_ = pa_text;
}

int CoreLogic::EventManagement::Object::TutorialBox::getFontSize()
{
    return fontSize_;
}

void CoreLogic::EventManagement::Object::TutorialBox::setFontSize(int pa_fontSize)
{
fontSize_ = pa_fontSize;
}

int CoreLogic::EventManagement::Object::TutorialBox::getSpacing()
{
    return spacing_;
}

void CoreLogic::EventManagement::Object::TutorialBox::setSpacing(int pa_spacing)
{
spacing_ = pa_spacing;
}

Vector2 CoreLogic::EventManagement::Object::TutorialBox::getAnchor()
{
    return anchor_;
}

void CoreLogic::EventManagement::Object::TutorialBox::setAnchor(Vector2 pa_anchor)
{
anchor_ = pa_anchor;
}
