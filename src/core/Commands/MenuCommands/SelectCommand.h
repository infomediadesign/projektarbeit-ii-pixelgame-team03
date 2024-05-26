//
// Created by Josi on 23.05.2024.
//

#ifndef GITKEEP_SELECTCOMMAND_H
#define GITKEEP_SELECTCOMMAND_H
#include "Commands/Command.h"

namespace Command {

    class SelectCommand : public Command::Command {
    public:
        void execute() override;
    };

} // Command

#endif //GITKEEP_SELECTCOMMAND_H
