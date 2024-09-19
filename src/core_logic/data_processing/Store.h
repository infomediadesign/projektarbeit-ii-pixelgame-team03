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
#include "event_management/actors/objects/Vine.h"
#include "event_management/actors/objects/Rubble.h"
#include "event_management/actors/objects/JumpPoint.h"
#include "event_management/actors/objects/Boulder.h"
#include "event_management/actors/enemies/Colonist.h"
#include "event_management/actors/objects/Barrel.h"
#include "event_management/actors/objects/TutorialBox.h"
#include "event_management/actors/objects/Note.h"
#include "event_management/actors/objects/LevelSwitch.h"
#include "event_management/actors/Enemy.h"
#include "event_management/actors/objects/DroneRespawnPoint.h"
#include "event_management/actors/enemies/Mech.h"
#include "event_management/actors/objects/Uplink.h"
#include "event_management/actors/objects/CameraPan.h"


namespace CoreLogic::DataProcessing
{
    enum GameState
    {
        MAIN_MENU,
        IN_GAME,
        DRONE_SELECTION,
        PAUSE,
        SETTINGS,
        END_SCENE,
        CREDITS,
        DEATH,
        NOTE,
        VICTORY,
        CAMERA_PAN,
    };
    inline long long int global_ticks = 1;
    inline const int global_tileSize = 24;

    const int screenWidth_ = 640;
    const int screenHeight_ = 360;

    struct StateMachine
{
public:
    static void Initialize();
    static GameState getCurrentState();
    static GameState getPreviousState();
    static void changeState(GameState newState);

protected:
    static GameState currentState_;
    static GameState previousState_;
};

    struct Fonts
{
public:
    static Font getFont(int pa_index);
    static void Initialize();
private:
    static std::shared_ptr<std::vector<Font>> po_fonts_;
};

    struct TileMap
    {
    private:
        static std::shared_ptr<Texture2D> po_tileMap_;
    public:
        static std::shared_ptr<Texture2D> getTileMap();
        static void Initialize();
    };

    struct SpriteStorage
    {
        enum SpriteEnum{
            WORKER_DRONE,
            SCOUT_DRONE,

            COLONIST,
            MECH,

            RUBBLE_OVERWORLD,
            RUBBLE_UNDERWORLD,
            SPAWN_OVERWORLD,
            SPAWN_UNDERWORLD,
            SPAWN_SECONDARY,
            BOULDER_OVERWORLD,
            BOULDER_UNDERWORLD,
            BARREL,
            NOTE,
            NOTE_SECONDARY,
            VINE_OVERWORLD_SECONDARY,
            VINE_UNDERWORLD_SECONDARY,
            UPLINK,

            HUD_BUTTONS,
            HUD_INTERACT,
            HUD_TOGGLE,
            HUD_MAIN_ABILITY,
            HUD_DEATH_ABILITY,

            HUD_CURRENT_LIFE,
            HUD_MAX_LIFE,
            HUD_PORTRAIT,

            DRONE_SELECTION,
            MAIN_MENU,
            DEATH_SCENE,
            VICTORY_BACKGROUND,
            VICTORY_BUTTONS,
            CREDIT_SCENE,

            LORE_ITEM,
            LORE_CRACKS
        };

    public:
        static void Initialize();
        static UserInterface::Sprite getSprite(SpriteEnum spriteEnum);
    protected:
        static std::vector<CoreLogic::UserInterface::Sprite> po_sprites_;
    };

    struct ActorStorage
    {
    private:
        static std::shared_ptr<std::map<CoreLogic::EventManagement::Actors::Drone::DroneType, bool>> po_unlockedDrones_;
        //------------------actives------------------//
        static std::shared_ptr<CoreLogic::EventManagement::Object::DroneRespawnPoint> po_activeRespawnPoint_;

        static std::shared_ptr<CoreLogic::EventManagement::Object::TutorialBox> po_activeTutorialBox_;
        static std::shared_ptr<CoreLogic::EventManagement::Object::CameraPan> po_activeCameraPan_;
        static std::shared_ptr<CoreLogic::EventManagement::Object::Note> po_activeNote_;
        static std::shared_ptr<EventManagement::Actors::Drone> po_player_;

        static int currentLevelID_;
        static int currentElevationLevels_;

        //------------------general lists------------------//
        static std::shared_ptr<std::map<int, std::vector<tson::Layer>>> po_layers_;

        static std::shared_ptr<std::map<int, std::vector<std::shared_ptr<EventManagement::Actor>>>> po_allActors_;
        static std::shared_ptr<std::map<int, std::vector<std::shared_ptr<EventManagement::Actor>>>> po_collidables_;
        //does not include Cliffs
        static std::shared_ptr<std::map<int, std::vector<std::shared_ptr<EventManagement::Actor>>>> po_visibles_;
        //does not include barrels
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


        //------------------specific lists------------------//
        static std::shared_ptr<std::map<int, std::vector<std::shared_ptr<EventManagement::Object::Barrier>>>>
        po_barriers_;
        static std::shared_ptr<std::map<int, std::vector<std::shared_ptr<EventManagement::Object::Rubble>>>>
                po_rubbles_;
        static std::shared_ptr<std::map<int, std::vector<std::shared_ptr<EventManagement::Object::Boulder>>>>
                po_boulders_;
        static std::shared_ptr<std::map<int, std::vector<std::shared_ptr<EventManagement::Object::Vine>>>>
                po_vines_;
        static std::shared_ptr<std::map<int, std::vector<std::shared_ptr<EventManagement::Object::JumpPoint>>>>
                po_jumpPoints_;
        static std::shared_ptr<std::map<int, std::vector<std::shared_ptr<EventManagement::Actors::Colonist>>>>
                po_colonists_;
        static std::shared_ptr<std::map<int, std::vector<std::shared_ptr<EventManagement::Actors::Mech>>>>
                po_mechs_;
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
        static std::shared_ptr<std::map<int, std::vector<std::shared_ptr<EventManagement::Object::Uplink>>>>
                po_uplinks_;
        static std::shared_ptr<std::map<int, std::vector<std::shared_ptr<EventManagement::Object::DroneRespawnPoint>>>>
                po_respawnPoints_;
        static std::shared_ptr<std::map<int, std::vector<std::shared_ptr<EventManagement::Object::CameraPan>>>>
                po_cameraPans_;

        template <typename T>
        static typename std::enable_if<!std::is_pointer<T>::value && !std::is_same<T, std::shared_ptr<typename std::remove_reference<T>::type>>::value,
                std::shared_ptr<std::map<int, std::vector<T>>>>::type
        initializeSpecificLists(int pa_elevationLevels);
        template <typename T>
        static typename std::enable_if<std::is_same<T, std::shared_ptr<typename std::remove_reference<T>::type>>::value,
                std::shared_ptr<std::map<int, std::vector<T>>>>::type
        initializeSpecificLists(int pa_elevationLevels);


    public:
        static void Initialize();
        static void Initialize(int pa_elevationLevels, int pa_levelID);

        static bool isDroneUnlocked(CoreLogic::EventManagement::Actors::Drone::DroneType pa_droneType);
        static void unlockDrone(CoreLogic::EventManagement::Actors::Drone::DroneType pa_droneType);

        static std::shared_ptr<std::map<CoreLogic::EventManagement::Actors::Drone::DroneType, bool>> getUnlockedDrones();
        static void setUnlockedDrones(std::shared_ptr<std::map<CoreLogic::EventManagement::Actors::Drone::DroneType, bool>>
        pa_unlockedDrones);

        //------------------actives------------------//
        static std::shared_ptr<CoreLogic::EventManagement::Object::DroneRespawnPoint> getActiveSpawnPoint();
        static void setActiveSpawnPoint(std::shared_ptr<CoreLogic::EventManagement::Object::DroneRespawnPoint> pa_spawnPoint);

        static std::shared_ptr<CoreLogic::EventManagement::Object::TutorialBox> getActiveTutorialBox();
        static void setActiveTutorialBox(
                std::shared_ptr<CoreLogic::EventManagement::Object::TutorialBox> pa_tutorialBox);

        static std::shared_ptr<CoreLogic::EventManagement::Object::CameraPan> getActiveCameraPan();
        static void setActiveCameraPan(
                std::shared_ptr<CoreLogic::EventManagement::Object::CameraPan> pa_cameraPan);

        static std::shared_ptr<CoreLogic::EventManagement::Object::Note> getActiveNote();
        static void setActiveNote(std::shared_ptr<CoreLogic::EventManagement::Object::Note> pa_activeNote);


        static std::shared_ptr<EventManagement::Actors::Drone> getPlayer();
        static void setPlayer(std::shared_ptr<EventManagement::Actors::Drone> pa_player);


        static int getCurrentElevationLevels();
        static void setCurrentElevationLevels(int pa_currentElevationLayers);

        static int getCurrentLevelID();
        static void setCurrentLevelID(int pa_currentLevelID);
        //------------------general lists------------------//
        template <typename T>
        static void addActor(std::shared_ptr<std::map<int, std::vector<std::shared_ptr<T>>>> pa_map, int pa_elevation,
                std::shared_ptr<T> pa_actor);


        static void addActorByType(int pa_elevation, std::shared_ptr<EventManagement::Actor> pa_actor);
        static std::shared_ptr<std::map<int, std::vector<tson::Layer>>> getLayers();

        static void setLayers(std::shared_ptr<std::map<int, std::vector<tson::Layer>>> pa_layers);


        static std::shared_ptr<std::map<int, std::vector<std::shared_ptr<EventManagement::Actor>>>> getActors();
        static void setActors(std::shared_ptr<std::map<int, std::vector<std::shared_ptr<EventManagement::Actor>>>> pa_actors);


        static std::shared_ptr<std::map<int, std::vector<std::shared_ptr<EventManagement::Actor>>>> getCollidables();
        static void setCollidables(std::shared_ptr<std::map<int, std::vector<std::shared_ptr<EventManagement::Actor>>>> pa_collidables);

        static std::shared_ptr<std::map<int, std::vector<std::shared_ptr<EventManagement::Actor>>>> getVisibles();
        static void setVisibles(std::shared_ptr<std::map<int, std::vector<std::shared_ptr<EventManagement::Actor>>>> pa_visibles);
        static void changeDrawingElevation(std::shared_ptr<CoreLogic::EventManagement::Actor> pa_actor, int pa_newElevation);


        static std::shared_ptr<std::map<int, std::vector<std::shared_ptr<EventManagement::Object::Ability>>>> getAbilities();
        static void setAbilities(std::shared_ptr<std::map<int, std::vector<std::shared_ptr<EventManagement::Object::Ability>>>> pa_abilities);

        static std::shared_ptr<std::map<int, std::vector<std::shared_ptr<EventManagement::Object::Ability>>>> getWorkerAbilities();
        static void setWorkerAbilities(std::shared_ptr<std::map<int, std::vector<std::shared_ptr<EventManagement::Object::Ability>>>> pa_workerAbilities);

        static std::shared_ptr<std::map<int, std::vector<std::shared_ptr<EventManagement::Object::Ability>>>> getScoutAbilities();
        static void setScoutAbilities(std::shared_ptr<std::map<int,
                std::vector<std::shared_ptr<EventManagement::Object::Ability>>>> pa_scoutAbilities);

        static std::shared_ptr<std::map<int, std::vector<std::shared_ptr<EventManagement::Object::Interaction>>>> getInteractions();
        static void setInteractions(std::shared_ptr<std::map<int, std::vector<std::shared_ptr<EventManagement::Object::Interaction>>>> pa_interactions);

        static std::shared_ptr<std::map<int, std::vector<std::shared_ptr<EventManagement::Actors::Enemy>>>> getEnemies();
        static void setEnemies(std::shared_ptr<std::map<int, std::vector<std::shared_ptr<EventManagement::Actors::Enemy>>>> pa_enemies);



        //------------------specific lists------------------//
        static std::shared_ptr<std::map<int, std::vector<std::shared_ptr<EventManagement::Object::Barrier>>>> getBarriers();
        static void setBarriers(std::shared_ptr<std::map<int, std::vector<std::shared_ptr<EventManagement::Object::Barrier>>>> pa_barriers);

        static std::shared_ptr<std::map<int, std::vector<std::shared_ptr<EventManagement::Object::Rubble>>>> getRubbles();
        static void setRubbles(std::shared_ptr<std::map<int, std::vector<std::shared_ptr<EventManagement::Object::Rubble>>>> pa_rubbles);

        static std::shared_ptr<std::map<int, std::vector<std::shared_ptr<EventManagement::Object::Boulder>>>> getBoulders();
        static void setBoulders(std::shared_ptr<std::map<int, std::vector<std::shared_ptr<EventManagement::Object::Boulder>>>> pa_boulders);

        static std::shared_ptr<std::map<int, std::vector<std::shared_ptr<EventManagement::Object::Vine>>>> getVines();
        static void setVines(std::shared_ptr<std::map<int, std::vector<std::shared_ptr<EventManagement::Object::Vine>>>> pa_vines);

        static std::shared_ptr<std::map<int, std::vector<std::shared_ptr<EventManagement::Object::JumpPoint>>>> getJumpPoints();
        static void setJumpPoints(std::shared_ptr<std::map<int, std::vector<std::shared_ptr<EventManagement::Object::JumpPoint>>>> pa_jumpPoints);

        static std::shared_ptr<std::map<int, std::vector<std::shared_ptr<EventManagement::Actors::Colonist>>>>
        getColonists();
        static void setColonists(std::shared_ptr<std::map<int, std::vector<std::shared_ptr<EventManagement::Actors::Colonist>>>> pa_colonists);

        static std::shared_ptr<std::map<int, std::vector<std::shared_ptr<EventManagement::Actors::Mech>>>> getMechs();
        static void setMechs(std::shared_ptr<std::map<int,
                std::vector<std::shared_ptr<EventManagement::Actors::Mech>>>> pa_mechs);

        static std::shared_ptr<std::map<int, std::vector<std::shared_ptr<EventManagement::Object::Cliff>>>> getCliffs();
        static void setCliffs(std::shared_ptr<std::map<int, std::vector<std::shared_ptr<EventManagement::Object::Cliff>>>> pa_cliffs);

        static std::shared_ptr<std::map<int, std::vector<std::shared_ptr<EventManagement::Object::Barrel>>>> getBarrels();
        static void setBarrels(std::shared_ptr<std::map<int, std::vector<std::shared_ptr<EventManagement::Object::Barrel>>>> pa_barrels);

        static std::shared_ptr<std::map<int, std::vector<std::shared_ptr<EventManagement::Object::TutorialBox>>>> getTutorialBoxes();
        static void setTutorialBoxes(std::shared_ptr<std::map<int, std::vector<std::shared_ptr<EventManagement::Object::TutorialBox>>>> pa_tutorialBoxes);

        static std::shared_ptr<std::map<int, std::vector<std::shared_ptr<EventManagement::Object::Note>>>> getNotes();
        static void setNotes(std::shared_ptr<std::map<int, std::vector<std::shared_ptr<EventManagement::Object::Note>>>> pa_notes);

        static std::shared_ptr<std::map<int, std::vector<std::shared_ptr<EventManagement::Object::LevelSwitch>>>> getLevelSwitches();
        static void setLevelSwitches(
                std::shared_ptr<std::map<int, std::vector<std::shared_ptr<EventManagement::Object::LevelSwitch>>>> pa_levelSwitches);

        static std::shared_ptr<std::map<int, std::vector<std::shared_ptr<EventManagement::Object::Uplink>>>> getUplinks();
        static void setUplinks(std::shared_ptr<std::map<int, std::vector<std::shared_ptr<EventManagement::Object::Uplink>>>> pa_uplinks);

        static std::shared_ptr<std::map<int, std::vector<std::shared_ptr<EventManagement::Object::CameraPan>>>> getCameraPans();
        static void setCameraPans(std::shared_ptr<std::map<int, std::vector<std::shared_ptr<EventManagement::Object::CameraPan>>>> pa_cameraPans);
    };

}




#endif //RAYLIBSTARTER_STORE_H
