//
// Created by Josi on 03.09.2024.
//

#ifndef HIVE_LEVELSWITCH_H
#define HIVE_LEVELSWITCH_H

#include "event_management/Actor.h"

namespace CoreLogic::EventManagement::Object
{
    class LevelSwitch : public Actor
    {
    public:
        LevelSwitch(Vector2 pa_position, Rectangle pa_hitbox, int pa_id, Vector2 pa_size, int pa_elevation, int pa_newLevelID, Vector2 pa_switchCoordinates, int pa_switchElevation);

        int getNewLevelID() const;
        void setNewLevelID(int pa_newLevelID);
    protected:
        int newLevelID_;
        Vector2 switchCoordinates_;
        int switchElevation_;
    };
}

#endif //HIVE_LEVELSWITCH_H
