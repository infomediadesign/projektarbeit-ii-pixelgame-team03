//
// Created by keanu on 8/30/2024.
//

#include <stdexcept>
#include "FallingEvent.h"
#include "actors/MovableActor.h"
#include "Store.h"
#include "EventHandler.h"
#include "FallingBarrelEvent.h"
#include "FallingBoulderEvent.h"


CoreLogic::EventManagement::FallingEvent::~FallingEvent()
{
    po_mainActor_ -> setVisible(false);
    po_mainActor_ -> setCollisionType(Actor::CollisionType::NONE);
}

void CoreLogic::EventManagement::FallingEvent::update()
{
    if (!broken_)
    {
        fall();
    } else {
        destroy();
    }
}

CoreLogic::EventManagement::FallingEvent::FallingEvent(int pa_actorID): Event(FALLING)
{
    std::vector<Pushable> pushables = CoreLogic::DataProcessing::ActorStorage::getPushables();
    for (auto &pushable: pushables)
    {
        if (pushable -> getId() == pa_actorID)
        {
            po_mainActor_ = pushable;
            break;
        }
    }
    if (po_mainActor_ == nullptr)
    {
        throw std::runtime_error("Actor not found");
    }

}

void CoreLogic::EventManagement::FallingEvent::fall()
{
    if (ticks_ != 0 && ticks_ % 5 == 0)
    {
        Vector2 newPosition = po_mainActor_ -> getPosition();
        int tileSize = CoreLogic::DataProcessing::tileSize;
        newPosition.y += (0.5 * tileSize);
        std::dynamic_pointer_cast<CoreLogic::EventManagement::Actors::MovableActor>(po_mainActor_)
                -> setPosition(newPosition);
        fallenHeight_ += 0.5;
    }
    ticks_++;

    if (fallenHeight_ >= fallHeight_)
    {
        broken_ = true;
        ticks_ = 0;
    }
}

/*void CoreLogic::EventManagement::FallingEvent::explode()
{
    if (ticks_ == 0)
    {
        *//**
         * @todo: Code Drawing for different frame sizes
         *//*

        auto& eventHandler = EventHandler::getInstance();
        Rectangle explosionRadius;
        int tileSize = CoreLogic::DataProcessing::tileSize;
        explosionRadius.x = po_mainActor_ -> getPosition().x - (tileSize * 2);
        explosionRadius.y = po_mainActor_ -> getPosition().y - (tileSize * 2);
        explosionRadius.width = po_mainActor_ -> getSize().x + (tileSize * 5);
        explosionRadius.height = po_mainActor_ -> getSize().y + (tileSize * 5);
        std::vector<std::shared_ptr<Enemy>> enemies = CoreLogic::DataProcessing::ActorStorage::getEnemies();
        for (std::shared_ptr<Enemy> enemy: enemies)
        {
            if (enemy == nullptr)
            {
                continue;
            }
            if (CheckCollisionRecs(explosionRadius, enemy -> getHitbox()))
            {
                eventHandler.handleEvents({DISCONNECT}, enemy -> getId());
            }
        }
    }
    if (ticks_ % 5 == 0)
    {
        po_mainActor_ -> shiftFrame(*//**@Attention: set to Breaking frames*//*);
    }
    if (ticks_ >= 60)
    {
        throw true;
    }
    ticks_++;
}*/

/*
void CoreLogic::EventManagement::FallingEvent::crumble()
{
    if (ticks_ == 0)
    {
        auto& eventHandler = EventHandler::getInstance();
        Rectangle hitbox = po_mainActor_ -> getHitbox();
        std::vector<std::shared_ptr<Enemy>> enemies = CoreLogic::DataProcessing::ActorStorage::getEnemies();
        for (std::shared_ptr<Enemy> enemy: enemies)
        {
            if (enemy == nullptr)
            {
                continue;
            }
            if (CheckCollisionRecs(hitbox, enemy -> getHitbox()))
            {
                eventHandler.handleEvents({DISCONNECT}, enemy -> getId());
            }
        }
    }
    if (ticks_ % 5 == 0)
    {
        po_mainActor_ -> shiftFrame(*/
/**@Attention: set to Breaking frames*//*
);
    }
    if (ticks_ >= 20)
    {
        throw true;
    }
    ticks_++;
}
*/

std::unique_ptr<CoreLogic::EventManagement::FallingEvent> CoreLogic::EventManagement::FallingEvent::transform()
{
    if (std::dynamic_pointer_cast<Ability>(po_mainActor_) -> getAbilityType() == AbilityType::PUSHABLE)
    {
        return std::make_unique<FallingBoulderEvent>(std::dynamic_pointer_cast<Pushable>(po_mainActor_));
    } else if (std::dynamic_pointer_cast<Ability>(po_mainActor_) -> getAbilityType() == AbilityType::BARREL) {
        return std::make_unique<FallingBarrelEvent>(std::dynamic_pointer_cast<Barrel>(po_mainActor_));
    }
}
