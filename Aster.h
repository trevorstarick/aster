//
// Created by Trevor Starick on 2015-11-12.
//

#ifndef ASTER_THANOS_H
#define ASTER_THANOS_H

#include <SDL2/SDL.h>

# define __gl_h_
# define GL_DO_NOT_WARN_IF_MULTI_GL_VERSION_HEADERS_INCLUDED

#include <OpenGL/gl3.h>
#include <OpenGL/glu.h>

#include <Thanos/Thanos.h>
#include <Thanos/ResourceManager.h>
#include <Thanos/GLSLProgram.h>
#include <Thanos/GLTexture.h>
#include <Thanos/SpriteKit.h>
#include <Thanos/SpriteBatch.h>
#include <Thanos/Window.h>
#include <Thanos/Input.h>
#include <Thanos/Camera.h>

#include <vector>

enum class GameState {
    PLAY,
    EXIT
};

class Aster {
public:
    Aster();
    ~Aster();

    void run();

private:
    void init();
    void initShaders();
    void input();
    void gameLoop();
    void draw();
    void calculateFPS();

    Thanos::Window _window;

    int _screenWidth;
    int _screenHeight;

    GameState   _gameState;
    Thanos::GLSLProgram _colorProgram;
    Thanos::Camera _camera;
    Thanos::SpriteBatch _spriteBatch;

    float _fps;
    float _maxFPS;
    float _frameTime;

    float _time;
};

#endif //ASTER_THANOS_H
