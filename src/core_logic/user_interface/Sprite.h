//
// Created by Josi on 09.06.2024.
//

#ifndef HIVE_SPRITE_H
#define HIVE_SPRITE_H

#include <string>
#include "raylib.h"

namespace CoreLogic::UserInterface {

    class Sprite
    {
    public:
        Sprite(std::string pa_path);
        ~Sprite();

    protected:
        std::string path_;
        Texture2D texture_;
    };

}

#endif //HIVE_SPRITE_H
