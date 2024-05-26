//
// Created by Josi on 23.05.2024.
//

#ifndef GITKEEP_INTERACTCOMMAND_H
#define GITKEEP_INTERACTCOMMAND_H
#include "Commands/Command.h"

namespace Command {

    class InteractCommand : public Command::Command {
    public:
        void execute() override;
    };

} // Command

#endif //GITKEEP_INTERACTCOMMAND_H
