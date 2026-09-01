cmake_minimum_required(VERSION 3.15)
project(MyApp)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)   # helps IntelliSense find headers

find_package(raylib REQUIRED)

add_executable(MyApp main.cpp)
target_link_libraries(MyApp raylib)

if(APPLE)
    target_link_libraries(MyApp "-framework IOKit" "-framework Cocoa" "-framework OpenGL")
endif()