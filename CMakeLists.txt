cmake_minimum_required(VERSION 3.15)
project(MotionPlanningSimulator CXX)
 
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
 
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
FetchContent_Declare(
    raygui
    GIT_REPOSITORY https://github.com/raysan5/raygui.git
    GIT_TAG 4.0
    GIT_SHALLOW TRUE
)
FetchContent_MakeAvailable(raygui)
 
add_executable(MotionPlanningSimulator main.cpp)
 
target_include_directories(MotionPlanningSimulator PRIVATE
    ${raygui_SOURCE_DIR}/src
)
 
target_link_libraries(MotionPlanningSimulator PRIVATE raylib)
 
# macOS needs these frameworks linked
if (APPLE)
    target_link_libraries(MotionPlanningSimulator PRIVATE "-framework IOKit" "-framework Cocoa" "-framework OpenGL")
endif()