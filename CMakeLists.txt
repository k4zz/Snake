cmake_minimum_required(VERSION 3.16)
project(Snake)

if (STATIC)
    set(SFML_STATIC_LIBRARIES TRUE)
endif ()

find_package(SFML 2.5.1 REQUIRED COMPONENTS graphics)

set(CMAKE_CXX_STANDARD 17)

add_executable(${PROJECT_NAME} src/main.cpp src/Game.cpp src/Snake.cpp src/Food.cpp)

target_include_directories(${PROJECT_NAME} PRIVATE include)

target_link_libraries(${PROJECT_NAME} sfml-graphics)

if (STATIC)
    target_compile_definitions(${PROJECT_NAME} PRIVATE SFML_STATIC)
endif ()