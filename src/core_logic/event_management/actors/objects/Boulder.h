//
// Created by Josi on 03.09.2024.
//

#ifndef HIVE_BOULDER_H
#define HIVE_BOULDER_H

#include <memory>
#include "Ability.h"
#include "Cliff.h"

namespace CoreLogic::EventManagement::Object
{
    class Boulder : public Ability
    {
    public:
        Boulder(Vector2 pa_position, Rectangle pa_hitbox, int pa_id, Vector2
        pa_size, int pa_elevation);
        int getFallHeight();
        int getNewElevation();
        std::shared_ptr<Cliff> getCliff();
    protected:
        std::shared_ptr<Cliff> cliff_ = nullptr;

    };
}

#endif //HIVE_BOULDER_H
