//
// Created by keanu on 5/26/2024.
//

#ifndef RAYLIBSTARTER_STORE_H
#define RAYLIBSTARTER_STORE_H

#include <memory>
#include <mutex>
#include <vector>
#include <map>
#include "raylib.h"
#include "../../tileson.h"


#include "event_management/Actor.h"
#include "event_management/actors/Drone.h"
#include "event_management/actors/objects/Barrier.h"
#include "actors/objects/Vine.h"
#include "actors/objects/Rubble.h"
#include "actors/objects/JumpPoint.h"
#include "actors/objects/Boulder.h"
#include "actors/enemies/Colonist.h"
#include "actors/objects/Barrel.h"
#include "actors/objects/TutorialBox.h"
#include "actors/objects/Note.h"
#include "actors/objects/LevelSwitch.h"
#include "actors/Enemy.h"
#include "actors/objects/Water.h"


namespace CoreLogic::DataProcessing
{
    enum GameState
    {
        MainMenu = 0,
        InGame = 1,
        Pause = 2,
        Settings = 3
    };
    inline long long int ticks = 1;
    const int tileSize = 24;

    const int screenWidth_ = 640;
    const int screenHeight_ = 360;



    struct TileMap
    {
    private:
        static std::shared_ptr<Texture2D> po_tileMap_;
    public:
        static std::shared_ptr<Texture2D> getTileMap();
        static void Initialize();
    };

    struct ActorStorage
    {
    /**
     * @todo: actual implementaion for po_actors_(convert Objects from map Class)
     * @note: possibly also get std::map<int, vector<Layer>> po_layers_ as to not have to make the Map class static
     **/
    private:
        static std::shared_ptr<EventManagement::Actors::Drone> po_player_;
        static std::shared_ptr<std::map<int, std::vector<std::shared_ptr<EventManagement::Actor>>>> po_actors_;
        static std::shared_ptr<std::map<int, std::vector<tson::Layer>>> po_layers_;

        static std::shared_ptr<std::map<int, std::vector<std::shared_ptr<EventManagement::Actor>>>> po_allActors_;
        static std::shared_ptr<std::map<int, std::vector<std::shared_ptr<EventManagement::Actor>>>> po_visibles_;
        //wil not include barrels
        static std::shared_ptr<std::map<int, std::vector<std::shared_ptr<EventManagement::Object::Ability>>>>
        po_allAbilities_;
        static std::shared_ptr<std::map<int, std::vector<std::shared_ptr<EventManagement::Object::Ability>>>>
        po_workerAbilities_;
        static std::shared_ptr<std::map<int, std::vector<std::shared_ptr<EventManagement::Object::Ability>>>>
                po_scoutAbilities_;
        static std::shared_ptr<std::map<int, std::vector<std::shared_ptr<EventManagement::Object::Interaction>>>>
                po_interactions_;
        static std::shared_ptr<std::map<int, std::vector<std::shared_ptr<EventManagement::Actors::Enemy>>>>
                po_allEnemies_;



        static std::shared_ptr<std::map<int, std::vector<std::shared_ptr<EventManagement::Object::Barrier>>>>
        po_barriers_;
        static std::shared_ptr<std::map<int, std::vector<std::shared_ptr<EventManagement::Object::Rubble>>>>
                po_rubbles_;
        static std::shared_ptr<std::map<int, std::vector<std::shared_ptr<EventManagement::Object::Boulder>>>>
                po_boulders_;
        static std::shared_ptr<std::map<int, std::vector<std::shared_ptr<EventManagement::Object::Vine>>>>
                po_vines_;
        static std::shared_ptr<std::map<int, std::vector<std::shared_ptr<EventManagement::Object::Water>>>>
                po_waters_;
        static std::shared_ptr<std::map<int, std::vector<std::shared_ptr<EventManagement::Object::JumpPoint>>>>
                po_jumpPoints_;
        static std::shared_ptr<std::map<int, std::vector<std::shared_ptr<EventManagement::Actors::Colonist>>>>
                po_colonists_;
        static std::shared_ptr<std::map<int, std::vector<std::shared_ptr<EventManagement::Object::Cliff>>>>
                po_cliffs_;
        static std::shared_ptr<std::map<int, std::vector<std::shared_ptr<EventManagement::Object::Barrel>>>>
                po_barrels_;
        static std::shared_ptr<std::map<int, std::vector<std::shared_ptr<EventManagement::Object::TutorialBox>>>>
                po_tutorialBoxes_;
        static std::shared_ptr<std::map<int, std::vector<std::shared_ptr<EventManagement::Object::Note>>>>
                po_notes_;
        static std::shared_ptr<std::map<int, std::vector<std::shared_ptr<EventManagement::Object::LevelSwitch>>>>
                po_levelSwitches_;


    public:
        static void Initialize();

        static std::shared_ptr<EventManagement::Actors::Drone> getPlayer();
        static void setPlayer(std::shared_ptr<EventManagement::Actors::Drone> pa_player);

        static std::shared_ptr<std::map<int, std::vector<std::shared_ptr<EventManagement::Actor>>>> getActors();
        static std::shared_ptr<EventManagement::Actor> getActorByID(int pa_actorID);
        static void setActors(std::shared_ptr<std::map<int, std::vector<std::shared_ptr<EventManagement::Actor>>>> pa_actors);
        template <typename T>
        static void addActor(std::shared_ptr<std::map<int, std::vector<std::shared_ptr<T>>>> pa_map, int pa_elevation,
                std::shared_ptr<T> pa_actor);
        static void addActorByType(int pa_elevation, std::shared_ptr<EventManagement::Actor> pa_actor);

        static std::shared_ptr<std::map<int, std::vector<tson::Layer>>> getLayers();
        static void setLayers(std::shared_ptr<std::map<int, std::vector<tson::Layer>>> pa_layers);
        //static void newDrone(//DroneType);

    };

}




#endif //RAYLIBSTARTER_STORE_H
