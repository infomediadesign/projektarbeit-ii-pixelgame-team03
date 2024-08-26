//
// Created by Josi on 12.06.2024.
//

#include <memory>
#include "Scout.h"
#include "Store.h"

namespace CoreLogic::EventManagement::Actors
{

    void Scout::checkAbility()
    {
        /**
         * @Pseudo_Code: getScoutAbilities() not yet existing
         */
        std::vector<std::shared_ptr<Ability>> &abilities = DataProcessing::ActorStorage::getScoutAbilities();
        for (auto &ability : abilities)
        {
            if (ability == nullptr)
            {
                continue;
            }
            if (ability->getElevation() == elevation_)
            {
                if (CheckCollisionRecs(hitbox_, ability->getHitbox()))
                {
                    setAbility(ability);
                    return;
                }
            }
        }
        setAbility(nullptr);
    }
}