cmake_minimum_required(VERSION 3.15)
project(MotionPlanningSimulator CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# raylib's bundled CMakeLists.txt still pins an old cmake_minimum_required
# (VERSION 3.5, no upper bound). CMake 4.0+ hard-errors on that unless we
# tell it we're fine building against that old policy set.
set(CMAKE_POLICY_VERSION_MINIMUM 3.5)

include(FetchContent)

# --- raylib ---
set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(BUILD_GAMES OFF CACHE BOOL "" FORCE)
FetchContent_Declare(
    raylib
    GIT_REPOSITORY https://github.com/raysan5/raylib.git
    GIT_TAG 5.5
    GIT_SHALLOW TRUE
)
FetchContent_MakeAvailable(raylib)

# --- raygui (header-only) ---
# raygui has no top-level CMakeLists.txt (its CMake files live under
# projects/CMake/), so FetchContent_MakeAvailable would fail trying to
# add_subdirectory() it. We only need the source, not a build, so just
# populate it.
FetchContent_Declare(
    raygui
    GIT_REPOSITORY https://github.com/raysan5/raygui.git
    GIT_TAG 4.0
    GIT_SHALLOW TRUE
)
FetchContent_GetProperties(raygui)
if(NOT raygui_POPULATED)
    FetchContent_Populate(raygui)
endif()

add_executable(MotionPlanningSimulator
    main.cpp
    PointStore.cpp
)

target_include_directories(MotionPlanningSimulator PRIVATE
    ${raygui_SOURCE_DIR}/src
)

target_link_libraries(MotionPlanningSimulator PRIVATE raylib)

# macOS needs these frameworks linked
if (APPLE)
    target_link_libraries(MotionPlanningSimulator PRIVATE "-framework IOKit" "-framework Cocoa" "-framework OpenGL")
endif()