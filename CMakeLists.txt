cmake_minimum_required(VERSION 3.17.5)

project(2DGame)

add_executable(${PROJECT_NAME} src/main.cpp src/game/loaders.cpp src/game/loaders.hpp src/render/sprite.cpp src/render/sprite.hpp src/game/gameManager.cpp src/game/gameManager.hpp src/game/map.cpp src/game/map.hpp src/entities/character.cpp src/entities/character.hpp src/render/vector.cpp src/render/vector.hpp src/render/UI.cpp src/render/UI.hpp)

target_link_libraries(${PROJECT_NAME} SDL2 SDL2_image SDL2_ttf)

set(CMAKE_CXX_FLAGS "-Wall -Wextra")
set(CMAKE_CXX_FLAGS_DEBUG "-ggdb")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")
