cmake_minimum_required(VERSION 3.3)
project(aster)

if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
endif()

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${PROJECT_SOURCE_DIR}/cmake")

find_package(OpenGL REQUIRED)
if(WIN32)
set(SDL2_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/deps/SDL2/include)
set(SDL2_LIBRARY ${PROJECT_SOURCE_DIR}/deps/SDL2/lib/win32/SDL2main.lib ${PROJECT_SOURCE_DIR}/deps/SDL2/lib/win32/SDL2.lib)
else()
find_package(SDL2 REQUIRED)
endif(WIN32)

message(WARNING "SDL2 INCLUDE: "  ${SDL2_INCLUDE_DIR})
message(WARNING "SDL2 LIBRARY: " ${SDL2_LIBRARY})

include_directories(${SDL2_INCLUDE_DIR} ${PROJECT_SOURCE_DIR}/deps/glm ${PROJECT_SOURCE_DIR}/deps/gl3w/include ${OPENGL_INCLUDE_DIRS} ${PROJECT_SOURCE_DIR})

set(SOURCE_FILES main.cpp Aster.cpp Aster.h)

add_subdirectory(Thanos)
add_subdirectory(deps/gl3w)

add_executable(aster ${SOURCE_FILES})

target_link_libraries(aster gl3w ${SDL2_LIBRARY} ${OPENGL_LIBRARIES} thanos)
