//
// Created by Josi on 10.07.2024.
//

#include "Sprite.h"

namespace CoreLogic::UserInterface
{

    CoreLogic::UserInterface::Sprite::Sprite(std::string pa_path,
            std::vector<std::vector<CoreLogic::UserInterface::AnimationState>> pa_animationStates)
    {
        path_ = pa_path;
        animationStates_ = pa_animationStates;

        texture_ = LoadTexture(pa_path.c_str());
        frame_ = {0, 0, (float)animationStates_[0][0].width_, (float)animationStates_[0][0].height_};
        currentState_ = animationStates_[0][0];
        currentStep_ = 0;
    }

    void CoreLogic::UserInterface::Sprite::shiftFrame(int pa_stateID,
            CoreLogic::UserInterface::Direction pa_primaryDirection)
    {
        if (pa_stateID < animationStates_.size() &&
                static_cast<int>(pa_primaryDirection) < animationStates_[pa_stateID].size())
        {
            currentState_ = animationStates_[pa_stateID][static_cast<int>(pa_primaryDirection)];

            if (pa_stateID == currentStateId_ && pa_primaryDirection == primaryDirection_)
            {
                currentStep_++;

                if (currentStep_ >= currentState_.steps_)
                {
                    currentStep_ = 0;
                }
                frame_.x = (float) (currentStep_ * currentState_.width_);
            } else
            {

                frame_ = {0, (float) currentState_.pxRow_, (float)currentState_.width_, (float)currentState_.height_};

                currentStep_ = 0;
            }
            currentStateId_ = pa_stateID;
            primaryDirection_ = pa_primaryDirection;
        }
    }

    void CoreLogic::UserInterface::Sprite::resetFrame(int pa_stateID)
    {
        if (pa_stateID < animationStates_.size() &&
                static_cast<int>(primaryDirection_) < animationStates_[pa_stateID].size())
        {
            currentState_ = animationStates_[pa_stateID][static_cast<int>(primaryDirection_)];
            currentStateId_ = pa_stateID;
        } else
        {
            currentState_ = animationStates_[0][0];
            currentStateId_ = 0;
            primaryDirection_ = Direction::UP;
        }

        frame_ = {0, (float) currentState_.pxRow_, (float)currentState_.width_, (float)currentState_.height_};
        currentStep_ = 0;
    }

    CoreLogic::UserInterface::Sprite::Sprite()
    {
        path_ = "";
        animationStates_ = std::vector<std::vector<CoreLogic::UserInterface::AnimationState>>();
    }

    void Sprite::shiftFrame(int pa_stateID)
    {
        shiftFrame(pa_stateID, Direction::UP);
    }

    Vector2 Sprite::getRelativePosition()
    {
        return animationStates_[currentStateId_][static_cast<int>(primaryDirection_)].relativePosition_;
    }

    int Sprite::getFrameAmount()
    {
        return animationStates_[currentStateId_][static_cast<int>(primaryDirection_)].steps_;
    }

    int Sprite::getFrameAmount(int pa_stateID)
    {
        if (pa_stateID < animationStates_.size() &&
                static_cast<int>(Direction::UP) < animationStates_[pa_stateID].size())
        {
            return animationStates_[pa_stateID][static_cast<int>(Direction::UP)].steps_;
        }
        return -1;
    }

    int Sprite::getFrameAmount(int pa_stateID, Direction pa_primaryDirection)
    {
        if (pa_stateID < animationStates_.size() &&
                static_cast<int>(pa_primaryDirection) < animationStates_[pa_stateID].size())
        {
            return animationStates_[pa_stateID][static_cast<int>(pa_primaryDirection)].steps_;
        }
        return -1;
    }
}