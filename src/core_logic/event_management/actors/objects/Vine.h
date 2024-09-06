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
        Vine(Vector2 pa_position, Rectangle pa_hitbox, int pa_id, Vector2 pa_size, int pa_elevation, Vector2 pa_coordinates);

        Vector2 getCoordinates() const;
        void setCoordinates(Vector2 pa_coordinates);

        int getNewElevation() const;
        void setNewElevation(int pa_newElevation);
    protected:
        Vector2 coordinates_;
        int elevationChange_;
        int newElevation;


    };
}

#endif //HIVE_VINE_H
