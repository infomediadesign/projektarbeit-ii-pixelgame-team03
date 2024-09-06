cmake_minimum_required(VERSION 3.24)

set(SCENES_SOURCES
        GameScene.cpp
        MainMenuScene.cpp
        PauseScene.cpp
        SettingsScene.cpp
)

set(SCENES_HEADERS
        GameScene.h
        MainMenuScene.h
        PauseScene.h
        SettingsScene.h
        DroneSelectionScene.cpp
        DroneSelectionScene.h
)

add_library(scenes STATIC ${SCENES_SOURCES} ${SCENES_HEADERS})

target_include_directories(scenes PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")

target_link_libraries(scenes raylib core_logic)