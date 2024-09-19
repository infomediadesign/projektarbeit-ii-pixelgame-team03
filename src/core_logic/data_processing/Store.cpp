//
// Created by keanu on 6/1/2024.
//
#include "Store.h"
#include "raylib.h"


std::shared_ptr<Texture2D> CoreLogic::DataProcessing::TileMap::po_tileMap_ = nullptr;
std::shared_ptr<std::vector<Font>> CoreLogic::DataProcessing::Fonts::po_fonts_ = nullptr;
std::shared_ptr<Texture2D> CoreLogic::DataProcessing::TileMap::getTileMap() {return po_tileMap_;}

// Define the static member variables for ActorStorage

std::shared_ptr<std::map<CoreLogic::EventManagement::Actors::Drone::DroneType, bool>> CoreLogic::DataProcessing::ActorStorage::po_unlockedDrones_ =
        std::make_shared<std::map<CoreLogic::EventManagement::Actors::Drone::DroneType, bool>>();


//------------------actives------------------//
std::shared_ptr<CoreLogic::EventManagement::Object::DroneRespawnPoint> CoreLogic::DataProcessing::ActorStorage::po_activeRespawnPoint_;
std::shared_ptr<CoreLogic::EventManagement::Object::TutorialBox> CoreLogic::DataProcessing::ActorStorage::po_activeTutorialBox_;
std::shared_ptr<CoreLogic::EventManagement::Object::Note> CoreLogic::DataProcessing::ActorStorage::po_activeNote_;

std::shared_ptr<CoreLogic::EventManagement::Actors::Drone> CoreLogic::DataProcessing::ActorStorage::po_player_;

int CoreLogic::DataProcessing::ActorStorage::currentElevationLevels_;
int CoreLogic::DataProcessing::ActorStorage::currentLevelID_;
//------------------general lists------------------//
std::shared_ptr<std::map<int, std::vector<tson::Layer>>> CoreLogic::DataProcessing::ActorStorage::po_layers_;

std::shared_ptr<std::map<int, std::vector<std::shared_ptr<CoreLogic::EventManagement::Actor>>>> CoreLogic::DataProcessing::ActorStorage::po_allActors_;
std::shared_ptr<std::map<int, std::vector<std::shared_ptr<CoreLogic::EventManagement::Actor>>>> CoreLogic::DataProcessing::ActorStorage::po_collidables_;
std::shared_ptr<std::map<int, std::vector<std::shared_ptr<CoreLogic::EventManagement::Actor>>>> CoreLogic::DataProcessing::ActorStorage::po_visibles_;
std::shared_ptr<std::map<int, std::vector<std::shared_ptr<CoreLogic::EventManagement::Object::Ability>>>> CoreLogic::DataProcessing::ActorStorage::po_allAbilities_;
std::shared_ptr<std::map<int, std::vector<std::shared_ptr<CoreLogic::EventManagement::Object::Ability>>>> CoreLogic::DataProcessing::ActorStorage::po_workerAbilities_;
std::shared_ptr<std::map<int, std::vector<std::shared_ptr<CoreLogic::EventManagement::Object::Ability>>>> CoreLogic::DataProcessing::ActorStorage::po_scoutAbilities_;
std::shared_ptr<std::map<int, std::vector<std::shared_ptr<CoreLogic::EventManagement::Object::Interaction>>>> CoreLogic::DataProcessing::ActorStorage::po_interactions_;
std::shared_ptr<std::map<int, std::vector<std::shared_ptr<CoreLogic::EventManagement::Actors::Enemy>>>> CoreLogic::DataProcessing::ActorStorage::po_allEnemies_;

//------------------specific lists------------------//
std::shared_ptr<std::map<int, std::vector<std::shared_ptr<CoreLogic::EventManagement::Object::Barrier>>>> CoreLogic::DataProcessing::ActorStorage::po_barriers_;
std::shared_ptr<std::map<int, std::vector<std::shared_ptr<CoreLogic::EventManagement::Object::Rubble>>>> CoreLogic::DataProcessing::ActorStorage::po_rubbles_;
std::shared_ptr<std::map<int, std::vector<std::shared_ptr<CoreLogic::EventManagement::Object::Boulder>>>> CoreLogic::DataProcessing::ActorStorage::po_boulders_;
std::shared_ptr<std::map<int, std::vector<std::shared_ptr<CoreLogic::EventManagement::Object::Vine>>>> CoreLogic::DataProcessing::ActorStorage::po_vines_;
std::shared_ptr<std::map<int, std::vector<std::shared_ptr<CoreLogic::EventManagement::Object::JumpPoint>>>> CoreLogic::DataProcessing::ActorStorage::po_jumpPoints_;
std::shared_ptr<std::map<int, std::vector<std::shared_ptr<CoreLogic::EventManagement::Actors::Colonist>>>> CoreLogic::DataProcessing::ActorStorage::po_colonists_;
std::shared_ptr<std::map<int, std::vector<std::shared_ptr<CoreLogic::EventManagement::Actors::Mech>>>> CoreLogic::DataProcessing::ActorStorage::po_mechs_;
std::shared_ptr<std::map<int, std::vector<std::shared_ptr<CoreLogic::EventManagement::Object::Cliff>>>> CoreLogic::DataProcessing::ActorStorage::po_cliffs_;
std::shared_ptr<std::map<int, std::vector<std::shared_ptr<CoreLogic::EventManagement::Object::Barrel>>>> CoreLogic::DataProcessing::ActorStorage::po_barrels_;
std::shared_ptr<std::map<int, std::vector<std::shared_ptr<CoreLogic::EventManagement::Object::TutorialBox>>>> CoreLogic::DataProcessing::ActorStorage::po_tutorialBoxes_;
std::shared_ptr<std::map<int, std::vector<std::shared_ptr<CoreLogic::EventManagement::Object::Note>>>> CoreLogic::DataProcessing::ActorStorage::po_notes_;
std::shared_ptr<std::map<int, std::vector<std::shared_ptr<CoreLogic::EventManagement::Object::LevelSwitch>>>> CoreLogic::DataProcessing::ActorStorage::po_levelSwitches_;
std::shared_ptr<std::map<int, std::vector<std::shared_ptr<CoreLogic::EventManagement::Object::Uplink>>>> CoreLogic::DataProcessing::ActorStorage::po_uplinks_;
std::shared_ptr<std::map<int, std::vector<std::shared_ptr<CoreLogic::EventManagement::Object::DroneRespawnPoint>>>> CoreLogic::DataProcessing::ActorStorage::po_respawnPoints_;


std::vector<CoreLogic::UserInterface::Sprite> CoreLogic::DataProcessing::SpriteStorage::po_sprites_;


CoreLogic::DataProcessing::GameState CoreLogic::DataProcessing::StateMachine::previousState_;
CoreLogic::DataProcessing::GameState CoreLogic::DataProcessing::StateMachine::currentState_;



void CoreLogic::DataProcessing::TileMap::Initialize()
{
    if (po_tileMap_ == nullptr)
    {
        po_tileMap_ = std::make_shared<Texture2D>(LoadTexture("assets/graphics/Tile_Atlas_.png"));
    }
}


void CoreLogic::DataProcessing::ActorStorage::Initialize()
{
    std::map<CoreLogic::EventManagement::Actors::Drone::DroneType, bool> map = {
            {CoreLogic::EventManagement::Actors::Drone::DroneType::WORKER, false},
            {CoreLogic::EventManagement::Actors::Drone::DroneType::SCOUT, false},};

    po_unlockedDrones_ = std::make_shared<std::map<CoreLogic::EventManagement::Actors::Drone::DroneType, bool>>(map);

    //------------------actives------------------//
    po_activeRespawnPoint_ = nullptr;
    po_activeTutorialBox_ = nullptr;
    po_activeNote_ = nullptr;

    po_player_ = nullptr;

    //------------------general lists------------------//
    po_layers_ = std::make_shared<std::map<int, std::vector<tson::Layer>>>();
    currentElevationLevels_ = 1;
    currentLevelID_ = 0;

    po_allActors_ = std::make_shared<std::map<int, std::vector<std::shared_ptr<EventManagement::Actor>>>>();
    po_collidables_ = std::make_shared<std::map<int, std::vector<std::shared_ptr<EventManagement::Actor>>>>();
    //does not include Cliffs
    po_visibles_ = std::make_shared<std::map<int, std::vector<std::shared_ptr<EventManagement::Actor>>>>();
    //does not include barrels
    po_allAbilities_ = std::make_shared<std::map<int, std::vector<std::shared_ptr<EventManagement::Object::Ability>>>>();
    po_workerAbilities_ = std::make_shared<std::map<int, std::vector<std::shared_ptr<EventManagement::Object::Ability>>>>();
    po_scoutAbilities_ = std::make_shared<std::map<int, std::vector<std::shared_ptr<EventManagement::Object::Ability>>>>();
    po_interactions_ = std::make_shared<std::map<int, std::vector<std::shared_ptr<EventManagement::Object::Interaction>>>>();
    po_allEnemies_ = std::make_shared<std::map<int, std::vector<std::shared_ptr<EventManagement::Actors::Enemy>>>>();


    //------------------specific lists------------------//
    po_barriers_ = std::make_shared<std::map<int, std::vector<std::shared_ptr<EventManagement::Object::Barrier>>>>();
    po_rubbles_ = std::make_shared<std::map<int, std::vector<std::shared_ptr<EventManagement::Object::Rubble>>>>();;
    po_boulders_ = std::make_shared<std::map<int, std::vector<std::shared_ptr<EventManagement::Object::Boulder>>>>();
    po_vines_ = std::make_shared<std::map<int, std::vector<std::shared_ptr<EventManagement::Object::Vine>>>>();
    po_jumpPoints_ = std::make_shared<std::map<int, std::vector<std::shared_ptr<EventManagement::Object::JumpPoint>>>>();
    po_colonists_ = std::make_shared<std::map<int, std::vector<std::shared_ptr<EventManagement::Actors::Colonist>>>>();
    po_mechs_ = std::make_shared<std::map<int, std::vector<std::shared_ptr<EventManagement::Actors::Mech>>>>();
    po_cliffs_ = std::make_shared<std::map<int, std::vector<std::shared_ptr<EventManagement::Object::Cliff>>>>();
    po_barrels_ = std::make_shared<std::map<int, std::vector<std::shared_ptr<EventManagement::Object::Barrel>>>>();
    po_tutorialBoxes_ = std::make_shared<std::map<int, std::vector<std::shared_ptr<EventManagement::Object::TutorialBox>>>>();
    po_notes_ = std::make_shared<std::map<int, std::vector<std::shared_ptr<EventManagement::Object::Note>>>>();
    po_levelSwitches_ = std::make_shared<std::map<int, std::vector<std::shared_ptr<EventManagement::Object::LevelSwitch>>>>();
    po_uplinks_ = std::make_shared<std::map<int, std::vector<std::shared_ptr<EventManagement::Object::Uplink>>>>();
    po_respawnPoints_ = std::make_shared<std::map<int, std::vector<std::shared_ptr<EventManagement::Object::DroneRespawnPoint>>>>();


}

void CoreLogic::DataProcessing::ActorStorage::Initialize(int pa_elevationLevels, int pa_levelID)
{
//    CoreLogic::DataProcessing::ActorStorage::Initialize();
    DataProcessing::ActorStorage::setCurrentElevationLevels(pa_elevationLevels);
    DataProcessing::ActorStorage::setCurrentLevelID(pa_levelID);
    DataProcessing::ActorStorage::setLayers(initializeSpecificLists<tson::Layer>(pa_elevationLevels));
    DataProcessing::ActorStorage::setActors(initializeSpecificLists<std::shared_ptr<EventManagement::Actor>>(pa_elevationLevels));
    DataProcessing::ActorStorage::setCollidables(initializeSpecificLists<std::shared_ptr<EventManagement::Actor>>(pa_elevationLevels));
    DataProcessing::ActorStorage::setVisibles(initializeSpecificLists<std::shared_ptr<EventManagement::Actor>>(pa_elevationLevels));
    DataProcessing::ActorStorage::setAbilities(initializeSpecificLists<std::shared_ptr<EventManagement::Object::Ability>>(pa_elevationLevels));
    DataProcessing::ActorStorage::setWorkerAbilities(initializeSpecificLists<std::shared_ptr<EventManagement::Object::Ability>>(pa_elevationLevels));
    DataProcessing::ActorStorage::setScoutAbilities(initializeSpecificLists<std::shared_ptr<EventManagement::Object::Ability>>(pa_elevationLevels));
    DataProcessing::ActorStorage::setInteractions
            (initializeSpecificLists<std::shared_ptr<EventManagement::Object::Interaction>>(pa_elevationLevels));
    DataProcessing::ActorStorage::setEnemies(initializeSpecificLists<std::shared_ptr<EventManagement::Actors::Enemy>>(pa_elevationLevels));
    DataProcessing::ActorStorage::setBarriers(initializeSpecificLists<std::shared_ptr<EventManagement::Object::Barrier>>(pa_elevationLevels));
    DataProcessing::ActorStorage::setRubbles(initializeSpecificLists<std::shared_ptr<EventManagement::Object::Rubble>>(pa_elevationLevels));
    DataProcessing::ActorStorage::setBoulders(initializeSpecificLists<std::shared_ptr<EventManagement::Object::Boulder>>(pa_elevationLevels));
    DataProcessing::ActorStorage::setVines(initializeSpecificLists<std::shared_ptr<EventManagement::Object::Vine>>(pa_elevationLevels));
    DataProcessing::ActorStorage::setJumpPoints
            (initializeSpecificLists<std::shared_ptr<EventManagement::Object::JumpPoint>>(pa_elevationLevels));
    DataProcessing::ActorStorage::setColonists(initializeSpecificLists<std::shared_ptr<EventManagement::Actors::Colonist>>(pa_elevationLevels));
    DataProcessing::ActorStorage::setMechs(initializeSpecificLists<std::shared_ptr<EventManagement::Actors::Mech>>(pa_elevationLevels));
    DataProcessing::ActorStorage::setCliffs(initializeSpecificLists<std::shared_ptr<EventManagement::Object::Cliff>>(pa_elevationLevels));
    DataProcessing::ActorStorage::setBarrels(initializeSpecificLists<std::shared_ptr<EventManagement::Object::Barrel>>(pa_elevationLevels));
    DataProcessing::ActorStorage::setTutorialBoxes(initializeSpecificLists<std::shared_ptr<EventManagement::Object::TutorialBox>>(pa_elevationLevels));
    DataProcessing::ActorStorage::setNotes(initializeSpecificLists<std::shared_ptr<EventManagement::Object::Note>>(pa_elevationLevels));
    DataProcessing::ActorStorage::setLevelSwitches(initializeSpecificLists<std::shared_ptr<EventManagement::Object::LevelSwitch>>(pa_elevationLevels));
    DataProcessing::ActorStorage::setUplinks(initializeSpecificLists<std::shared_ptr<EventManagement::Object::Uplink>>(pa_elevationLevels));
}

// Base template for regular types (e.g., tson::Layer)
template <typename T>
typename std::enable_if<!std::is_pointer<T>::value && !std::is_same<T, std::shared_ptr<typename std::remove_reference<T>::type>>::value,
        std::shared_ptr<std::map<int, std::vector<T>>>>::type
CoreLogic::DataProcessing::ActorStorage::initializeSpecificLists(int pa_elevationLevels)
{
    auto list = std::make_shared<std::map<int, std::vector<T>>>();

    for (int i = 0; i < pa_elevationLevels; ++i)
    {
        (*list)[i] = std::vector<T>();  // Initialize with an empty vector of type T
    }

    (*list)[9] = std::vector<T>();  // Initialize elevation 9 for debug purposes

    return list;
}

// Specialized template for shared_ptr types
template <typename T>
typename std::enable_if<std::is_same<T, std::shared_ptr<typename std::remove_reference<T>::type>>::value,
        std::shared_ptr<std::map<int, std::vector<T>>>>::type
CoreLogic::DataProcessing::ActorStorage::initializeSpecificLists(int pa_elevationLevels)
{
    auto list = std::make_shared<std::map<int, std::vector<T>>>();

    for (int i = 0; i < pa_elevationLevels; ++i)
    {
        (*list)[i] = std::vector<T>();  // Initialize with an empty vector of shared_ptr<T>
    }

    (*list)[9] = std::vector<T>();  // Initialize elevation 9 for debug purposes


    return list;
}

std::shared_ptr<CoreLogic::EventManagement::Actors::Drone> CoreLogic::DataProcessing::ActorStorage::getPlayer() {return po_player_;}

std::shared_ptr<std::map<int, std::vector<std::shared_ptr<CoreLogic::EventManagement::Actor>>>> CoreLogic::DataProcessing::ActorStorage::getActors() {return po_allActors_;}

std::shared_ptr<std::map<int, std::vector<tson::Layer>>> CoreLogic::DataProcessing::ActorStorage::getLayers() {return po_layers_;}

int CoreLogic::DataProcessing::ActorStorage::getCurrentElevationLevels(){return currentElevationLevels_;};


/**
 * @brief: Zum hinzufügen von Actors, die als tson::Object's aus der Map geladen werden
 **/
void CoreLogic::DataProcessing::ActorStorage::setActors(
        std::shared_ptr<std::map<int, std::vector<std::shared_ptr<EventManagement::Actor>>>> pa_actors)
{
    po_allActors_ = pa_actors;
}

template <typename T>
void CoreLogic::DataProcessing::ActorStorage::addActor(std::shared_ptr<std::map<int, std::vector<std::shared_ptr<T>>>> pa_map, int pa_elevation,
        std::shared_ptr<T> pa_actor) {
    if (pa_map == nullptr) {
        return;
    }
    if (!(*pa_map).empty()) {
        auto it = pa_map->find(pa_elevation);
        if (it != pa_map->end()) {
            it->second.push_back(pa_actor);
        } else {
            pa_map->insert({pa_elevation, {pa_actor}});
        }
    } else {
        pa_map->insert({pa_elevation, {pa_actor}});
    }
}

void CoreLogic::DataProcessing::ActorStorage::setLayers(std::shared_ptr<std::map<int, std::vector<tson::Layer>>> pa_layers)
{
    po_layers_ = pa_layers;
}

void CoreLogic::DataProcessing::ActorStorage::setCurrentElevationLevels(int pa_currentElevationLayers)
{
    currentElevationLevels_ = pa_currentElevationLayers;
}

void CoreLogic::DataProcessing::ActorStorage::setCurrentLevelID(int pa_currentLevelID)
{
    currentLevelID_ = pa_currentLevelID;
}

void CoreLogic::DataProcessing::ActorStorage::setPlayer(std::shared_ptr<EventManagement::Actors::Drone> pa_player) {
    po_player_.reset();
    std::shared_ptr<EventManagement::Actors::Drone> old_player = po_player_; //for debug
    po_player_ = nullptr;
    std::shared_ptr<EventManagement::Actors::Drone> debug_player = po_player_;
    po_player_ = pa_player;
}


void CoreLogic::DataProcessing::ActorStorage::addActorByType(int pa_elevation,
        std::shared_ptr<EventManagement::Actor> pa_actor)
{
    if (auto barrier = std::dynamic_pointer_cast<EventManagement::Object::Barrier>(pa_actor))
    {
        addActor(po_barriers_, pa_elevation, barrier);

        auto actor = std::dynamic_pointer_cast<EventManagement::Actor>(pa_actor);
        addActor(po_collidables_, pa_elevation, actor);
        addActor(po_allActors_, pa_elevation, actor);

    } else if (auto rubble = std::dynamic_pointer_cast<EventManagement::Object::Rubble>(pa_actor))
    {
        addActor(po_rubbles_, pa_elevation, rubble);

        auto ability = std::dynamic_pointer_cast<EventManagement::Object::Ability>(pa_actor);
        addActor(po_allAbilities_, pa_elevation, ability);
        addActor(po_workerAbilities_, pa_elevation, ability);

        auto actor = std::dynamic_pointer_cast<EventManagement::Actor>(pa_actor);
        addActor(po_collidables_, pa_elevation, actor);
        addActor(po_visibles_, pa_elevation, actor);
        addActor(po_allActors_, pa_elevation, actor);

    } else if (auto boulder = std::dynamic_pointer_cast<EventManagement::Object::Boulder>(pa_actor))
    {
        addActor(po_boulders_, pa_elevation, boulder);

        auto ability = std::dynamic_pointer_cast<EventManagement::Object::Ability>(pa_actor);
        addActor(po_allAbilities_, pa_elevation, ability);
        addActor(po_workerAbilities_, pa_elevation, ability);

        auto actor = std::dynamic_pointer_cast<EventManagement::Actor>(pa_actor);
        addActor(po_collidables_, pa_elevation, actor);
        addActor(po_visibles_, pa_elevation, actor);
        addActor(po_allActors_, pa_elevation, actor);

    } else if (auto vine = std::dynamic_pointer_cast<EventManagement::Object::Vine>(pa_actor))
    {
        addActor(po_vines_, pa_elevation, vine);

        auto interaction = std::dynamic_pointer_cast<EventManagement::Object::Interaction>(pa_actor);
        addActor(po_interactions_, pa_elevation, interaction);

        auto actor = std::dynamic_pointer_cast<EventManagement::Actor>(pa_actor);
        addActor(po_allActors_, pa_elevation, actor);

    } else if (auto jumpPoint = std::dynamic_pointer_cast<EventManagement::Object::JumpPoint>(pa_actor))
    {
        addActor(po_jumpPoints_, pa_elevation, jumpPoint);

        auto ability = std::dynamic_pointer_cast<EventManagement::Object::Ability>(pa_actor);
        addActor(po_allAbilities_, pa_elevation, ability);
        addActor(po_scoutAbilities_, pa_elevation, ability);

        auto actor = std::dynamic_pointer_cast<EventManagement::Actor>(pa_actor);
        addActor(po_allActors_, pa_elevation, actor);

    } else if (auto colonist = std::dynamic_pointer_cast<EventManagement::Actors::Colonist>(pa_actor))
    {
        addActor(po_colonists_, pa_elevation, colonist);

        auto enemy = std::dynamic_pointer_cast<EventManagement::Actors::Enemy>(pa_actor);
        addActor(po_allEnemies_, pa_elevation, enemy);

        auto actor = std::dynamic_pointer_cast<EventManagement::Actor>(pa_actor);
        addActor(po_visibles_, pa_elevation, actor);
        addActor(po_collidables_, pa_elevation, actor);
        addActor(po_allActors_, pa_elevation, actor);

    } else if (auto cliff = std::dynamic_pointer_cast<EventManagement::Object::Cliff>(pa_actor))
    {
        addActor(po_cliffs_, pa_elevation, cliff);

        auto actor = std::dynamic_pointer_cast<EventManagement::Actor>(pa_actor);
        addActor(po_allActors_, pa_elevation, actor);

    } else if (auto barrel = std::dynamic_pointer_cast<EventManagement::Object::Barrel>(pa_actor))
    {
        addActor(po_barrels_, pa_elevation, barrel);

        auto ability = std::dynamic_pointer_cast<EventManagement::Object::Ability>(pa_actor);
        addActor(po_workerAbilities_, pa_elevation, ability);

        auto actor = std::dynamic_pointer_cast<EventManagement::Actor>(pa_actor);
        addActor(po_collidables_, pa_elevation, actor);
        addActor(po_allActors_, pa_elevation, actor);

    } else if (auto tutorialBox = std::dynamic_pointer_cast<EventManagement::Object::TutorialBox>(pa_actor))
    {
        addActor(po_tutorialBoxes_, pa_elevation, tutorialBox);

        auto actor = std::dynamic_pointer_cast<EventManagement::Actor>(pa_actor);
        addActor(po_allActors_, pa_elevation, actor);

    } else if (auto note = std::dynamic_pointer_cast<EventManagement::Object::Note>(pa_actor))
    {
        addActor(po_notes_, pa_elevation, note);

        auto interaction = std::dynamic_pointer_cast<EventManagement::Object::Interaction>(pa_actor);
        addActor(po_interactions_, pa_elevation, interaction);

        auto actor = std::dynamic_pointer_cast<EventManagement::Actor>(pa_actor);
        addActor(po_allActors_, pa_elevation, actor);

    } else if (auto levelSwitch = std::dynamic_pointer_cast<EventManagement::Object::LevelSwitch>(pa_actor))
    {
        addActor(po_levelSwitches_, pa_elevation, levelSwitch);

        auto actor = std::dynamic_pointer_cast<EventManagement::Actor>(pa_actor);
        addActor(po_allActors_, pa_elevation, actor);

    } else if (auto uplink = std::dynamic_pointer_cast<EventManagement::Object::Uplink>(pa_actor))
    {
        addActor(po_uplinks_, pa_elevation, uplink);

        auto actor = std::dynamic_pointer_cast<EventManagement::Actor>(pa_actor);
        addActor(po_collidables_, pa_elevation, actor);
        addActor(po_visibles_, pa_elevation, actor);
        addActor(po_allActors_, pa_elevation, actor);

    }else if (auto spawn = std::dynamic_pointer_cast<EventManagement::Object::DroneRespawnPoint>(pa_actor))
    {
        bool activeSpawn = false;
        if (spawn->getRespawnState() == EventManagement::Object::DroneRespawnPoint::DroneRespawnPointState::ACTIVATED)
        {
            activeSpawn = true;
        }
        addActor(po_respawnPoints_, pa_elevation, spawn);

        auto interaction = std::dynamic_pointer_cast<EventManagement::Object::Interaction>(pa_actor);
        addActor(po_interactions_, pa_elevation, interaction);

        auto actor = std::dynamic_pointer_cast<EventManagement::Actor>(pa_actor);
        addActor(po_visibles_, pa_elevation, actor);
        addActor(po_allActors_, pa_elevation, actor);
        if (activeSpawn)
        {
            po_activeRespawnPoint_ = spawn;
        }
    } else if (auto mech = std::dynamic_pointer_cast<EventManagement::Actors::Mech>(pa_actor)) {
        addActor(po_mechs_, pa_elevation, mech);

        auto enemy = std::dynamic_pointer_cast<EventManagement::Actors::Enemy>(pa_actor);
        addActor(po_allEnemies_, pa_elevation, enemy);

        auto actor = std::dynamic_pointer_cast<EventManagement::Actor>(pa_actor);
        addActor(po_visibles_, pa_elevation, actor);
        addActor(po_collidables_, pa_elevation, actor);
        addActor(po_allActors_, pa_elevation, actor);

    }
}

std::shared_ptr<CoreLogic::EventManagement::Object::DroneRespawnPoint>
CoreLogic::DataProcessing::ActorStorage::getActiveSpawnPoint()
{
    return po_activeRespawnPoint_;
}

std::shared_ptr<CoreLogic::EventManagement::Object::TutorialBox>
CoreLogic::DataProcessing::ActorStorage::getActiveTutorialBox()
{
    return po_activeTutorialBox_;
}

std::shared_ptr<CoreLogic::EventManagement::Object::Note> CoreLogic::DataProcessing::ActorStorage::getActiveNote()
{
    return po_activeNote_;
}

void CoreLogic::DataProcessing::ActorStorage::setActiveSpawnPoint(
        std::shared_ptr<CoreLogic::EventManagement::Object::DroneRespawnPoint> pa_spawnPoint)
{
    po_activeRespawnPoint_ = pa_spawnPoint;
}

void CoreLogic::DataProcessing::ActorStorage::setActiveTutorialBox(
        std::shared_ptr<CoreLogic::EventManagement::Object::TutorialBox> pa_tutorialBox)
{
    po_activeTutorialBox_ = pa_tutorialBox;
}

void CoreLogic::DataProcessing::ActorStorage::setActiveNote(
        std::shared_ptr<CoreLogic::EventManagement::Object::Note> pa_activeNote)
{
    po_activeNote_ = pa_activeNote;
}

std::shared_ptr<std::map<int, std::vector<std::shared_ptr<CoreLogic::EventManagement::Actor>>>>
CoreLogic::DataProcessing::ActorStorage::getCollidables()
{
    return po_collidables_;
}

void CoreLogic::DataProcessing::ActorStorage::setCollidables(
        std::shared_ptr<std::map<int, std::vector<std::shared_ptr<EventManagement::Actor>>>> pa_collidables)
{
po_collidables_ = pa_collidables;
}

std::shared_ptr<std::map<int, std::vector<std::shared_ptr<CoreLogic::EventManagement::Actor>>>>
CoreLogic::DataProcessing::ActorStorage::getVisibles()
{
    return po_visibles_;
}

void CoreLogic::DataProcessing::ActorStorage::setVisibles(
        std::shared_ptr<std::map<int, std::vector<std::shared_ptr<EventManagement::Actor>>>> pa_visibles)
{
    po_visibles_ = pa_visibles;
}
void CoreLogic::DataProcessing::ActorStorage::changeDrawingElevation(std::shared_ptr<CoreLogic::EventManagement::Actor> pa_actor, int pa_newElevation)
{
    auto &vec = po_visibles_->at(pa_actor->getElevation());
    for (auto it = vec.begin(); it != vec.end(); ++it) {
        if (*it == pa_actor) {
            vec.erase(it);
            break;
        }
    }
    po_visibles_->at(pa_newElevation).push_back(pa_actor);

}


std::shared_ptr<std::map<int, std::vector<std::shared_ptr<CoreLogic::EventManagement::Object::Ability>>>>
CoreLogic::DataProcessing::ActorStorage::getAbilities()
{
    return po_allAbilities_;
}

void CoreLogic::DataProcessing::ActorStorage::setAbilities(
        std::shared_ptr<std::map<int, std::vector<std::shared_ptr<EventManagement::Object::Ability>>>> pa_abilities)
{
po_allAbilities_ = pa_abilities;
}

std::shared_ptr<std::map<int, std::vector<std::shared_ptr<CoreLogic::EventManagement::Object::Ability>>>>
CoreLogic::DataProcessing::ActorStorage::getWorkerAbilities()
{
    return po_workerAbilities_;
}

void CoreLogic::DataProcessing::ActorStorage::setWorkerAbilities(
        std::shared_ptr<std::map<int, std::vector<std::shared_ptr<EventManagement::Object::Ability>>>> pa_workerAbilities)
{
po_workerAbilities_ = pa_workerAbilities;
}

std::shared_ptr<std::map<int, std::vector<std::shared_ptr<CoreLogic::EventManagement::Object::Ability>>>>
CoreLogic::DataProcessing::ActorStorage::getScoutAbilities()
{
    return po_scoutAbilities_;
}

void CoreLogic::DataProcessing::ActorStorage::setScoutAbilities(
        std::shared_ptr<std::map<int, std::vector<std::shared_ptr<EventManagement::Object::Ability>>>> pa_scoutAbilities)
{
po_scoutAbilities_ = pa_scoutAbilities;
}

std::shared_ptr<std::map<int, std::vector<std::shared_ptr<CoreLogic::EventManagement::Object::Interaction>>>>
CoreLogic::DataProcessing::ActorStorage::getInteractions()
{
    auto interacts = po_interactions_;
    return po_interactions_;
}

void CoreLogic::DataProcessing::ActorStorage::setInteractions(
        std::shared_ptr<std::map<int, std::vector<std::shared_ptr<EventManagement::Object::Interaction>>>> pa_interactions)
{
po_interactions_ = pa_interactions;
}

std::shared_ptr<std::map<int, std::vector<std::shared_ptr<CoreLogic::EventManagement::Actors::Enemy>>>>
CoreLogic::DataProcessing::ActorStorage::getEnemies()
{
    auto enem = po_allEnemies_;
    return po_allEnemies_;
}

void CoreLogic::DataProcessing::ActorStorage::setEnemies(
        std::shared_ptr<std::map<int, std::vector<std::shared_ptr<EventManagement::Actors::Enemy>>>> pa_enemies)
{
    po_allEnemies_ = pa_enemies;
}

std::shared_ptr<std::map<int, std::vector<std::shared_ptr<CoreLogic::EventManagement::Object::Barrier>>>>
CoreLogic::DataProcessing::ActorStorage::getBarriers()
{
    return po_barriers_;
}

void CoreLogic::DataProcessing::ActorStorage::setBarriers(
        std::shared_ptr<std::map<int, std::vector<std::shared_ptr<EventManagement::Object::Barrier>>>> pa_barriers)
{
po_barriers_ = pa_barriers;
}

std::shared_ptr<std::map<int, std::vector<std::shared_ptr<CoreLogic::EventManagement::Object::Rubble>>>>
CoreLogic::DataProcessing::ActorStorage::getRubbles()
{
    return po_rubbles_;
}

void CoreLogic::DataProcessing::ActorStorage::setRubbles(
        std::shared_ptr<std::map<int, std::vector<std::shared_ptr<EventManagement::Object::Rubble>>>> pa_rubbles)
{
po_rubbles_ = pa_rubbles;
}

std::shared_ptr<std::map<int, std::vector<std::shared_ptr<CoreLogic::EventManagement::Object::Boulder>>>>
CoreLogic::DataProcessing::ActorStorage::getBoulders()
{
    return po_boulders_;
}

void CoreLogic::DataProcessing::ActorStorage::setBoulders(
        std::shared_ptr<std::map<int, std::vector<std::shared_ptr<EventManagement::Object::Boulder>>>> pa_boulders)
{
po_boulders_ = pa_boulders;
}

std::shared_ptr<std::map<int, std::vector<std::shared_ptr<CoreLogic::EventManagement::Object::Vine>>>>
CoreLogic::DataProcessing::ActorStorage::getVines()
{
    return po_vines_;
}

void CoreLogic::DataProcessing::ActorStorage::setVines(
        std::shared_ptr<std::map<int, std::vector<std::shared_ptr<EventManagement::Object::Vine>>>> pa_vines)
{
po_vines_ = pa_vines;
}

std::shared_ptr<std::map<int, std::vector<std::shared_ptr<CoreLogic::EventManagement::Object::JumpPoint>>>>
CoreLogic::DataProcessing::ActorStorage::getJumpPoints()
{
    return po_jumpPoints_;
}

void CoreLogic::DataProcessing::ActorStorage::setJumpPoints(
        std::shared_ptr<std::map<int, std::vector<std::shared_ptr<EventManagement::Object::JumpPoint>>>> pa_jumpPoints)
{
po_jumpPoints_ = pa_jumpPoints;
}

std::shared_ptr<std::map<int, std::vector<std::shared_ptr<CoreLogic::EventManagement::Actors::Colonist>>>>
CoreLogic::DataProcessing::ActorStorage::getColonists()
{
    return po_colonists_;
}

void CoreLogic::DataProcessing::ActorStorage::setColonists(
        std::shared_ptr<std::map<int, std::vector<std::shared_ptr<EventManagement::Actors::Colonist>>>> pa_colonists)
{
po_colonists_ = pa_colonists;
}

std::shared_ptr<std::map<int, std::vector<std::shared_ptr<CoreLogic::EventManagement::Actors::Mech>>>>
CoreLogic::DataProcessing::ActorStorage::getMechs()
{
    return po_mechs_;
}

void CoreLogic::DataProcessing::ActorStorage::setMechs(
        std::shared_ptr<std::map<int, std::vector<std::shared_ptr<EventManagement::Actors::Mech>>>> pa_mechs)
{
    po_mechs_ = pa_mechs;
}

std::shared_ptr<std::map<int, std::vector<std::shared_ptr<CoreLogic::EventManagement::Object::Cliff>>>>
CoreLogic::DataProcessing::ActorStorage::getCliffs()
{
    return po_cliffs_;
}

void CoreLogic::DataProcessing::ActorStorage::setCliffs(
        std::shared_ptr<std::map<int, std::vector<std::shared_ptr<EventManagement::Object::Cliff>>>> pa_cliffs)
{
po_cliffs_ = pa_cliffs;
}

std::shared_ptr<std::map<int, std::vector<std::shared_ptr<CoreLogic::EventManagement::Object::Barrel>>>>
CoreLogic::DataProcessing::ActorStorage::getBarrels()
{
    return po_barrels_;
}

void CoreLogic::DataProcessing::ActorStorage::setBarrels(
        std::shared_ptr<std::map<int, std::vector<std::shared_ptr<EventManagement::Object::Barrel>>>> pa_barrels)
{
po_barrels_ = pa_barrels;
}

std::shared_ptr<std::map<int, std::vector<std::shared_ptr<CoreLogic::EventManagement::Object::TutorialBox>>>>
CoreLogic::DataProcessing::ActorStorage::getTutorialBoxes()
{
    return po_tutorialBoxes_;
}

void CoreLogic::DataProcessing::ActorStorage::setTutorialBoxes(
        std::shared_ptr<std::map<int, std::vector<std::shared_ptr<EventManagement::Object::TutorialBox>>>> pa_tutorialBoxes)
{
po_tutorialBoxes_ = pa_tutorialBoxes;
}

std::shared_ptr<std::map<int, std::vector<std::shared_ptr<CoreLogic::EventManagement::Object::Note>>>>
CoreLogic::DataProcessing::ActorStorage::getNotes()
{
    return po_notes_;
}

void CoreLogic::DataProcessing::ActorStorage::setNotes(
        std::shared_ptr<std::map<int, std::vector<std::shared_ptr<EventManagement::Object::Note>>>> pa_notes)
{
po_notes_ = pa_notes;
}

std::shared_ptr<std::map<int, std::vector<std::shared_ptr<CoreLogic::EventManagement::Object::LevelSwitch>>>>
CoreLogic::DataProcessing::ActorStorage::getLevelSwitches()
{
    return po_levelSwitches_;
}

void CoreLogic::DataProcessing::ActorStorage::setLevelSwitches(
        std::shared_ptr<std::map<int, std::vector<std::shared_ptr<EventManagement::Object::LevelSwitch>>>> pa_levelSwitches)
{
po_levelSwitches_ = pa_levelSwitches;
}

std::shared_ptr<std::map<int, std::vector<std::shared_ptr<CoreLogic::EventManagement::Object::Uplink>>>>
CoreLogic::DataProcessing::ActorStorage::getUplinks()
{
    return po_uplinks_;
}

void CoreLogic::DataProcessing::ActorStorage::setUplinks(
        std::shared_ptr<std::map<int, std::vector<std::shared_ptr<EventManagement::Object::Uplink>>>> pa_uplinks)
{
po_uplinks_ = pa_uplinks;
}

void CoreLogic::DataProcessing::ActorStorage::unlockDrone(CoreLogic::EventManagement::Actors::Drone::DroneType pa_droneType)
{
    if (po_unlockedDrones_->find(pa_droneType) != po_unlockedDrones_->end())
        po_unlockedDrones_->at(pa_droneType) = true;
}

std::shared_ptr<std::map<CoreLogic::EventManagement::Actors::Drone::DroneType, bool>>
CoreLogic::DataProcessing::ActorStorage::getUnlockedDrones()
{
    return po_unlockedDrones_;
}

void CoreLogic::DataProcessing::ActorStorage::setUnlockedDrones(
        std::shared_ptr<std::map<CoreLogic::EventManagement::Actors::Drone::DroneType, bool>> pa_unlockedDrones)
{
    po_unlockedDrones_ = pa_unlockedDrones;
}

bool CoreLogic::DataProcessing::ActorStorage::isDroneUnlocked(
        CoreLogic::EventManagement::Actors::Drone::DroneType pa_droneType)
{
        return po_unlockedDrones_->at(pa_droneType);
}


CoreLogic::DataProcessing::GameState CoreLogic::DataProcessing::StateMachine::getCurrentState()
{
    return currentState_;
}

int CoreLogic::DataProcessing::ActorStorage::getCurrentLevelID()
{
    return currentLevelID_;
}

void CoreLogic::DataProcessing::StateMachine::changeState(CoreLogic::DataProcessing::GameState newState)
{
    previousState_ = currentState_;
    currentState_ = newState;
}

CoreLogic::DataProcessing::GameState CoreLogic::DataProcessing::StateMachine::getPreviousState()
{
    return previousState_;
}

void CoreLogic::DataProcessing::StateMachine::Initialize()
{
    currentState_ = IN_GAME;
    previousState_ = IN_GAME;
}

CoreLogic::UserInterface::Sprite
CoreLogic::DataProcessing::SpriteStorage::getSprite(CoreLogic::DataProcessing::SpriteStorage::SpriteEnum spriteEnum)
{
    return po_sprites_[spriteEnum];
}

void CoreLogic::DataProcessing::SpriteStorage::Initialize()
{
    po_sprites_.resize(40);
    //0 - worker
    UserInterface::Sprite sprite = UserInterface::Sprite("assets/graphics/SpriteSheets/hive_ARTI_Worker-Spritesheet.png",
            {
                    {    //0 - walking
                        {CoreLogic::UserInterface::AnimationState {1 * 38, 38, 38, 8, {-3, -3}}}, //up
                        {CoreLogic::UserInterface::AnimationState {0 * 38, 38, 38, 8, {-3, -3}}}, //down
                        {CoreLogic::UserInterface::AnimationState {3 * 38, 38, 38, 8, {-3, -3}}}, //left
                        {CoreLogic::UserInterface::AnimationState {2 * 38, 38, 38, 8, {-3, -3}}}, //right
                    },
                    {    //1 - ability
                            {CoreLogic::UserInterface::AnimationState {5 * 38, 38, 38, 8, {-3, -3}}}, //up
                            {CoreLogic::UserInterface::AnimationState {4 * 38, 38, 38, 8, {-3, -3}}}, //down
                            {CoreLogic::UserInterface::AnimationState {7 * 38, 38, 38, 8, {-3, -3}}}, //left
                            {CoreLogic::UserInterface::AnimationState {6 * 38, 38, 38, 8, {-3, -3}}}, //right
                    },
                    {    //2 - death
                        {CoreLogic::UserInterface::AnimationState {8 * 38, 38, 38, 12, {-3, -3}}},
                    }
            });

    po_sprites_[WORKER_DRONE] = sprite;

    //1 - scout
    sprite = UserInterface::Sprite("assets/graphics/SpriteSheets/hive_ARTI_Scout-Spritesheet_2024-09-12.png",
            {
                    {    //0 - walking
                            {CoreLogic::UserInterface::AnimationState {1 * 38, 38, 38, 5}}, //up
                            {CoreLogic::UserInterface::AnimationState {0 * 38, 38, 38, 8}}, //down
                            {CoreLogic::UserInterface::AnimationState {2 * 38, 38, 38, 8}}, //left
                            {CoreLogic::UserInterface::AnimationState {3 * 38, 38, 38, 8}}, //right
                    },
                    {},  //1- ability; not handled via Sprites
                    {    //2 - death
                            {CoreLogic::UserInterface::AnimationState {(4 * 38) + (2 * 38), 38, 38, 12}},
                    },
                    {   //3 - death ability
                            {CoreLogic::UserInterface::AnimationState {4 * 38, 2 * 38, 2 * 38, 12, {-22, -27}}},
                    }
            });

    po_sprites_[SCOUT_DRONE] = sprite;

    //2 - colonist
    sprite = UserInterface::Sprite("assets/graphics/SpriteSheets/hive_ARTI_Colonist-Spritesheet.png",
            {
                    {    //0 - idle
                            {CoreLogic::UserInterface::AnimationState {1 * 48, 24, 48, 12}}, //up
                            {CoreLogic::UserInterface::AnimationState {0 * 48, 24, 48, 12}}, //down
                            {CoreLogic::UserInterface::AnimationState {3 * 48, 24, 48, 12}}, //left
                            {CoreLogic::UserInterface::AnimationState {2 * 48, 24, 48, 12}}, //right
                    },
                    {    //1 - alert
                            {CoreLogic::UserInterface::AnimationState {(4 * 48) + (1 * 72), 24, 72, 6, {0, -24}}}, //up
                            {CoreLogic::UserInterface::AnimationState {(4 * 48) + (0 * 72), 24, 72, 6, {0, -24}}}, //down
                            {CoreLogic::UserInterface::AnimationState {(4 * 48) + (3 * 72), 24, 72, 6, {0, -24}}}, //left
                            {CoreLogic::UserInterface::AnimationState {(4 * 48) + (2 * 72), 24, 72, 6, {0, -24}}}, //right
                    },
                    {    //2 - shoot
                            {CoreLogic::UserInterface::AnimationState {(4 * 48) + (5 * 72), 24, 72, 4, {0, -24}}}, //up
                            {CoreLogic::UserInterface::AnimationState {(4 * 48) + (4 * 72), 24, 72, 4, {0, -24}}}, //down
                            {CoreLogic::UserInterface::AnimationState {(4 * 48) + (7 * 72), 24, 72, 4, {0, -24}}}, //left
                            {CoreLogic::UserInterface::AnimationState {(4 * 48) + (6 * 72), 24, 72, 4, {0, -24}}}, //right
                    },
                    {    //3 - death
                            {CoreLogic::UserInterface::AnimationState {(4 * 48) + (8 * 72), 72, 72, 6}},
                    }
            });

    po_sprites_[COLONIST] = sprite;

    //3 - mech
    sprite = UserInterface::Sprite("assets/graphics/SpriteSheets/hive_ARTI_Mech-Spritesheet_2024-09-13.png",
            {
                    {    //0 - idle
                            {CoreLogic::UserInterface::AnimationState {3 * (3 * 24), 48, 72, 12}}, //up
                            {CoreLogic::UserInterface::AnimationState {0 * (3 * 24), 48, 72, 12}}, //down
                            {CoreLogic::UserInterface::AnimationState {1 * (3 * 24), 48, 72, 12}}, //left
                            {CoreLogic::UserInterface::AnimationState {2 * (3 * 24), 48, 72, 12}}, //right
                    },
                    {    //1 - alert
                            {CoreLogic::UserInterface::AnimationState {(4 * (3 * 24) + (3 * (4 * 24))), 48, 72 + 24, 6,
                                    {0,
                                    -24}}}, //up
                            {CoreLogic::UserInterface::AnimationState {(4 * (3 * 24) + (0 * (4 * 24))), 48, 72 + 24, 6,
                                    {0, -24}}}, //down
                            {CoreLogic::UserInterface::AnimationState {(4 * (3 * 24) + (1 * (4 * 24))), 48, 72 + 24, 6,
                                    {0, -24}}}, //left
                            {CoreLogic::UserInterface::AnimationState {(4 * (3 * 24) + (2 * (4 * 24))), 48, 72 + 24, 6,
                                    {0, -24}}}, //right
                    },
                    {    //2 - shoot
                            {CoreLogic::UserInterface::AnimationState {(4 * (3 * 24) + (7 * (4 * 24))), 48, 72 + 24, 6,
                                    {0, -24}}}, //up
                            {CoreLogic::UserInterface::AnimationState {(4 * (3 * 24) + (4 * (4 * 24))), 48, 72 + 24, 6,
                                    {0, -24}}}, //down
                            {CoreLogic::UserInterface::AnimationState {(4 * (3 * 24) + (5 * (4 * 24))), 48, 72 + 24, 6,
                                    {0, -24}}}, //left
                            {CoreLogic::UserInterface::AnimationState {(4 * (3 * 24) + (6 * (4 * 24))), 48, 72 + 24, 6,
                                    {0, -24}}}, //right
                    },
                    {    //3 - death
                            {CoreLogic::UserInterface::AnimationState {(4 * (3 * 24) + (8 * (4 * 24))), 48, 72, 12}},
                    }
            });

    po_sprites_[MECH] = sprite;

    //4 - rubble - overworld
    sprite = UserInterface::Sprite("assets/graphics/SpriteSheets/Abilities/hive_ARTI_Overworld-Rubble-Spritesheet.png",
            {
                    {    //0 - idle
                            {CoreLogic::UserInterface::AnimationState {0 * 24, 24, 24, 1}},
                    },
                    {    //1 - breaking
                            {CoreLogic::UserInterface::AnimationState {1 * 24, 24, 24, 11}},
                    },
            });

    po_sprites_[RUBBLE_OVERWORLD] = sprite;

    //5 - rubble - underworld
    sprite = UserInterface::Sprite("assets/graphics/SpriteSheets/Abilities/hive_ARTI_Underworld-Rubble-Spritesheet.png",
            {
                    {    //0 - idle
                            {CoreLogic::UserInterface::AnimationState {0 * 24, 24, 24, 1}},
                    },
                    {    //1 - breaking
                            {CoreLogic::UserInterface::AnimationState {1 * 24, 24, 24, 11}},
                    },
            });

    po_sprites_[RUBBLE_UNDERWORLD] = sprite;

    //6 - spawn - overworld
    sprite = UserInterface::Sprite("assets/graphics/SpriteSheets/Interacts/hive_ARTI_Overworld-Respawns-Spritesheet.png",
            {
                    {    //0 - undiscovered
                            {CoreLogic::UserInterface::AnimationState {0 * 48, 48, 48, 1}},
                    },
                    {    //1 - discovered
                            {CoreLogic::UserInterface::AnimationState {1 * 48, 48, 48, 1}},
                    },
                    {    //2 - active
                            {CoreLogic::UserInterface::AnimationState {2 * 48, 48, 48, 1}},
                    },
                    {   //3 - egg
                            {CoreLogic::UserInterface::AnimationState {3 * 48, 48, 48, 1}},
                    }
            });

    po_sprites_[SPAWN_OVERWORLD] = sprite;

    //7 - spawn - underworld
    sprite = UserInterface::Sprite("assets/graphics/SpriteSheets/Interacts/hive_ARTI_Underworld-Respawns-Spritesheet.png",
            {
                    {    //0 - undiscovered
                            {CoreLogic::UserInterface::AnimationState {0 * 48, 48, 48, 1}},
                    },
                    {    //1 - discovered
                            {CoreLogic::UserInterface::AnimationState {1 * 48, 48, 48, 1}},
                    },
                    {    //2 - active
                            {CoreLogic::UserInterface::AnimationState {2 * 48, 48, 48, 11}},
                    },
            });

    po_sprites_[SPAWN_UNDERWORLD] = sprite;

    //8 - boulder - overworld
    sprite = UserInterface::Sprite("assets/graphics/SpriteSheets/Abilities/hive_ARTI_Overworld-Boulder-Spritesheet.png",
            {
                    {    //0 - idle
                            {CoreLogic::UserInterface::AnimationState {0 * 48, 48, 48, 1}},
                    },
                    {    //1 - breaking
                            {CoreLogic::UserInterface::AnimationState {1 * 48, 96,48, 6, {-24, 0}}},
                    },
            });

    po_sprites_[BOULDER_OVERWORLD] = sprite;

    //9 - boulder - underworld
    sprite = UserInterface::Sprite("assets/graphics/SpriteSheets/Abilities/hive_ARTI_Underworld-Boulder-Spritesheet.png",
            {
                    {    //0 - idle
                            {CoreLogic::UserInterface::AnimationState {0 * 48, 48, 48, 1}},
                    },
                    {    //1 - breaking
                            {CoreLogic::UserInterface::AnimationState {1 * 48, 96,48, 6, {-24, 0}}},
                    },
            });

    po_sprites_[BOULDER_UNDERWORLD] = sprite;

    //10 - barrel
    sprite = UserInterface::Sprite("assets/graphics/SpriteSheets/hive_ARTI_Explosive-Barrel-Spritesheet.png",
            {
                    {    //0 - idle
                            {CoreLogic::UserInterface::AnimationState {0 * 24, 24, 24, 1}},
                    },
                    {    //1 - breaking
                            {CoreLogic::UserInterface::AnimationState {1 * 24, 120, 120, 11, {-48, -48}}},
                    },
            });

    po_sprites_[BARREL] = sprite;

    //11 - note
    sprite = UserInterface::Sprite("assets/graphics/SpriteSheets/Interacts/hive_ARTI_Lore-Item-Spritesheet.png",
            {
                    {    //0 - idle
                            {CoreLogic::UserInterface::AnimationState {0 * 24, 24, 24, 6}},
                    },
            });

    po_sprites_[NOTE] = sprite;

    //12 - uplink
    sprite = UserInterface::Sprite("assets/graphics/SpriteSheets/Interacts/hive_ARTI_Uplink-Spritesheet.png",
            {
                    {    //0 - idle
                            {CoreLogic::UserInterface::AnimationState {0 * 72, 48, 72, 6}},
                    },
            });

    po_sprites_[UPLINK] = sprite;


    //-----HUD-----//

    //13 - max life
    sprite = UserInterface::Sprite("assets/graphics/SpriteSheets/HUD/hive_ARTI_newHUD_max-drone-life.png",
            {
                    {CoreLogic::UserInterface::AnimationState{0 * 360, 640, 360, 1}},
                    {CoreLogic::UserInterface::AnimationState{0 * 360, 640, 360, 1}},
                    {CoreLogic::UserInterface::AnimationState{0 * 360, 640, 360, 1}},
                    {CoreLogic::UserInterface::AnimationState{1 * 360, 640, 360, 1}},
                    {CoreLogic::UserInterface::AnimationState{1 * 360, 640, 360, 1}},
                    {CoreLogic::UserInterface::AnimationState{1 * 360, 640, 360, 1}},
                    {CoreLogic::UserInterface::AnimationState{2 * 360, 640, 360, 1}}
            });

    po_sprites_[HUD_MAX_LIFE] = sprite;

    //14 - current life
    sprite = UserInterface::Sprite("assets/graphics/SpriteSheets/HUD/hive_ARTI_newHUD_current-drone-life.png",
            {
                    {CoreLogic::UserInterface::AnimationState{0 * 360, 640, 360, 1}},
                    {CoreLogic::UserInterface::AnimationState{1 * 360, 640, 360, 1}},
                    {CoreLogic::UserInterface::AnimationState{2 * 360, 640, 360, 1}},
                    {CoreLogic::UserInterface::AnimationState{3 * 360, 640, 360, 1}},
                    {CoreLogic::UserInterface::AnimationState{4 * 360, 640, 360, 1}},
                    {CoreLogic::UserInterface::AnimationState{5 * 360, 640, 360, 1}},
                    {CoreLogic::UserInterface::AnimationState{6 * 360, 640, 360, 1}}
            });

    po_sprites_[HUD_CURRENT_LIFE] = sprite;

    //15 - portrait
    sprite = UserInterface::Sprite("assets/graphics/SpriteSheets/HUD/hive_ARTI_newHUD_portrait.png",
            {
                    {CoreLogic::UserInterface::AnimationState{0 * 360, 640, 360, 1}},
                    {CoreLogic::UserInterface::AnimationState{1 * 360, 640, 360, 1}}
            });

    po_sprites_[HUD_PORTRAIT] = sprite;

    //16 - buttons
    sprite = UserInterface::Sprite("assets/graphics/SpriteSheets/HUD/hive_ARTI_newHUD_buttons.png",
            {
                    {CoreLogic::UserInterface::AnimationState{0 * 360, 640, 360, 1}}, //keyboard
                    {CoreLogic::UserInterface::AnimationState{1 * 360, 640, 360, 1}} //controller
            });

    po_sprites_[HUD_BUTTONS] = sprite;

    //interact
    sprite = UserInterface::Sprite("assets/graphics/SpriteSheets/HUD/hive_ARTI_newHUD_interact.png",
            {
                    {CoreLogic::UserInterface::AnimationState{1 * 360, 640, 360, 1}},
                    {CoreLogic::UserInterface::AnimationState{0 * 360, 640, 360, 1}}
            });

    po_sprites_[HUD_INTERACT] = sprite;

    //disconnect
    sprite = UserInterface::Sprite("assets/graphics/SpriteSheets/HUD/hive_ARTI_newHUD_toggle-hud.png",
            {
                    {CoreLogic::UserInterface::AnimationState{0 * 360, 640, 360, 1}}
            });

    po_sprites_[HUD_DISCONNECT] = sprite;

    //main ability
    sprite = UserInterface::Sprite("assets/graphics/SpriteSheets/HUD/hive_ARTI_newHUD_main-ability.png",
            {
                    {CoreLogic::UserInterface::AnimationState{1 * 360, 640, 360, 1}},
                    {CoreLogic::UserInterface::AnimationState{0 * 360, 640, 360, 1}}
            });

    po_sprites_[HUD_MAIN_ABILITY] = sprite;

    //death ability
    sprite = UserInterface::Sprite("assets/graphics/SpriteSheets/HUD/hive_ARTI_newHUD_death-ability.png",
            {
                    {CoreLogic::UserInterface::AnimationState{1 * 360, 640, 360, 1}},
                    {CoreLogic::UserInterface::AnimationState{0 * 360, 640, 360, 1}}
            });

    po_sprites_[HUD_DEATH_ABILITY] = sprite;

    //drone selection
    sprite = UserInterface::Sprite("assets/graphics/SpriteSheets/Scenes/hive_ARTI_newHUD_drone-selection-screen-Spritesheet.png",
            {
                    {CoreLogic::UserInterface::AnimationState{0 * 360, 640, 360, 1}},
                    {CoreLogic::UserInterface::AnimationState{1 * 360, 640, 360, 1}},
                    {CoreLogic::UserInterface::AnimationState{2 * 360, 640, 360, 1}},
            });

    po_sprites_[DRONE_SELECTION] = sprite;

    //main menu
    sprite = UserInterface::Sprite("assets/graphics/SpriteSheets/Scenes/hive_ARTI_newHUD_main-menu-screen-Spritesheet.png",
            {
                    {CoreLogic::UserInterface::AnimationState{0 * 360, 640, 360, 1}},
                    {CoreLogic::UserInterface::AnimationState{1 * 360, 640, 360, 1}},
            });

    po_sprites_[MAIN_MENU] = sprite;

    //death scene
    sprite = UserInterface::Sprite("assets/graphics/SpriteSheets/Scenes/hive_ARTI_newHUD_death-screen-Spritesheet.png",
            {
                    {CoreLogic::UserInterface::AnimationState{0 * 360, 640, 360, 1}},
                    {CoreLogic::UserInterface::AnimationState{1 * 360, 640, 360, 1}},
            });

    po_sprites_[DEATH_SCENE] = sprite;

    //victory background
    sprite = UserInterface::Sprite("assets/graphics/SpriteSheets/Scenes/hive_ARTI_newHUD_victory-background.png",
            {
                    {CoreLogic::UserInterface::AnimationState{0 * 360, 640, 360, 12}},
            });

    po_sprites_[VICTORY_BACKGROUND] = sprite;

    //victory buttons
    sprite = UserInterface::Sprite("assets/graphics/SpriteSheets/Scenes/hive_ARTI_newHUD_victory-buttons.png",
            {
                    {CoreLogic::UserInterface::AnimationState{0 * 360, 640, 360, 1}},
                    {CoreLogic::UserInterface::AnimationState{1 * 360, 640, 360, 1}},
            });

    po_sprites_[VICTORY_BUTTONS] = sprite;

    //lore screen
    sprite = UserInterface::Sprite("assets/graphics/SpriteSheets/Scenes/hive_ARTI_Lore-Items-Tablet_2024-09-13.png",
            {
                    {CoreLogic::UserInterface::AnimationState{0 * 360, 640, 360, 1}}
            });

    po_sprites_[LORE_ITEM] = sprite;

    //lore cracks
    sprite = UserInterface::Sprite("assets/graphics/SpriteSheets/Scenes/hive_ARTI_Lore-Item-Cracks_2024-09-13.png",
            {
                    {CoreLogic::UserInterface::AnimationState{0 * 360, 640, 360, 1}}
            });

    po_sprites_[LORE_CRACKS] = sprite;
}

void CoreLogic::DataProcessing::Fonts::Initialize()
{
    if (po_fonts_ == nullptr)
    {
        po_fonts_ = std::make_shared<std::vector<Font>>(std::vector<Font>({LoadFont("assets/fonts/PixelOperator.ttf"), LoadFont("assets/fonts/PixelOperatorHB.ttf")}));
    }

}

Font CoreLogic::DataProcessing::Fonts::getFont(int pa_index)
{
    return po_fonts_->at(pa_index);
}
