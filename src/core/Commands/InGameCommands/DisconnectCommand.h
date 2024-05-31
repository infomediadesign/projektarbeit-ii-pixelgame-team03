//
// Created by Josi on 23.05.2024.
//

#ifndef GITKEEP_DISCONNECTCOMMAND_H
#define GITKEEP_DISCONNECTCOMMAND_H
#include "Commands/Command.h"


namespace Command {

    class DisconnectCommand : public Command {
    public:
        void execute() override;
    };

} // Command

#endif //GITKEEP_DISCONNECTCOMMAND_H
