//
// Created by Josi on 22.05.2024.
//

#ifndef GITKEEP_MOVEDOWNCOMMAND_H
#define GITKEEP_MOVEDOWNCOMMAND_H

#include "Commands/Command.h"
#include "actor.h"
#include <iostream>

namespace Command {

    class MoveDownCommand : public Command::Command {
    public:
        void execute() override;

    };

} // Command

#endif //GITKEEP_MOVEDOWNCOMMAND_H
