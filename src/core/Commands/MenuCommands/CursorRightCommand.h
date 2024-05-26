//
// Created by Josi on 23.05.2024.
//

#ifndef GITKEEP_CURSORRIGHTCOMMAND_H
#define GITKEEP_CURSORRIGHTCOMMAND_H
#include "Commands/Command.h"

namespace Command {

    class CursorRightCommand : public Command::Command {
    public:
        void execute() override;
    };

} // Command

#endif //GITKEEP_CURSORRIGHTCOMMAND_H
