//
// Created by keanu on 5/23/2024.
//

#include "Level.h"

CoreLogic::DataProcessing::Level::Level(std::unique_ptr<std::vector<std::string>> pa_mapPath, int pa_levelID, LevelState pa_levelState): levelID_(pa_levelID)
{
    po_mapPath_ = std::move(pa_mapPath);
    levelState_ = pa_levelState;
}

CoreLogic::DataProcessing::Level::Level(const Level &other): po_mapPath_(std::make_unique<std::vector<std::string>>(*other.po_mapPath_)), levelID_(other.levelID_), levelState_(other.levelState_){}

std::string CoreLogic::DataProcessing::Level::getMapPath() const
{
    return po_mapPath_->at(static_cast<int>(levelState_));
}

int CoreLogic::DataProcessing::Level::getLevelID() const
{
    return levelID_;
}

CoreLogic::DataProcessing::LevelState CoreLogic::DataProcessing::Level::getLevelState() const
{
    return levelState_;
}

/*
 * @brief: TODO change to correct return Value
 * */
std::vector<std::string> CoreLogic::DataProcessing::Level::getStateChanges() const
{
    return *stateChanges_;
}

void CoreLogic::DataProcessing::Level::setLevelState(LevelState pa_levelState)
{
    levelState_ = pa_levelState;
}

