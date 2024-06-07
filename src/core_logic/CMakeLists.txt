cmake_minimum_required(VERSION 3.24)

set(CORE_LOGIC_SOURCES
    data_processing/Level.cpp
    data_processing/Map.cpp
    data_processing/Store.cpp


    event_management/Actor.cpp
    event_management/Player.cpp
    event_management/Trigger.cpp

    user_interface/Renderer.cpp

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

    user_interface/Renderer.h

    Scene.h
    data_processing/Store.cpp
        event_management/ButtonMapping.cpp
        event_management/ButtonMapping.h
        event_management/Comands.cpp
        event_management/Comands.h

)

add_library(core_logic STATIC ${CORE_LOGIC_SOURCES} ${CORE_LOGIC_HEADERS})

target_include_directories(core_logic PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")

target_link_libraries(core_logic raylib)
