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
        TutorialBox(Vector2 pa_position, Rectangle pa_hitbox, int pa_id, Vector2 pa_size, int pa_elevation, std::string pa_text, int pa_fontSize, int pa_spacing, Vector2 pa_anchor);

        std::string getText();
        void setText(std::string pa_text);

        int getFontSize();
        void setFontSize(int pa_fontSize);

        int getSpacing();
        void setSpacing(int pa_spacing);

        Vector2 getAnchor();
        void setAnchor(Vector2 pa_anchor);
    protected:
        std::string text_;
        int fontSize_ = 17;
        int spacing_ = 0;
        Vector2 anchor_;
    };
}

#endif //HIVE_TUTORIALBOX_H
