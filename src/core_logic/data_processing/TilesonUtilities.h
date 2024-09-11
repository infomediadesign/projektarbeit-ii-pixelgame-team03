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

    struct Line {
        Vector2 p1, p2;
        Line(Vector2 pa_p1, Vector2 pa_p2) : p1(pa_p1), p2(pa_p2) {}
        Line() = default;
    };

    inline bool CheckCollisionLineRec(Line line, Rectangle rec) {
        bool collides = false;
        Vector2 *collisionPoint = new Vector2();
        bool collisionTop = CheckCollisionLines(line.p1, line.p2, {rec.x, rec.y}, {rec.x + rec.width, rec.y}, collisionPoint);
        bool collisionLeft = CheckCollisionLines(line.p1, line.p2, {rec.x,rec.y}, {rec.x, rec.y + rec.height},collisionPoint);
        bool collisionRight = CheckCollisionLines(line.p1, line.p2, {rec.x + rec.width,rec.y}, {rec.x + rec.width, rec.y + rec.height},collisionPoint);
        bool collisionBottom = CheckCollisionLines(line.p1, line.p2, {rec.x,rec.y + rec.height}, {rec.x + rec.width, rec.y + rec.height},collisionPoint);
        if (collisionTop || collisionLeft || collisionRight || collisionBottom) {
            collides = true;
        }
        return collides;
    }
}
#endif //RAYLIBSTARTER_TILESONUTILITIES_H
