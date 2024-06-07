//
// Created by Josi on 07.06.2024.
//

#include <iostream>
#include "Commands.h"

namespace CoreLogic::EventManagement {

   namespace InGameCommand {
       void MoveDownCommand::execute()
       {
           std::cout << "moving Down" << std::endl;
       }

       void MoveUpCommand::execute()
       {
           std::cout << "moving Up" << std::endl;
       }

       void MoveLeftCommand::execute()
       {
           std::cout << "moving Left" << std::endl;
       }

       void MoveRightCommand::execute()
       {
           std::cout << "moving Right" << std::endl;
       }

       void ActionCommand::execute()
       {
           std::cout << "action" << std::endl;
       }

       void DeathAbilityCommand::execute()
       {
           std::cout << "death ability" << std::endl;
       }

       void DisconnectCommand::execute()
       {
           std::cout << "disconnect" << std::endl;
       }

       void InteractCommand::execute()
       {
            std::cout << "interact" << std::endl;
       }

       void HighlightInteractablesCommand::execute()
       {
            std::cout << "highlight interactables" << std::endl;
       }

       void PauseCommand::execute()
       {
            std::cout << "pause" << std::endl;
       }
   }

   namespace MenuCommand
   {

       void CursorDownCommand::execute()
       {

       }

       void CursorUpCommand::execute()
       {

       }

       void CursorLeftCommand::execute()
       {

       }

       void CursorRightCommand::execute()
       {

       }

       void BackCommand::execute()
       {

       }

       void SelectCommand::execute()
       {

       }
   }

}