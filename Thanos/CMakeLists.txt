cmake_minimum_required(VERSION 3.3)
project(thanos)

if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
endif()

set(SOURCE_FILES GLSLProgram.cpp GLSLProgram.h GLTexture.h IOManager.cpp IOManager.h ImageLoader.cpp ImageLoader.h picopng.h picopng.cpp ResourceManager.cpp ResourceManager.h SpriteKit.cpp SpriteKit.h TextureCache.cpp TextureCache.h Vertex.h Window.cpp Window.h Thanos.cpp Thanos.h Camera.cpp Camera.h SpriteBatch.cpp SpriteBatch.h InputManager.cpp InputManager.h)

add_library(thanos STATIC ${SOURCE_FILES})

install(TARGETS thanos DESTINATION lib)
install(FILES ${SOURCE_FILES} DESTINATION include)