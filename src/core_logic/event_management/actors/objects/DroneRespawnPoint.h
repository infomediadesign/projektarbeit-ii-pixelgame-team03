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

        void changeState(DroneRespawnPointState pa_state);
    protected:
        DroneRespawnPointState state_ = UNDISCOVERED;
    };
}

#endif //HIVE_DRONERESPAWNPOINT_H
