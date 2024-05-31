//
// Created by Josi on 21.05.2024.
//

#ifndef GITKEEP_MOVEUPCOMMAND_H
#define GITKEEP_MOVEUPCOMMAND_H

#include "Commands/Command.h"
#include <iostream>

namespace Command {

    class MoveUpCommand : public Command {
    public:
        void execute() override;
    };

} // Command

#endif //GITKEEP_MOVEUPCOMMAND_H
