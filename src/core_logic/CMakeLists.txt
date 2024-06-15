cmake_minimum_required(VERSION 3.24)

set(CORE_LOGIC_SOURCES
    data_processing/Level.cpp
    data_processing/Map.cpp
    data_processing/Store.cpp

    event_management/Actor.cpp
    event_management/Player.cpp
    event_management/Trigger.cpp
    event_management/ButtonMapping.cpp
    event_management/Commands.cpp
    event_management/EventHandler.cpp
    event_management/events/Event.cpp
    event_management/events/MovementEvent.cpp
    event_management/actor/StaticActor.cpp
    event_management/actor/AnimatedActor.cpp
    event_management/actor/MovableActor.cpp
    event_management/actor/Drone.cpp
    event_management/actor/Drones/Worker.cpp
    event_management/actor/Drones/Scout.cpp
    event_management/actor/Drones/Grappler.cpp
    event_management/actor/Enemy.cpp
    event_management/actor/Enemies/Kolonist.cpp
    event_management/actor/Enemies/Hazmat.cpp
    event_management/actor/Enemies/Mech.cpp

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

    event_management/Actor.h
    event_management/Player.h
    event_management/Trigger.h
    event_management/ButtonMapping.h
    event_management/Commands.h
    event_management/EventHandler.h
    event_management/events/Event.h
    event_management/events/MovementEvent.h
    event_management/actor/AnimatedActor.h
    event_management/actor/StaticActor.h
    event_management/actor/MovableActor.h
    event_management/actor/Drone.h
    event_management/actor/Enemy.h
    event_management/actor/Drones/Worker.h
    event_management/actor/Drones/Scout.h
    event_management/actor/Drones/Grappler.h
    event_management/actor/Enemies/Kolonist.h
    event_management/actor/Enemies/Hazmat.h
    event_management/actor/Enemies/Mech.h

    user_interface/Renderer.h
    user_interface/Sprite.h
    user_interface/AnimatedSprite.h

    Scene.h

)

add_library(core_logic STATIC ${CORE_LOGIC_SOURCES} ${CORE_LOGIC_HEADERS})

target_include_directories(core_logic PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")

target_link_libraries(core_logic raylib)
