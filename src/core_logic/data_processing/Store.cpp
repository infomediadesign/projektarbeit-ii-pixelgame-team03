//
// Created by keanu on 6/1/2024.
//
#include "Store.h"
#include "raylib.h"

std::shared_ptr<Texture2D> CoreLogic::DataProcessing::TileMap::po_tileMap_ = nullptr;
std::shared_ptr<Texture2D> CoreLogic::DataProcessing::TileMap::getTileMap() {return po_tileMap_;}

std::shared_ptr<CoreLogic::EventManagement::Actors::Drone> CoreLogic::DataProcessing::ActorStorage::po_player_;
std::shared_ptr<std::map<int, std::vector<std::shared_ptr<CoreLogic::EventManagement::Actor>>>>
        CoreLogic::DataProcessing::ActorStorage::po_allActors_;
std::shared_ptr<std::map<int, std::vector<tson::Layer>>> CoreLogic::DataProcessing::ActorStorage::po_layers_;

void CoreLogic::DataProcessing::TileMap::Initialize()
{
    if (po_tileMap_ == nullptr)
    {
        po_tileMap_ = std::make_shared<Texture2D>(LoadTexture("assets/graphics/hive_ARTI_TileAtlas.png"));
    }

}


void CoreLogic::DataProcessing::ActorStorage::Initialize()
{
        ActorStorage::po_player_ = {};

        std::map<int, std::vector<std::shared_ptr<EventManagement::Actor>>> actors = {};
        ActorStorage::po_allActors_ = std::make_shared<std::map<int, std::vector<std::shared_ptr<EventManagement::Actor>>>>(actors);

        std::map<int, std::vector<tson::Layer>> layers = {};
        ActorStorage::po_layers_ = std::make_shared<std::map<int, std::vector<tson::Layer>>>(layers);

}


std::shared_ptr<CoreLogic::EventManagement::Actors::Drone> CoreLogic::DataProcessing::ActorStorage::getPlayer() {return po_player_;}

std::shared_ptr<std::map<int, std::vector<std::shared_ptr<CoreLogic::EventManagement::Actor>>>> CoreLogic::DataProcessing::ActorStorage::getActors() {return po_allActors_;}

std::shared_ptr<std::map<int, std::vector<tson::Layer>>> CoreLogic::DataProcessing::ActorStorage::getLayers() {return po_layers_;}

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
    if (!pa_map->empty()) {
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

void CoreLogic::DataProcessing::ActorStorage::setPlayer(std::shared_ptr<EventManagement::Actors::Drone> pa_player) {
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
        addActor(po_collidables_, pa_elevation, actor);
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
        addActor(po_allActors_, pa_elevation, actor);

    } else if (auto cliff = std::dynamic_pointer_cast<EventManagement::Object::Cliff>(pa_actor))
    {
        addActor(po_cliffs_, pa_elevation, cliff);

        auto actor = std::dynamic_pointer_cast<EventManagement::Actor>(pa_actor);
        addActor(po_allActors_, pa_elevation, actor);

    } else if (auto barrel = std::dynamic_pointer_cast<EventManagement::Object::Barrel>(pa_actor))
    {
        addActor(po_barrels_, pa_elevation, barrel);

        auto interaction = std::dynamic_pointer_cast<EventManagement::Object::Interaction>(pa_actor);
        addActor(po_interactions_, pa_elevation, interaction);

        auto actor = std::dynamic_pointer_cast<EventManagement::Actor>(pa_actor);
        addActor(po_collidables_, pa_elevation, actor);
        addActor(po_visibles_, pa_elevation, actor);
        addActor(po_allActors_, pa_elevation, actor);

    } else if (auto tutorialBox = std::dynamic_pointer_cast<EventManagement::Object::TutorialBox>(pa_actor))
    {
        addActor(po_tutorialBoxes_, pa_elevation, tutorialBox);

        auto actor = std::dynamic_pointer_cast<EventManagement::Actor>(pa_actor);
        addActor(po_allActors_, pa_elevation, actor);

    } else if (auto note = std::dynamic_pointer_cast<EventManagement::Object::Note>(pa_actor))
    {
        addActor(po_notes_, pa_elevation, note);

        auto actor = std::dynamic_pointer_cast<EventManagement::Actor>(pa_actor);
        addActor(po_allActors_, pa_elevation, actor);

    } else if (auto levelSwitch = std::dynamic_pointer_cast<EventManagement::Object::LevelSwitch>(pa_actor))
    {
        addActor(po_levelSwitches_, pa_elevation, levelSwitch);

        auto actor = std::dynamic_pointer_cast<EventManagement::Actor>(pa_actor);
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

CoreLogic::DataProcessing::GameState CoreLogic::DataProcessing::StateMachine::getCurrentState()
{
    return currentState_;
}

void CoreLogic::DataProcessing::StateMachine::changeState(CoreLogic::DataProcessing::GameState newState)
{
    previousState_ = currentState_;
    currentState_ = newState;
}
