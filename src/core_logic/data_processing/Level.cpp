//
// Created by keanu on 5/23/2024.
//

#include <map>
#include "Level.h"
#include "Store.h"

CoreLogic::DataProcessing::Level::Level(std::unique_ptr<std::vector<std::string>> pa_mapPath, int pa_levelID, LevelState pa_levelState): levelID_(pa_levelID)
{
    po_mapPath_ = std::move(pa_mapPath);
    levelState_ = pa_levelState;
}

CoreLogic::DataProcessing::Level::Level(const Level &other): po_mapPath_(std::make_unique<std::vector<std::string>>(*other.po_mapPath_)), levelID_(other.levelID_), levelState_(other.levelState_){}

std::string CoreLogic::DataProcessing::Level::getMapPath() const
{
    std::string copy = po_mapPath_->at(static_cast<int>(levelState_));
    return copy;
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



void CoreLogic::DataProcessing::Level::saveLevelStates()
{
    std::shared_ptr<std::map<int, std::vector<std::shared_ptr<EventManagement::Actor>>>> actors = CoreLogic::DataProcessing::ActorStorage::getActors();
    std::shared_ptr<std::map<int, std::vector<tson::Layer>>> layers = CoreLogic::DataProcessing::ActorStorage::getLayers();
    elevationLevels_ = *CoreLogic::DataProcessing::ActorStorage::getCurrentElevationLevels();
    po_levelActorStateStorage_ = actors;
    po_layers_ = layers;
}

void CoreLogic::DataProcessing::Level::loadLevelData()
{
    CoreLogic::DataProcessing::ActorStorage::Initialize(elevationLevels_);
    CoreLogic::DataProcessing::ActorStorage::setLayers(po_layers_);

    for (auto &pair : *po_levelActorStateStorage_)
    {
        for (auto &actor : pair.second)
        {
            CoreLogic::DataProcessing::ActorStorage::addActorByType(pair.first, actor);
        }
    }
}

void CoreLogic::DataProcessing::Level::setLevelState(LevelState pa_levelState)
{
    levelState_ = pa_levelState;
}





