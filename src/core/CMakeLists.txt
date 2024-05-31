cmake_minimum_required(VERSION 3.11)

add_library(core STATIC game.h game.cpp store.h scene.h stage.h stage.cpp renderer.h renderer.cpp texture2d.cpp texture2d.h sprite.h sprite.cpp sprite_animated.cpp sprite_animated.h actor.cpp actor.h
        letterbox.cpp
        letterbox.h
        qualityOfLife.h
        InputHandler.cpp
        InputHandler.h
        Commands/allCommands.h
        Commands/Command.cpp
        Commands/Command.h
        Commands/InGameCommands/MovementCommands/MoveUpCommand.cpp
        Commands/InGameCommands/MovementCommands/MoveUpCommand.h
        Commands/InGameCommands/MovementCommands/MoveDownCommand.cpp
        Commands/InGameCommands/MovementCommands/MoveDownCommand.h
        Commands/InGameCommands/MovementCommands/MoveLeftCommand.cpp
        Commands/InGameCommands/MovementCommands/MoveLeftCommand.h
        Commands/InGameCommands/MovementCommands/MoveRightCommand.cpp
        Commands/InGameCommands/MovementCommands/MoveRightCommand.h
        Commands/InGameCommands/PauseCommand.cpp
        Commands/InGameCommands/PauseCommand.h
        Commands/InGameCommands/PauseCommand.h
        Commands/InGameCommands/InteractCommand.cpp
        Commands/InGameCommands/InteractCommand.h
        Commands/InGameCommands/ActionCommand.cpp
        Commands/InGameCommands/ActionCommand.h
        Commands/InGameCommands/DisconnectCommand.cpp
        Commands/InGameCommands/DisconnectCommand.h
        Commands/InGameCommands/DeathAbilityCommand.cpp
        Commands/InGameCommands/DeathAbilityCommand.h
        Commands/InGameCommands/HighlightInteractablesCommand.cpp
        Commands/InGameCommands/HighlightInteractablesCommand.h
        Commands/MenuCommands/SelectCommand.cpp
        Commands/MenuCommands/SelectCommand.h
        Commands/MenuCommands/BackCommand.cpp
        Commands/MenuCommands/BackCommand.h
        Commands/MenuCommands/CursorUpCommand.cpp
        Commands/MenuCommands/CursorUpCommand.h
        Commands/MenuCommands/CursorDownCommand.cpp
        Commands/MenuCommands/CursorDownCommand.h
        Commands/MenuCommands/CursorLeftCommand.cpp
        Commands/MenuCommands/CursorLeftCommand.h
        Commands/MenuCommands/CursorRightCommand.cpp
        Commands/MenuCommands/CursorRightCommand.h)

target_include_directories(core PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")

target_link_libraries(core raylib raylib_cpp)
