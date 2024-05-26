//
// Created by Josi on 23.05.2024.
//

#ifndef GITKEEP_ACTIONCOMMAND_H
#define GITKEEP_ACTIONCOMMAND_H
#include "Commands/Command.h"

namespace Command {

class ActionCommand : public Command::Command {
public:
    void execute() override;
    };

} // Command

#endif //GITKEEP_ACTIONCOMMAND_H
