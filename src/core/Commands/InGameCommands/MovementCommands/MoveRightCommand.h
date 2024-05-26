//
// Created by Josi on 22.05.2024.
//

#ifndef GITKEEP_MOVERIGHTCOMMAND_H
#define GITKEEP_MOVERIGHTCOMMAND_H

#include "Commands/Command.h"
#include <iostream>

namespace Command {

    class MoveRightCommand : public Command::Command {
    public:
        void execute() override;
    };

} // Command

#endif //GITKEEP_MOVERIGHTCOMMAND_H
