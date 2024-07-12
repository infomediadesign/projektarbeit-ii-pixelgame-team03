//
// Created by Josi on 10.07.2024.
//

#ifndef HIVE_SPRITE_H
#define HIVE_SPRITE_H

#include <vector>
#include <string>
#include "raylib.h"
#include "event_management/actor/Drone.h"

namespace CoreLogic::EventManagement
{
    struct AnimationState
    {
        /// y-offset measured in rows (depending on the frame height, i.e. row 1 has a y-offset of 0px, row 2 has a y-offset of the height of an animation frame, etc.).
        int row_;
        /// Number of steps of the animation.
        int steps_;
    };

    class Sprite
    {

    public:
        Sprite();
        Sprite(std::string pa_path, int pa_frameWidth, int pa_frameHeight, std::vector<std::vector<AnimationState>>
        pa_animationStates);
        //void shiftFrame(int pa_stateID, Actor::Direction pa_primaryDirection);

    protected:

        std::vector<std::vector<AnimationState>> animationStates_; // state<direction<animationState>>
        int currentState_ = 0;
        int currentFrame_ = 0;

        /**
         * @note: this breaks shit and I don't know why
         */
        //Actor::Direction primaryDirection_;

        int frameWidth_;
        int frameHeight_;

        std::string path_;
        Texture2D texture_;
        Rectangle frame_;

    };

}

#endif //HIVE_SPRITE_H
