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
        std::vector<std::shared_ptr<Object::Ability>> &abilities = DataProcessing::ActorStorage::getScoutAbilities() ->at(elevation_);
        for (auto &ability : abilities)
        {
            if (ability == nullptr)
            {
                continue;
            }
            if (ability->getElevation() != elevation_)
            {
                throw std::runtime_error("Elevation does not match");
            }

            if (CheckCollisionRecs(hitbox_, ability->getHitbox()))
            {
                setAbility(ability);
                return;
            }

        }
        setAbility(nullptr);
    }

    Scout::Scout(Vector2 pa_position, Rectangle pa_hitbox, int pa_id, Actor::CollisionType pa_collisionType,
            Vector2 pa_size, bool pa_visible, int pa_elevation) :
            Drone(pa_position, pa_hitbox, pa_id, pa_collisionType, pa_size, pa_visible, pa_elevation)
    {
        sprite_ = DataProcessing::SpriteStorage::getSprite(DataProcessing::SpriteStorage::SCOUT_DRONE);
    }
}