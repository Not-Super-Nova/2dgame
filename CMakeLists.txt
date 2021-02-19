cmake_minimum_required(VERSION 3.17.5)

project(2DGame)

add_executable(${PROJECT_NAME} src/main.cpp src/loaders.cpp src/loaders.h src/constants.h src/globals.h src/sprite.cpp src/sprite.h)

target_link_libraries(${PROJECT_NAME} SDL2)
target_link_libraries(${PROJECT_NAME} SDL2_image)
