//
// Created by Josi on 10.07.2024.
//

#include <iostream>
#include "Sprite.h"

namespace CoreLogic::EventManagement
{

    Sprite::Sprite(std::string pa_path, int pa_frameWidth, int pa_frameHeight,
                   std::vector<std::vector<AnimationState>> pa_animationStates)
    {
        path_ = pa_path;
        frameWidth_ = pa_frameWidth;
        frameHeight_ = pa_frameHeight;
        animationStates_ = pa_animationStates;

        texture_ = LoadTexture(pa_path.c_str());
        frame_ = {0, 0, (float) frameWidth_, (float) frameHeight_};

    }

    void Sprite::shiftFrame(int pa_stateID, Direction pa_primaryDirection)
    {

        if (pa_stateID < animationStates_.size() &&
            static_cast<int>(pa_primaryDirection) < animationStates_[pa_stateID].size())
        {
            std::cout << currentState_ << std::endl;
            if (pa_stateID == currentState_ && pa_primaryDirection == primaryDirection_)
            {
                currentStep_++;

                if (currentStep_ >= animationStates_[pa_stateID][static_cast<int>(pa_primaryDirection)].steps_)
                {
                    currentStep_ = 0;
                }

                frame_.x = (float) (currentStep_ * frameWidth_);
            } else
            {
                frame_.x = 0;
                frame_.y = animationStates_[pa_stateID][static_cast<int>(pa_primaryDirection)].row_ * frameHeight_;
                currentStep_ = 0;
            }
            currentState_ = pa_stateID;
            primaryDirection_ = pa_primaryDirection;
        }
    }

    void Sprite::resetFrame(int pa_stateID)
    {
        if (pa_stateID < animationStates_.size() &&
            static_cast<int>(primaryDirection_) < animationStates_[pa_stateID].size())
        {
            frame_.x = 0;
            frame_.y = animationStates_[pa_stateID][static_cast<int>(primaryDirection_)].row_ * frameHeight_;
            currentStep_ = 0;
        }
        else
        {
            frame_.x = 0;
            frame_.y = animationStates_[1][1].row_ * frameHeight_;;
            currentStep_ = 0;

            primaryDirection_ = Direction::RIGHT;
        }
        currentState_ = pa_stateID;


    }

    Sprite::Sprite()
    {
        path_ = "";
        frameWidth_ = 0;
        frameHeight_ = 0;
        animationStates_ = std::vector<std::vector<AnimationState>>();
    }
}