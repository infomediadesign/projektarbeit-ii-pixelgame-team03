cmake_minimum_required(VERSION 3.24)

set(CORE_LOGIC_SOURCES
    data_processing/Level.cpp
    data_processing/Map.cpp
    data_processing/Store.cpp



    event_management/Trigger.cpp
    event_management/InputHandler.cpp
    event_management/EventHandler.cpp
    event_management/events/Event.cpp
    event_management/events/MovementEvent.cpp

    event_management/Actor.cpp
    event_management/actor/StaticActor.cpp
    event_management/actor/AnimatedActor.cpp
    event_management/actor/MovableActor.cpp

        event_management/actor/Drone.cpp
        event_management/actor/drones/Worker.cpp
        event_management/actor/drones/Scout.cpp
        event_management/actor/drones/Grappler.cpp

    event_management/actor/Enemy.cpp
        event_management/actor/enemies/Kolonist.cpp
        event_management/actor/enemies/Hazmat.cpp
        event_management/actor/enemies/Mech.cpp



    user_interface/Renderer.cpp
    user_interface/Sprite.cpp
    user_interface/AnimatedSprite.cpp



    Scene.cpp
)

set(CORE_LOGIC_HEADERS
    data_processing/Level.h
    data_processing/Map.h
    data_processing/Store.h
    data_processing/TilesonUtilities.h



    event_management/Trigger.h
    event_management/InputHandler.h
    event_management/EventHandler.h
    event_management/events/Event.h
    event_management/events/MovementEvent.h

    event_management/Actor.h
    event_management/actor/AnimatedActor.h
    event_management/actor/StaticActor.h
    event_management/actor/MovableActor.h

        event_management/actor/Drone.h
        event_management/actor/drones/Worker.h
        event_management/actor/drones/Scout.h
        event_management/actor/drones/Grappler.h

    event_management/actor/Enemy.h
        event_management/actor/enemies/Kolonist.h
        event_management/actor/enemies/Hazmat.h
        event_management/actor/enemies/Mech.h



    user_interface/Renderer.h
    user_interface/Sprite.h
    user_interface/AnimatedSprite.h



    Scene.h
        event_management/EventUtilities.h

)

add_library(core_logic STATIC ${CORE_LOGIC_SOURCES} ${CORE_LOGIC_HEADERS})

target_include_directories(core_logic PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")

target_link_libraries(core_logic raylib)
