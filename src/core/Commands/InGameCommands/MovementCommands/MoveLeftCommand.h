//
// Created by Josi on 22.05.2024.
//

#ifndef GITKEEP_MOVELEFTCOMMAND_H
#define GITKEEP_MOVELEFTCOMMAND_H

#include "Commands/Command.h"
#include <iostream>

namespace Command {

    class MoveLeftCommand : public Command::Command {
    public:
        void execute() override;
    };

} // Command

#endif //GITKEEP_MOVELEFTCOMMAND_H
