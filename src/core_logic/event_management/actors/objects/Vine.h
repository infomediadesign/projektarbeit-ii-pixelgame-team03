//
// Created by Josi on 03.09.2024.
//

#ifndef HIVE_VINE_H
#define HIVE_VINE_H

#include "Interaction.h"

namespace CoreLogic::EventManagement::Object
{
    class Vine : public Interaction
    {
    public:
        Vine(Vector2 pa_position, Rectangle pa_hitbox, int pa_id, Vector2 pa_size, int pa_elevation, Vector2 pa_coordinates, int pa_newElevation, int pa_spriteState);

        Vector2 getCoordinates() const;
        void setCoordinates(Vector2 pa_coordinates);

        int getNewElevation() const;
        void setNewElevation(int pa_newElevation);
        void initFrame(int pa_state) {secondarySprite_.shiftFrame(pa_state, primaryDirection_);};
    protected:
        Vector2 coordinates_;
        int newElevation;


    };
}

#endif //HIVE_VINE_H
