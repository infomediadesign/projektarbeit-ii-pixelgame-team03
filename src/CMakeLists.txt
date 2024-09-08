cmake_minimum_required(VERSION 3.24)

include(../cmake/raylib.cmake)

project(hive VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_subdirectory(core_logic)
add_subdirectory(scenes)
add_subdirectory(staging)

add_executable(${PROJECT_NAME} main.cpp
        tileson.h
)

# Add config.h.in file
configure_file(config.h.in config.h)
target_include_directories(${PROJECT_NAME} PUBLIC
        "${PROJECT_BINARY_DIR}"
        )

# Link to Raylib
# Ensure static linking of Raylib
if(UNIX)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static-libgcc -static-libstdc++")
    # Link Raylib statically
    target_link_libraries(${PROJECT_NAME} ${CMAKE_BINARY_DIR}/_deps/raylib-build/raylib/raylib.lib)
else()
    # Link Raylib statically on Windows
    target_link_libraries(${PROJECT_NAME} ${CMAKE_BINARY_DIR}/_deps/raylib-build/raylib/raylib.lib -static)
endif()

# Link other libraries
target_link_libraries(${PROJECT_NAME} core_logic scenes staging)

# Copy assets to assets path
add_custom_target(copy_assets
        COMMAND ${CMAKE_COMMAND} -P "${CMAKE_CURRENT_LIST_DIR}/../cmake/copy-assets.cmake"
        )
add_dependencies(${PROJECT_NAME} copy_assets)

if (APPLE)
    target_link_libraries(${PROJECT_NAME} "-framework IOKit")
    target_link_libraries(${PROJECT_NAME} "-framework Cocoa")
    target_link_libraries(${PROJECT_NAME} "-framework OpenGL")
endif ()

# CPack instructions
# call e.g. cpack -G ZIP -C Debug to create a binary distribution
install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION "${PROJECT_NAME}_Bundle")
install(DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/assets" DESTINATION "${PROJECT_NAME}_Bundle")