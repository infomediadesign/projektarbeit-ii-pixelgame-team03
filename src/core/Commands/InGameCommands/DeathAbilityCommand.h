//
// Created by Josi on 23.05.2024.
//

#ifndef GITKEEP_DEATHABILITYCOMMAND_H
#define GITKEEP_DEATHABILITYCOMMAND_H
#include "Commands/Command.h"

namespace Command {

    class DeathAbilityCommand : public Command {
    public:
        void execute() override;
    };

} // Command

#endif //GITKEEP_DEATHABILITYCOMMAND_H
