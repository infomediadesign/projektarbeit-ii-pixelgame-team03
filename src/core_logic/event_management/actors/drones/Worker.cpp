//
// Created by Josi on 12.06.2024.
//

#include "Worker.h"
#include "Store.h"

namespace CoreLogic::EventManagement::Actors
{

    void Worker::checkAbility()
    {
        Rectangle extensionRec = hitbox_;
        switch (primaryDirection_)
        {
            case UserInterface::Direction::RIGHT:
                extensionRec.x += DataProcessing::tileSize / 2;
                break;
            case UserInterface::Direction::LEFT:
                extensionRec.x -= DataProcessing::tileSize / 2;
                break;
            case UserInterface::Direction::UP:
                extensionRec.y -= DataProcessing::tileSize / 2;
                break;
            case UserInterface::Direction::DOWN:
                extensionRec.y += DataProcessing::tileSize / 2;
                break;
        }
        /**
        * @Pseudo_Code: getWorkerAbilities() not yet existing
        */
        std::vector<std::shared_ptr<Object::Ability>> &abilities = DataProcessing::ActorStorage::getWorkerAbilities()->at(elevation_);
        for (auto &ability : abilities)
        {
            if (ability == nullptr)
            {
                continue;
            }
            if (ability->getCollisionType() == CollisionType::NONE && !ability->getVisible())
            {
                continue;
            }
            if (ability->getElevation() != elevation_)
            {
                throw std::runtime_error("Elevation does not match");
            }
            if (CheckCollisionRecs(extensionRec, ability->getHitbox()))
            {
                setAbility(ability);
                return;
            }

        }
        setAbility(nullptr);
    }

    Worker::Worker(Vector2 pa_position, Rectangle pa_hitbox, int pa_id,
            Vector2 pa_size, int pa_elevation) :
            Drone(pa_position, pa_hitbox, pa_id,  pa_size, pa_elevation)
    {
        sprite_ = DataProcessing::SpriteStorage::getSprite(DataProcessing::SpriteStorage::WORKER_DRONE);
    }



    void Worker::shiftFrame(int pa_frameShift)
    {
        if (currentDroneState_ != ABILITY && pa_frameShift == 1)
        {
            return;
        }
        sprite_.shiftFrame(pa_frameShift,primaryDirection_);
    }

}