//
// Created by Josi on 23.05.2024.
//

#ifndef GITKEEP_CURSORDOWNCOMMAND_H
#define GITKEEP_CURSORDOWNCOMMAND_H
#include "Commands/Command.h"

namespace Command {

    class CursorDownCommand : public Command::Command {
    public:
        void execute() override;
    };

} // Command

#endif //GITKEEP_CURSORDOWNCOMMAND_H
