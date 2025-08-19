//
// Created by Josi on 19.09.2024.
//

#ifndef HIVE_CAMERAPAN_H
#define HIVE_CAMERAPAN_H

#include "event_management/Actor.h"

namespace CoreLogic::EventManagement::Object
{
    class CameraPan : public Actor
    {
    public:
        CameraPan(Vector2 pa_position, Rectangle pa_hitbox, int pa_id, Vector2 pa_size, int pa_elevation, Vector2
        pa_destination, int pa_panTicks, int pa_restingTicks);

        Vector2 getDestination() const;
        void setDestination(Vector2 pa_destination);

        int getPanTicks() const;
        void setPanTicks(int pa_panTicks);

        int getRestingTicks() const;
        void setRestingTicks(int pa_restingTicks);

        bool getPlayed() const;
        void setPlayed(bool pa_played);

    protected:
        Vector2 destination_;

        int panTicks_;
        int restingTicks_;

        bool played_ = false;
    };
}

#endif //HIVE_CAMERAPAN_H
