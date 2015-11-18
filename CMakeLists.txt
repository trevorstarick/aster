cmake_minimum_required(VERSION 3.3)
project(aster)

set(SDL2_PATH ${PROJECT_SOURCE_DIR}/deps/SDL2-2.0.3/i686-w64-mingw32)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${PROJECT_SOURCE_DIR}/cmake")

find_package(OpenGL REQUIRED)
find_package(SDL2 REQUIRED)
message(WARNING "SDL2 INCLUDE: "  ${SDL2_INCLUDE_DIR})
message(WARNING "SDL2 LIBRARY: " ${SDL2_LIBRARY})

include_directories(${SDL2_INCLUDE_DIR} ${PROJECT_SOURCE_DIR}/deps/glm ${PROJECT_SOURCE_DIR}/deps/gl3w/include ${OPENGL_INCLUDE_DIRS} ${PROJECT_SOURCE_DIR})

set(SOURCE_FILES main.cpp Aster.cpp Aster.h)

add_subdirectory(Thanos)
add_subdirectory(deps/gl3w)

add_executable(aster ${SHADER_FILES} ${SOURCE_FILES})

target_link_libraries(aster gl3w ${SDL2_LIBRARY} ${OPENGL_LIBRARIES} thanos)
