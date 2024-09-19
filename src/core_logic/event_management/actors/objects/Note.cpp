//
// Created by Josi on 03.09.2024.
//

#include "Note.h"
#include "data_processing/Store.h"

std::string CoreLogic::EventManagement::Object::Note::getText()
{
    return text_;
}

CoreLogic::EventManagement::Object::Note::Note(Vector2 pa_position, Rectangle pa_hitbox, int pa_id, Vector2 pa_size, int pa_elevation, std::string pa_text) :
        text_(pa_text),
        Interaction(pa_position, pa_hitbox, pa_id, Actor::CollisionType::NONE, pa_size, true, pa_elevation, NOTE)
{
    sprite_ = DataProcessing::SpriteStorage::getSprite(DataProcessing::SpriteStorage::NOTE);
}

void CoreLogic::EventManagement::Object::Note::setText(std::string pa_text)
{
text_ = pa_text;
}



void CoreLogic::EventManagement::Object::Note::discover()
{
    discovered_ = true;
}

void CoreLogic::EventManagement::Object::Note::draw()
{
    if (!discovered_)
    {
        Rectangle dest = {
                hitbox_.x + sprite_.getRelativePosition().x, hitbox_.y + sprite_.getRelativePosition().y,
                sprite_.getFrame().width, sprite_.getFrame().height
        };

        DrawTexturePro(sprite_.getTexture(), sprite_.getFrame(), dest, {0, 0}, 0, WHITE);
    }

    if (glowing_)
    {
        Rectangle dest = {hitbox_.x + secondarySprite_.getRelativePosition().x, hitbox_.y + secondarySprite_.getRelativePosition().y,
                          secondarySprite_.getFrame().width, secondarySprite_.getFrame().height};

        DrawTexturePro(secondarySprite_.getTexture(), secondarySprite_.getFrame(), dest, {0, 0}, 0, WHITE);

    }
}
