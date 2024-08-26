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
        std::vector<std::shared_ptr<Ability>> &abilities = DataProcessing::ActorStorage::getWorkerAbilities();
        for (auto &ability : abilities)
        {
            if (ability == nullptr)
            {
                continue;
            }
            if (ability->getElevation() == elevation_)
            {
                if (CheckCollisionRecs(extensionRec, ability->getHitbox()))
                {
                    setAbility(ability);
                    return;
                }
            }
        }
        setAbility(nullptr);
    }
}