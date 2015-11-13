cmake_minimum_required(VERSION 3.3)
project(aster)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${PROJECT_SOURCE_DIR}/cmake")

find_package(SDL2 REQUIRED)
find_package(OpenGL REQUIRED)

include_directories(${SDL2_INCLUDE_DIR} ${OPENGL_INCLUDE_DIRS})

set(SOURCE_FILES main.cpp Thanos.cpp Thanos.h SpriteKit.cpp SpriteKit.h glslProgram.cpp glslProgram.h)

file(GLOB SHADER_FILES shaders/*)
file(COPY ${SHADER_FILES} DESTINATION shaders/)

add_executable(aster ${SHADER_FILES} ${SOURCE_FILES})

target_link_libraries(aster ${SDL2_LIBRARY} ${OPENGL_LIBRARIES})