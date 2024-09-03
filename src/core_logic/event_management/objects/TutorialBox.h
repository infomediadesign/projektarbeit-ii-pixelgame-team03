//
// Created by Josi on 03.09.2024.
//

#ifndef HIVE_TUTORIALBOX_H
#define HIVE_TUTORIALBOX_H

#include "Actor.h"

namespace CoreLogic::EventManagement::Object
{
    class TutorialBox : public Actor
    {
    public:
        std::string getText();
    protected:
        std::string text_;
    };
}

#endif //HIVE_TUTORIALBOX_H
