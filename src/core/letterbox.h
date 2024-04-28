
#ifndef RAYLIBSTARTER_LETTERBOX_H
#define RAYLIBSTARTER_LETTERBOX_H

#include "raylib.h"

namespace game {
    namespace core {

        class Letterbox {
        public:
            Letterbox(const RenderTexture2D&);
            void draw();
            void calculate(int pa_stage_width_, int pa_stage_height_);

            protected:
            float renderScale{}; // this and the line below are relevant to drawing later.
            Rectangle renderRec{};
            RenderTexture2D canvas;
        };

    } // core
} // game

#endif //RAYLIBSTARTER_LETTERBOX_H
