//
// Created by Josi on 03.09.2024.
//

#ifndef HIVE_NOTE_H
#define HIVE_NOTE_H

#include "Interaction.h"

namespace CoreLogic::EventManagement::Object
{
    class Note : public Interaction
    {
    public:
        Note(Vector2 pa_position, Rectangle pa_hitbox, int pa_id, Vector2 pa_size, int pa_elevation, std::string pa_text);

        std::string getText();
        void setText(std::string pa_text);
    protected:
        std::string text_;

    };
}

#endif //HIVE_NOTE_H
