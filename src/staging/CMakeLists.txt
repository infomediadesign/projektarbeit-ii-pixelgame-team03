cmake_minimum_required(VERSION 3.24)

set(STAGING_SOURCES
        Game.cpp
        Stage.cpp
)

set(STAGING_HEADERS
        Game.h
        Stage.h
)

add_library(staging STATIC ${STAGING_SOURCES} ${STAGING_HEADERS})

target_include_directories(staging PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")

target_link_libraries(staging raylib core_logic scenes)