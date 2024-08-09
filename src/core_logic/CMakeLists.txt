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

)

add_library(core_logic STATIC ${CORE_LOGIC_SOURCES} ${CORE_LOGIC_HEADERS})

target_include_directories(core_logic PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")

target_link_libraries(core_logic raylib)
