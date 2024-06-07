//
// Created by Josi on 07.06.2024.
//

#ifndef HIVE_HUDELEMENTS_H
#define HIVE_HUDELEMENTS_H

#include "user_interface/hud_elements/LifeBar.h"

namespace CoreLogic::UserInterface::HUDElement {

            class HUDElements {
            private:
                LifeBar lifeBar_;
                std::vector<std::shared_ptr<Texture2D>> elements_;
            public:
                std::vector<std::shared_ptr<Texture2D>> getElements(){return elements_;};

            };

}

#endif //HIVE_HUDELEMENTS_H
