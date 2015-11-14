cmake_minimum_required(VERSION 3.3)
project(aster)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${PROJECT_SOURCE_DIR}/cmake")

if(win32)
set(SDL2_PATH "${PROJECT_SOURCE_DIR}/deps/SDL2-2.0.3/i686-w64-mingw32")
set(GLEW_PATH "${PROJECT_SOURCE_DIR}/deps/glew-1.13.0")
find_package(GLEW REQUIRED)
endif(win32)

find_package(SDL2 REQUIRED)
find_package(OpenGL REQUIRED)

include_directories(${SDL2_INCLUDE_DIR} ${OPENGL_INCLUDE_DIRS} ${GLEW_INCLUDE_DIR})

set(SOURCE_FILES main.cpp Thanos.cpp Thanos.h SpriteKit.cpp SpriteKit.h glslProgram.cpp glslProgram.h Vertex.h IOManager.cpp IOManager.h picopng.h GLTexture.h ImageLoader.cpp ImageLoader.h picopng.cpp picopng.h ResourceManager.cpp ResourceManager.h TextureCache.cpp TextureCache.h)

file(GLOB SHADER_FILES shaders/*)
file(COPY ${SHADER_FILES} DESTINATION shaders/)

add_executable(aster ${SHADER_FILES} ${SOURCE_FILES})

target_link_libraries(aster ${SDL2_LIBRARY} ${OPENGL_LIBRARIES} ${GLEW_LIBRARY})