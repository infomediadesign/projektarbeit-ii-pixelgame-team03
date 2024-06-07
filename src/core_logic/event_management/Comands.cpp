//
// Created by Josi on 07.06.2024.
//

#include <iostream>
#include "Comands.h"

namespace CoreLogic::EventManagement {

   namespace InGameComand {
       void MoveDownComand::execute()
       {
           std::cout << "moving Down" << std::endl;
       }

       void MoveUpComand::execute()
       {
           std::cout << "moving Up" << std::endl;
       }

       void MoveLeftComand::execute()
       {
           std::cout << "moving Left" << std::endl;
       }

       void MoveRightComand::execute()
       {
           std::cout << "moving Right" << std::endl;
       }

       void ActionComand::execute()
       {
           std::cout << "action" << std::endl;
       }

       void DeathAbilityComand::execute()
       {
           std::cout << "death ability" << std::endl;
       }

       void DisconnectComand::execute()
       {
           std::cout << "disconnect" << std::endl;
       }

       void InteractComand::execute()
       {
            std::cout << "interact" << std::endl;
       }

       void HighlightInteractablesComand::execute()
       {
            std::cout << "highlight interactables" << std::endl;
       }

       void PauseComand::execute()
       {
            std::cout << "pause" << std::endl;
       }
   }

   namespace MenuComand
   {

       void CursorDownComand::execute()
       {

       }

       void CursorUpComand::execute()
       {

       }

       void CursorLeftComand::execute()
       {

       }

       void CursorRightComand::execute()
       {

       }

       void BackComand::execute()
       {

       }

       void SelectComand::execute()
       {

       }
   }

}