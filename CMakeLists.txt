cmake_minimum_required(VERSION 3.17.5)

project(2DGame)

add_executable(${PROJECT_NAME} src/main.cpp src/loaders.cpp src/loaders.hpp src/sprite.cpp src/sprite.hpp src/gameManager.cpp src/gameManager.hpp src/map.cpp src/map.hpp src/character.cpp src/character.hpp src/vector.cpp src/vector.hpp src/UI.cpp src/UI.hpp)

target_link_libraries(${PROJECT_NAME} SDL2)
target_link_libraries(${PROJECT_NAME} SDL2_image)

set(CMAKE_CXX_FLAGS "-Wall -Wextra")
set(CMAKE_CXX_FLAGS_DEBUG "-ggdb")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")
