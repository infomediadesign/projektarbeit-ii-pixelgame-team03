cmake_minimum_required(VERSION 3.24)

include_directories(user_interface)
include_directories(event_management)
include_directories(data_processing)

set(CORE_LOGIC_SOURCES
    data_processing/Level.cpp
    data_processing/Map.cpp
    data_processing/Store.cpp


    event_management/InputHandler.cpp
    event_management/EventHandler.cpp
    event_management/events/Event.cpp
    event_management/events/MovementEvent.cpp
    event_management/events/CleaningEvent.cpp
    event_management/events/AbilityEvent.cpp

    event_management/Actor.cpp
    event_management/actors/MovableActor.cpp

    event_management/actors/Drone.cpp
    event_management/actors/drones/Worker.cpp
    event_management/actors/drones/Scout.cpp
    event_management/actors/drones/Grappler.cpp

    event_management/actors/Enemy.cpp
    event_management/actors/enemies/Colonist.cpp
    event_management/actors/enemies/Hazmat.cpp
    event_management/actors/enemies/Mech.cpp



    user_interface/Renderer.cpp


    Scene.cpp
    user_interface/Sprite.cpp
)

set(CORE_LOGIC_HEADERS
        data_processing/Level.h
        data_processing/Map.h
        data_processing/Store.h
        data_processing/TilesonUtilities.h



        event_management/InputHandler.h
        event_management/EventHandler.h
        event_management/events/Event.h
        event_management/events/MovementEvent.h
        event_management/events/CleaningEvent.h
        event_management/events/AbilityEvent.h

        event_management/Actor.h
        event_management/actors/MovableActor.h

        event_management/actors/Drone.h
        event_management/actors/drones/Worker.h
        event_management/actors/drones/Scout.h
        event_management/actors/drones/Grappler.h

        event_management/actors/Enemy.h
        event_management/actors/enemies/Colonist.h
        event_management/actors/enemies/Hazmat.h
        event_management/actors/enemies/Mech.h



        user_interface/Renderer.h


        Scene.h
        event_management/EventUtilities.h
        user_interface/Sprite.h
        event_management/events/PushEvent.cpp
        event_management/events/PushEvent.h

        event_management/SoundHandler.cpp
        event_management/SoundHandler.h
        user_interface/HUD.cpp
        user_interface/HUD.h
        event_management/events/FallingEvent.cpp
        event_management/events/FallingEvent.h
        event_management/events/JumpEvent.cpp
        event_management/events/JumpEvent.h
        event_management/events/FallingBarrelEvent.cpp
        event_management/events/FallingBarrelEvent.h
        event_management/events/FallingBoulderEvent.cpp
        event_management/events/FallingBoulderEvent.h
        event_management/events/PushBarrelEvent.cpp
        event_management/events/PushBarrelEvent.h
        event_management/objects/Interaction.cpp
        event_management/objects/Interaction.h
        event_management/objects/Ability.cpp
        event_management/objects/Ability.h
        event_management/objects/Rubble.cpp
        event_management/objects/Rubble.h
        event_management/objects/Barrel.cpp
        event_management/objects/Barrel.h
        event_management/objects/Cliff.cpp
        event_management/objects/Cliff.h
        event_management/objects/Boulder.cpp
        event_management/objects/Boulder.h
        event_management/objects/JumpPoint.cpp
        event_management/objects/JumpPoint.h
        event_management/objects/ElevationChange.cpp
        event_management/objects/ElevationChange.h
        event_management/objects/Note.cpp
        event_management/objects/Note.h
        event_management/objects/DroneRespawnPoint.cpp
        event_management/objects/DroneRespawnPoint.h
        event_management/objects/Vine.cpp
        event_management/objects/Vine.h
        event_management/objects/TutorialBox.cpp
        event_management/objects/TutorialBox.h
        event_management/objects/LevelSwitch.cpp
        event_management/objects/LevelSwitch.h
        data_processing/DesignConfig.h


)

add_library(core_logic STATIC ${CORE_LOGIC_SOURCES} ${CORE_LOGIC_HEADERS})

target_include_directories(core_logic PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")

target_link_libraries(core_logic raylib)
