//
// Created by Josi on 07.06.2024.
//

#ifndef HIVE_LIFEBAR_H
#define HIVE_LIFEBAR_H

#include <vector>
#include <memory>
#include "raylib.h"

namespace CoreLogic::UserInterface::HUDElement {

        class LifeBar {
        private:
            std::vector<std::shared_ptr<Texture2D>> maxLifeTextures_;
            std::vector<std::shared_ptr<Texture2D>> currentLifeTextures_;

            Vector2 position_;

        public:
            LifeBar();

            std::shared_ptr<Texture2D> getMaxLifeTexture(int pa_maxLife){return maxLifeTextures_.at(pa_maxLife);};
            std::shared_ptr<Texture2D> getCurrentLifeTexture(int pa_currentLife){return currentLifeTextures_.at(pa_currentLife);};

            Vector2 getPosition(){return position_;};
        };

}

#endif //HIVE_LIFEBAR_H
