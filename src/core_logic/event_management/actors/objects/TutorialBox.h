//
// Created by Josi on 03.09.2024.
//

#ifndef HIVE_TUTORIALBOX_H
#define HIVE_TUTORIALBOX_H

#include "event_management/Actor.h"

namespace CoreLogic::EventManagement::Object
{
    class TutorialBox : public Actor
    {
    public:
        TutorialBox(Vector2 pa_position, Rectangle pa_hitbox, int pa_id, Vector2 pa_size, int pa_elevation, std::string pa_text);

        std::string getText();
        void setText(std::string pa_text);
    protected:
        std::string text_;
    };
}

#endif //HIVE_TUTORIALBOX_H
