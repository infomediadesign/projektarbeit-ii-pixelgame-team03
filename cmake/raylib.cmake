# raylib.cmake - Modified to download the correct raylib version based on the platform and use precompiled libraries

find_package(raylib 5.0.0 QUIET) # Let CMake search for raylib-config.cmake

if (NOT raylib_FOUND)
    include(FetchContent)

    if (WIN32)
        # Fetch precompiled Raylib for Windows
        FetchContent_Declare(
                raylib
                URL https://github.com/raysan5/raylib/releases/download/5.0/raylib-5.0_win64_msvc16.zip
        )

        FetchContent_GetProperties(raylib)
        if (NOT raylib_POPULATED)
            FetchContent_Populate(raylib)

            # Define paths to precompiled Raylib for Windows
            set(RAYLIB_DIR "${raylib_SOURCE_DIR}")
            set(RAYLIB_LIB "${RAYLIB_DIR}/lib/raylib.lib")
            set(RAYLIB_INCLUDE_DIR "${RAYLIB_DIR}/include")

            if (NOT EXISTS ${RAYLIB_LIB})
                message(FATAL_ERROR "Raylib library not found: ${RAYLIB_LIB}")
            endif()

            if (NOT EXISTS ${RAYLIB_INCLUDE_DIR})
                message(FATAL_ERROR "Raylib include directory not found: ${RAYLIB_INCLUDE_DIR}")
            endif()

            # Add the precompiled Raylib as an imported library
            add_library(raylib STATIC IMPORTED)
            set_target_properties(raylib PROPERTIES IMPORTED_LOCATION ${RAYLIB_LIB})

            # Include Raylib headers
            include_directories(${RAYLIB_INCLUDE_DIR})
        endif()

    elseif(APPLE)
        # Fetch precompiled Raylib for macOS
        FetchContent_Declare(
                raylib
                URL https://github.com/raysan5/raylib/releases/download/5.0.0/raylib-5.0.0_macos.tar.gz
        )

        FetchContent_GetProperties(raylib)
        if (NOT raylib_POPULATED)
            FetchContent_Populate(raylib)
            set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
            add_subdirectory(${raylib_SOURCE_DIR} ${raylib_BINARY_DIR})
        endif()

    else()
        # Fetch Raylib source for Unix/Linux platforms
        FetchContent_Declare(
                raylib
                URL https://github.com/raysan5/raylib/archive/refs/tags/5.0.tar.gz
        )

        FetchContent_GetProperties(raylib)
        if (NOT raylib_POPULATED)
            FetchContent_Populate(raylib)
            set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
            add_subdirectory(${raylib_SOURCE_DIR} ${raylib_BINARY_DIR})
        endif()
    endif()
endif()
