//
// Created by keanu on 5/23/2024.
//

#ifndef RAYLIBSTARTER_LEVEL_H
#define RAYLIBSTARTER_LEVEL_H


#include <string>
#include <memory>
#include <vector>
#include "raylib.h"
#include "event_management/Actor.h"
#include "../../tileson.h"



namespace CoreLogic::DataProcessing
{
    enum class LevelState
    {
        Default = 0,
        War = 1,
        Peace = 2
    };

    class Level
    {
    public:
        Level(std::unique_ptr<std::vector<std::string>> pa_mapPath, int pa_levelID, LevelState pa_levelState);

        Level(const Level &other);

        std::string getMapPath() const;

        int getLevelID() const;

        LevelState getLevelState() const;

        std::vector<std::string> getStateChanges() const;

        void setLevelState(LevelState pa_levelState);


        void saveLevelStates();
        void loadLevelData();
    private:
        Level() = delete;
    protected:
        const int levelID_;
        std::unique_ptr<std::vector<std::string>> po_mapPath_;


        LevelState levelState_;
        //to be changed as soon as we know how to handle object state changes(if we cant handle certain obj-changes via a map)
        std::unique_ptr<std::vector<std::string>> stateChanges_;

        std::shared_ptr<std::map<int, std::vector<std::shared_ptr<EventManagement::Actor>>>> po_levelActorStateStorage_ = nullptr;
        std::shared_ptr<std::map<int, std::vector<tson::Layer>>> po_layers_ = nullptr;
        int elevationLevels_ = 0;
    };
}


#endif //RAYLIBSTARTER_LEVEL_H
