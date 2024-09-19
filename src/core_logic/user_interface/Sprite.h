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
        int pxRow_; //it has to be measured in px to account for different sized states
        int width_; // same thing here
        int height_; // and here
        int steps_;
        Vector2 relativePosition_;
    };
    enum class Direction
    {
        UP = 0,
        DOWN = 1,
        LEFT = 2,
        RIGHT = 3
    };

    class Sprite
    {

    public:
        Sprite();
        Sprite(std::string pa_path, std::vector<std::vector<AnimationState>>
        pa_animationStates);
        void shiftFrame(int pa_stateID, Direction pa_primaryDirection);
        void shiftFrame(int pa_stateID);
        void resetFrame(int pa_stateID);

        int getFrameAmount(int pa_stateID, Direction pa_primaryDirection);
        int getFrameAmount(int pa_stateID);
        int getFrameAmount();

        Texture2D getTexture(){return texture_;};
        Rectangle getFrame(){return frame_;};
        Vector2 getRelativePosition();

        int getCurrentStateId(){return currentStateId_;};

    protected:

        std::vector<std::vector<AnimationState>> animationStates_; // state<direction<animationState>>
        AnimationState currentState_;
        int currentStateId_ = 0;
        int currentStep_ = 0;

        Direction primaryDirection_ = Direction::UP;

        std::string path_ = "";
        Texture2D texture_;
        Rectangle frame_;
    };
}



#endif //HIVE_SPRITE_H
