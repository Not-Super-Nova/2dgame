cmake_minimum_required(VERSION 3.17.5)

project(2DGame)

add_executable(${PROJECT_NAME} src/main.cpp src/game/loaders.cpp src/game/loaders.hpp src/graphics/sprite.cpp src/graphics/sprite.hpp src/game/gameManager.cpp src/game/gameManager.hpp src/game/map.cpp src/game/map.hpp src/entities/character.cpp src/entities/character.hpp src/graphics/vector.cpp src/graphics/vector.hpp)

target_link_libraries(${PROJECT_NAME} SDL2)
target_link_libraries(${PROJECT_NAME} SDL2_image)

set(CMAKE_CXX_FLAGS "-Wall -Wextra")
set(CMAKE_CXX_FLAGS_DEBUG "-ggdb")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")
