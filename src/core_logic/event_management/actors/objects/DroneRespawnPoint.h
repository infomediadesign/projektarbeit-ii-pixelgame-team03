//
// Created by Josi on 03.09.2024.
//

#ifndef HIVE_DRONERESPAWNPOINT_H
#define HIVE_DRONERESPAWNPOINT_H

#include "Interaction.h"

namespace CoreLogic::EventManagement::Object
{
    class DroneRespawnPoint : public Interaction
    {
    public:
        enum DroneRespawnPointState {
            UNDISCOVERED,
            DISCOVERED,
            ACTIVATED
        };

        DroneRespawnPoint(Vector2 pa_position, Rectangle pa_hitbox, int pa_id, Vector2 pa_size,  int pa_elevation);

        [[nodiscard]] DroneRespawnPointState getRespawnState() const;
        void changeState(DroneRespawnPointState pa_state);

    protected:

        DroneRespawnPointState state_ = UNDISCOVERED;
    };
}

#endif //HIVE_DRONERESPAWNPOINT_H
