//
// Created by Trevor Starick on 2015-11-12.
//

#ifndef ASTER_THANOS_H
#define ASTER_THANOS_H

#ifdef __APPLE__
# define __gl_h_
# define GL_DO_NOT_WARN_IF_MULTI_GL_VERSION_HEADERS_INCLUDED
#include <OpenGL/gl3.h>
#include <OpenGL/glu.h>
#else
#ifdef _WIN32
#include <windows.h>
#endif
#include <GL/gl3w.h>
#include <GL/gl.h>
#include <GL/glu.h>
#endif

#ifdef __APPLE__
#include <SDL2/SDL.h>
#else
#include <SDL.h>
#endif

#include <Thanos/Thanos.h>
#include <Thanos/ResourceManager.h>
#include <Thanos/GLSLProgram.h>
#include <Thanos/GLTexture.h>
#include <Thanos/SpriteKit.h>
#include <Thanos/SpriteBatch.h>
#include <Thanos/Window.h>
#include <Thanos/InputManager.h>
#include <Thanos/Camera.h>
#include <Thanos/Timing.h>
#include <Thanos/Entities.h>
#include <Thanos/WorldGen.h>

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
    void gameLoop();
	void inputLoop();
	void draw();
    void calculateFPS();

    Thanos::Window _window;

    int _screenWidth;
    int _screenHeight;

    GameState   _gameState;
    Thanos::GLSLProgram _colorProgram;
    Thanos::Camera _camera;
    Thanos::SpriteBatch _spriteBatch;
    Thanos::InputManager _inputManager;
    Thanos::Player* _player;

    Thanos::WorldGen* _worldGen;

	float _fps;
    int _frameTime;

    float _time;

	std::vector<SDL_Joystick*> _joysticks;
};

#endif //ASTER_THANOS_H
