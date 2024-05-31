//
// Created by Josi on 23.05.2024.
//

#ifndef GITKEEP_BACKCOMMAND_H
#define GITKEEP_BACKCOMMAND_H
#include "Commands/Command.h"

namespace Command {

    class BackCommand : public Command {
    public:
        void execute() override;
    };

} // Command

#endif //GITKEEP_BACKCOMMAND_H
