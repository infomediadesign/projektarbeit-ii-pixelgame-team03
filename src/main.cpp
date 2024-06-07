#include <cstdlib>
#include <algorithm>
#include <cmath>
#include <string>

#include "raylib.h"
#include "tileson.h"

#include "config.h"
#include "staging/Game.h"
#include "Game.h"


int main() {

    Staging::Game game(GameSpace::Config::Def_ScreenWidth, GameSpace::Config::Def_ScreenHeight,
                                  GameSpace::Config::Def_TargetFPS, GameSpace::Config::Def_WindowFlags,
                                  GameSpace::Config::Def_ExitKey,
                                  GameSpace::Config::Def_Audio, GameSpace::Config::Def_FullScreen,
                                  GameSpace::Config::PROJECT_NAME);

    game.run();

    /*// Raylib initialization
    // Project name, screen size, fullscreen mode etc. can be specified in the config.h.in file
    SetConfigFlags(FLAG_WINDOW_RESIZABLE | FLAG_VSYNC_HINT);
    InitWindow(GameSpace::ScreenWidth, GameSpace::ScreenHeight, GameSpace::PROJECT_NAME);
    SetTargetFPS(60);

#ifdef GAME_START_FULLSCREEN
    ToggleFullscreen();
#endif

    // Your own initialization code here
    // ...
    // ...
    Texture2D myTexture = LoadTexture("assets/graphics/backgrounds/testBackTiledFull.png");
    Texture2D Sprite = LoadTexture("assets/graphics/testSprite32.png");
    tson::Tileson tileson;
    auto MapPtr = tileson.parse("assets/data/tilemap.tmj");
    tson::Map &Map = *MapPtr;

    RenderTexture2D canvas = LoadRenderTexture(1536, 864);
    float renderScale{}; // this and the line below are relevant to drawing later.
    Rectangle renderRec{};

    Camera2D camera_ = { 0 };
    camera_.target = (Vector2){ 0, 0 };
    camera_.offset = (Vector2){ 0, 0 };
    camera_.rotation = 0.0f;
    camera_.zoom = 1.0f;

    // Main GameSpace loop
    while (!WindowShouldClose()) // Detect window close button or ESC key
    {
        if (IsKeyDown(KEY_LEFT_ALT) && IsKeyPressed(KEY_ENTER)) { //Fullscreen logic.
            if (IsWindowFullscreen()) {
                ToggleFullscreen();
                SetWindowSize(GameSpace::ScreenWidth,GameSpace::ScreenHeight);
            } else {
                SetWindowSize(GetMonitorWidth(GetCurrentMonitor()), GetMonitorHeight(GetCurrentMonitor()));
                ToggleFullscreen();
            }
        }
        // Updates that are made by frame are coded here
        // This is where YOUR logic code should go
        // ...
        // ...



        if (IsKeyDown(KEY_SPACE))
        {
            float scrW = GetScreenWidth();
            float scrH = GetScreenHeight();
            float camO = camera_.offset.x;
            float camH = camera_.offset.y;
            float spritePosX = (scrW / 2) + ((camO * (-1))-(Sprite.width/2));
            float spritePosY = (scrH / 2) + ((camH * (-1))-Sprite.height/2);
        }

        float spritePosX = (960 / 2) + ((camera_.offset.x * (-1))-(Sprite.width/2));
        float spritePosY = (540 / 2) + ((camera_.offset.y * (-1))-Sprite.height/2);

        if (IsKeyDown(KEY_W))
        {
            camera_.offset.y += 1;
        } else if (IsKeyDown(KEY_S)) {
            camera_.offset.y -= 1;
        }
        if (IsKeyDown(KEY_A))
        {
            camera_.offset.x += 1;
        } else if (IsKeyDown(KEY_D))
        {
            camera_.offset.x -= 1;
        }

        if (IsWindowFullscreen()){
            camera_.offset.x *=2;
            camera_.offset.y *=2;
        }




        BeginDrawing();
        // You can draw on the screen between BeginDrawing() and EndDrawing()
        // For the letterbox we draw on canvas instad
        BeginTextureMode(canvas);
        { //Within this block is where we draw our app to the canvas and YOUR code goes.
            ClearBackground(WHITE);
            DrawText("Hello, world!", 10, 10, 30, LIGHTGRAY);
            DrawTexture(myTexture, 0, 0, WHITE);
            DrawTexture(Sprite, spritePosX, spritePosY, WHITE);
        }
        EndTextureMode();
        //The following lines put the canvas in the middle of the window and have the negative as black
        ClearBackground(BLACK); // If you want something else than a black void in the background
        // then you can add stuff here.




        *//*renderScale = std::min(GetScreenHeight() / (float) canvas.texture.height, // Calculates how big or small the canvas has to be rendered.
                               GetScreenWidth()  / (float) canvas.texture.width); // Priority is given to the smaller side.
        renderScale = floorf(renderScale);
        if (renderScale < 1) renderScale = 1; // Ensure that scale is at least 1.
        renderRec.width = canvas.texture.width * renderScale;
        renderRec.height = canvas.texture.height * renderScale;
        renderRec.x = (GetScreenWidth() - renderRec.width) / 2.0f;
        renderRec.y = (GetScreenHeight() - renderRec.height) / 2.0f;*//*
        if (GetScreenWidth() > 960)
        {
            renderRec.width = 1536*2;
            renderRec.height = 864*2;
            renderRec.x = 0;
            renderRec.y = 0;
        } else {
            renderRec.width = 1536;
            renderRec.height = 864;
            renderRec.x = 0;
            renderRec.y = 0;
        }

        std::string offsetX = std::to_string(camera_.offset.x);
        std::string offsetY = std::to_string(camera_.offset.y);
        std::string scrHeight = std::to_string(GetScreenHeight());
        std::string scrWidth = std::to_string(GetScreenWidth());
        std::string monitorHeight = std::to_string(GetMonitorHeight(GetCurrentMonitor()));
        std::string monitorWidth = std::to_string(GetMonitorWidth(GetCurrentMonitor()));

        BeginMode2D(camera_);

        DrawTexturePro(canvas.texture,
                       Rectangle{0, 0, (float) canvas.texture.width, (float) -canvas.texture.height},
                       renderRec,
                       {}, 0, WHITE);

        //draw Text with Camera offsets "offsetX" and "offsetY" into the relative Position of left upper corner of the camera_
        DrawText(TextFormat("offsetX: %s", offsetX.c_str()), (camera_.offset.x)*(-1)+10, (camera_.offset.y)*(-1)+10, 20, BLACK);
        DrawText(TextFormat("offsetY: %s", offsetY.c_str()), (camera_.offset.x)*(-1) +10, (camera_.offset.y)*(-1)+30, 20, BLACK);
        DrawText(TextFormat("screenHeight: %s", scrHeight.c_str()), (camera_.offset.x)*(-1)+10, (camera_.offset.y)*(-1)+50, 20, BLACK);
        DrawText(TextFormat("screenWidth: %s", scrWidth.c_str()), (camera_.offset.x)*(-1)+10, (camera_.offset.y)*(-1)+70, 20, BLACK);
        DrawText(TextFormat("monitorHeight: %s", monitorHeight.c_str()), (camera_.offset.x)*(-1)+10, (camera_.offset.y)*(-1)+90, 20, BLACK);
        DrawText(TextFormat("monitorWidth: %s", monitorWidth.c_str()), (camera_.offset.x)*(-1)+10, (camera_.offset.y)*(-1)+110, 20, BLACK);

        EndMode2D();
        *//*if (IsKeyDown(KEY_LEFT_CONTROL) && IsKeyDown(KEY_S)) {
            DrawText(TextFormat("Render scale: %.0f", renderScale), 10, 10, 20, LIGHTGRAY);
        }*//*
        EndDrawing();
        if (IsWindowFullscreen())
        {
            camera_.offset.x /=2;
            camera_.offset.y /=2;
        }
    } // Main GameSpace loop end

    // De-initialization here
    // ...
    // ...
    UnloadTexture(myTexture);

    // Close window and OpenGL context
    CloseWindow();*/
    CloseWindow();
    return EXIT_SUCCESS;
}
