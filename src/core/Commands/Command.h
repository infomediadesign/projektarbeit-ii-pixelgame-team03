//
// Created by Josi on 21.05.2024.
//

#ifndef GITKEEP_COMMAND_H
#define GITKEEP_COMMAND_H

#include "raylib.h"

namespace Command {

    class Command {
    public:
        virtual void execute() = 0;
    };

} // Command

#endif //GITKEEP_COMMAND_H
