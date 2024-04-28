//
// Created by Josi on 28.04.2024.
//

#include "qualityOfLife.h"
#include "letterbox.h"
#include "../src/config.h"


namespace game {
    namespace core {
        Letterbox::Letterbox(const RenderTexture2D& pt_canvas) {
            canvas = pt_canvas;
        }

        void Letterbox::calculate(int pa_stage_width_, int pa_stage_height_) {
            if (IsKeyDown(KEY_LEFT_ALT) && IsKeyPressed(KEY_ENTER)) { //Fullscreen logic.
                if (IsWindowFullscreen()) {
                    ToggleFullscreen();
                    SetWindowSize(pa_stage_width_, pa_stage_height_);
                } else {
                    SetWindowSize(GetMonitorWidth(GetCurrentMonitor()), GetMonitorHeight(GetCurrentMonitor()));
                    ToggleFullscreen();
                }
            }
        }

        void Letterbox::draw() {
            ClearBackground(BLACK); // If you want something else than a black void in the background
            // then you can add stuff here.

            renderScale = std::min(GetScreenHeight() / (float) canvas.texture.height, // Calculates how big or small the canvas has to be rendered.
                                   GetScreenWidth()  / (float) canvas.texture.width); // Priority is given to the smaller side.
            renderScale = floorf(renderScale);
            if (renderScale < 1) renderScale = 1; // Ensure that scale is at least 1.
            renderRec.width = canvas.texture.width * renderScale;
            renderRec.height = canvas.texture.height * renderScale;
            renderRec.x = (GetScreenWidth() - renderRec.width) / 2.0f;
            renderRec.y = (GetScreenHeight() - renderRec.height) / 2.0f;
            DrawTexturePro(canvas.texture,
                           Rectangle{0, 0, (float) canvas.texture.width, (float) -canvas.texture.height},
                           renderRec,
                           {}, 0, WHITE);
            if (IsKeyDown(KEY_LEFT_CONTROL) && IsKeyDown(KEY_S)) {
                DrawText(TextFormat("Render scale: %.0f", renderScale), 10, 10, 20, LIGHTGRAY);
            }
        }


    } // core

} // game