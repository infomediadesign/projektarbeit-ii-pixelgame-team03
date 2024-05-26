//
// Created by Josi on 23.05.2024.
//

#ifndef GITKEEP_PAUSECOMMAND_H
#define GITKEEP_PAUSECOMMAND_H
#include "Commands/Command.h"

namespace Command {

    class PauseCommand : public Command::Command {
    public:
        void execute() override;
    };

} // Command

#endif //GITKEEP_PAUSECOMMAND_H
