//
// Created by Josi on 22.05.2024.
//

#ifndef GITKEEP_ALLCOMMANDS_H
#define GITKEEP_ALLCOMMANDS_H


#include "Command.h"

//inGame commands
#include "InGameCommands/MovementCommands/MoveUpCommand.h"
#include "InGameCommands/MovementCommands/MoveLeftCommand.h"
#include "InGameCommands/MovementCommands/MoveDownCommand.h"
#include "InGameCommands/MovementCommands/MoveRightCommand.h"

#include "InGameCommands/InteractCommand.h"
#include "InGameCommands/ActionCommand.h"
#include "InGameCommands/DisconnectCommand.h"
#include "InGameCommands/DeathAbilityCommand.h"
#include "InGameCommands/PauseCommand.h"
#include "InGameCommands/HighlightInteractablesCommand.h"


//menu commands
#include "MenuCommands/BackCommand.h"
#include "MenuCommands/CursorUpCommand.h"
#include "MenuCommands/CursorDownCommand.h"
#include "MenuCommands/CursorLeftCommand.h"
#include "MenuCommands/CursorRightCommand.h"
#include "MenuCommands/SelectCommand.h"

#endif //GITKEEP_ALLCOMMANDS_H
