//
// Created by Josi on 07.06.2024.
//

#include "LifeBar.h"

namespace CoreLogic::UserInterface::HUDElement {
        LifeBar::LifeBar() {
            maxLifeTextures_.push_back(std::make_shared<Texture2D>(LoadTexture("assets/graphics/hive_ARTI_test-life-bar-max-life-3_2024-06-07.png")));
            currentLifeTextures_.push_back(std::make_shared<Texture2D>(LoadTexture("assets/graphics/hive_ARTI_test-life-bar-current-life-3_2024-06-07.png")));

            position_ = {10, 10};
        }

    } // UserInterface
} // CoreLogic