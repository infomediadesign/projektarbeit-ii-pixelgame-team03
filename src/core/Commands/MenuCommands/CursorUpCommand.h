//
// Created by Josi on 23.05.2024.
//

#ifndef GITKEEP_CURSORUPCOMMAND_H
#define GITKEEP_CURSORUPCOMMAND_H
#include "Commands/Command.h"

namespace Command {

    class CursorUpCommand : public Command::Command {
    public:
        void execute() override;
    };

} // Command

#endif //GITKEEP_CURSORUPCOMMAND_H
