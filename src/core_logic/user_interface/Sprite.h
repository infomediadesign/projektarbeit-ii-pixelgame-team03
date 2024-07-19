//
// Created by Josi on 10.07.2024.
//

#ifndef HIVE_SPRITE_H
#define HIVE_SPRITE_H

#include <vector>
#include <string>
#include "raylib.h"

namespace CoreLogic::UserInterface
{
    struct AnimationState
    {
        int row_;
        int steps_;
    };
    enum class Direction
    {
        UP,
        DOWN,
        LEFT,
        RIGHT
    };

    class Sprite
    {

    public:
        Sprite();
        Sprite(std::string pa_path, int pa_frameWidth, int pa_frameHeight, std::vector<std::vector<AnimationState>>
        pa_animationStates);
        void shiftFrame(int pa_stateID, Direction pa_primaryDirection);
        void resetFrame(int pa_stateID);

        Texture2D getTexture(){return texture_;};
        Rectangle getFrame(){return frame_;};

    protected:

        std::vector<std::vector<AnimationState>> animationStates_; // state<direction<animationState>>
        int currentState_ = 0;
        int currentStep_ = 0;

        Direction primaryDirection_ = Direction::RIGHT;

        int frameWidth_ = 24;
        int frameHeight_ = 24;

        std::string path_ = "";
        Texture2D texture_;
        Rectangle frame_;
    };
}



#endif //HIVE_SPRITE_H
