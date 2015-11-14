//
// Created by Trevor Starick on 2015-11-12.
//

#ifndef ASTER_THANOS_H
#define ASTER_THANOS_H

#ifdef __APPLE__
# define __gl_h_
# define GL_DO_NOT_WARN_IF_MULTI_GL_VERSION_HEADERS_INCLUDED

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

#include <string>
#include <iostream>
#include <vector>
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

    int _mod;
    int _screenWidth;
    int _screenHeight;

    GameState   _gameState;
    std::vector<SpriteKit*> _sprites;
    glslProgram _colorProgram;

    float _time;
};


#endif //ASTER_THANOS_H
