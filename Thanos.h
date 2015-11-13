//
// Created by Trevor Starick on 2015-11-12.
//

#pragma once

#ifndef ASTER_THANOS_H
#define ASTER_THANOS_H

#include <string>
#include <iostream>

#ifdef __APPLE__
  #include <SDL2/SDL.h>

  #include <OpenGL/gl3.h>
  #include <OpenGL/glu.h>
#else
  #ifdef _WIN32
    #include <windows.h>
  #endif

  #include <SDL.h>

  #include <GL/glew.h>

  #include <GL/gl.h>
  #include <GL/glu.h>
#endif

#include "glslProgram.h"

#include "SpriteKit.h"

enum class GameState {
    PLAY,
    EXIT
};

class Thanos {
public:
    Thanos();
    ~Thanos();

    void run();

private:
    void init();
    void initShaders();
    void input();
    void gameLoop();
    void draw();

    SDL_Window* _window;
    std::string _windowTitle;

    int _screenWidth;
    int _screenHeight;

    GameState   _gameState;
    SpriteKit   _sprite;
    glslProgram _colorProgram;
};


#endif //ASTER_THANOS_H
