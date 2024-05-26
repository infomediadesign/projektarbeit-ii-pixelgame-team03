//
// Created by Josi on 23.05.2024.
//

#ifndef GITKEEP_CURSORLEFTCOMMAND_H
#define GITKEEP_CURSORLEFTCOMMAND_H
#include "Commands/Command.h"

namespace Command {

    class CursorLeftCommand : public Command::Command {
    public:
        void execute() override;
    };

} // Command

#endif //GITKEEP_CURSORLEFTCOMMAND_H
