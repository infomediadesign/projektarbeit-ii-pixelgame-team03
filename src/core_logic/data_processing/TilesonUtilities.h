//
// Created by keanu on 5/22/2024.
//

#ifndef RAYLIBSTARTER_TILESONUTILITIES_H
#define RAYLIBSTARTER_TILESONUTILITIES_H


#include "../../tileson.h"
#include "raylib.h"

namespace CoreLogic::DataProcessing {
    inline tson::Tileson tileson;

    inline Vector2 coordinatesToTile(Vector2 pa_coordinates) {
        return {floorf(pa_coordinates.x / 24), floorf(pa_coordinates.y / 24)};
    }
}
#endif //RAYLIBSTARTER_TILESONUTILITIES_H
