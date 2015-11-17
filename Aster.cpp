#include "Aster.h"

#include <iostream>
#include <string>

Aster::Aster() :
        _screenWidth(1024),
        _screenHeight(768),
        _time(0.0f),
        _gameState(GameState::PLAY),
        _maxFPS(60.0f) {
    _camera.init(_screenWidth, _screenHeight);
}

Aster::~Aster() {}

void Aster::run() {
    init();
    gameLoop();
}

void Aster::init() {
    Thanos::init();
    _window.create("Thanos v0.0.1", _screenWidth, _screenHeight, 0);
    initShaders();
    _spriteBatch.init();
}

void Aster::initShaders() {
    _colorProgram.compileShaders("shaders/colorShading.vert", "shaders/colorShading.frag");
    _colorProgram.addAttribute("vertexPosition");
    _colorProgram.addAttribute("vertexColor");
    _colorProgram.addAttribute("vertexUV");
    _colorProgram.linkShaders();
}

void Aster::gameLoop() {
    while(_gameState != GameState::EXIT) {
        float startingTicks = SDL_GetTicks();

        input();
        _time += 0.01;

        _camera.update();

        draw();
        calculateFPS();

        static int frameCounter = 0;
        frameCounter++;
        if(frameCounter == 10) {
//            std::cout << std::to_string((int)_fps)) << "\n";
            frameCounter = 0;
        }

        float frameTicks = SDL_GetTicks() - startingTicks;

        if(1000.0f / _maxFPS > frameTicks) {
            SDL_Delay((Uint32)1000.0f / _maxFPS - frameTicks);
        }
    }
}

void Aster::input() {
    SDL_Event event;

    const float CAMERA_SPEED = 20.0f;
    const float SCALE_SPEED = 0.1f;

    while(SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_QUIT:
                _gameState = GameState::EXIT;
                break;
            case SDL_KEYDOWN:
                switch (event.key.keysym.sym) {
                    case SDLK_w:
                        _camera.setPosition(_camera.getPosition() + glm::vec2(0.0f, CAMERA_SPEED));
                        break;
                    case SDLK_s:
                        _camera.setPosition(_camera.getPosition() + glm::vec2(0.0f, -CAMERA_SPEED));
                        break;
                    case SDLK_a:
                        _camera.setPosition(_camera.getPosition() + glm::vec2(-CAMERA_SPEED, 0.0f));
                        break;
                    case SDLK_d:
                        _camera.setPosition(_camera.getPosition() + glm::vec2(CAMERA_SPEED, 0.0f));
                        break;
                    case SDLK_q:
                        _camera.setScale(_camera.getScale() + SCALE_SPEED);
                        break;
                    case SDLK_e:
                        _camera.setScale(_camera.getScale() - SCALE_SPEED);
                        break;
                }

                break;
            case SDL_KEYUP:
                break;
            case SDL_MOUSEBUTTONDOWN:
                break;
            case SDL_MOUSEBUTTONUP:
                break;
            case SDL_MOUSEMOTION:
//                std::cout << "Mousemove: "<< event.motion.x << " " << event.motion.y << "\n";
                break;
            case SDL_MOUSEWHEEL:
                break;
        }
    }
}

void Aster::draw() {
    glClearDepth(1.0f);
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

    _colorProgram.use();

    glActiveTexture(GL_TEXTURE0);

    GLint textureLocation = _colorProgram.getUniformLocation("samplerTexture");
    glUniform1i(textureLocation, 0);

    GLint pLocation = _colorProgram.getUniformLocation("P");
    glm::mat4 cameraMatrix = _camera.getCameraMatrix();

    glUniformMatrix4fv(pLocation, 1 , GL_FALSE, &(cameraMatrix[0][0]));

    _spriteBatch.begin(Thanos::GlyphSortType::FRONT_TO_BACK);

    glm::vec4 pos(0.0f, 0.0f, 65.0f, 89.0f);
    glm::vec4 uv(0.0f, 0.0f, 1.0f, 1.0f);

    static Thanos::GLTexture texture = Thanos::ResourceManager::getTexture("textures/PNG/tileGrass.png");
    static Thanos::GLTexture texture2 = Thanos::ResourceManager::getTexture("textures/PNG/tileStone.png");

    Thanos::ColorRGBA8 color;

    color = Thanos::ColorRGBA8(255, 255, 255, 255);

    int tileWidth = 65;
    int tileHeight = 89;

    int tileModTop = (89 + 54) * 0.5;
    int tileModBot = (89 + 7) * 0.5;

    _spriteBatch.draw(pos + glm::vec4(-(tileWidth/2), 0.0, 0.0, 0.0), uv, texture.id, 0.0f, color);

    _spriteBatch.end();
    _spriteBatch.renderBatch();

    glBindTexture(GL_TEXTURE_2D, 0);
    _colorProgram.unuse();

    _window.swapBuffer();
}

void Aster::calculateFPS() {
    static const int NUM_SAMPLES = 10;
    static float frameTimes[NUM_SAMPLES];
    static int currentFrame = 0;

    static float prevTicks = SDL_GetTicks();

    float currentTicks;
    currentTicks = SDL_GetTicks();

    _frameTime = currentTicks - prevTicks;

    frameTimes[currentFrame % NUM_SAMPLES] = _frameTime;

    prevTicks = currentTicks;

    int count;

    currentFrame++;
    if(currentFrame < NUM_SAMPLES) {
        count = currentFrame;
    } else {
        count = NUM_SAMPLES;
    }

    float frameTimeAverage = 0;

    for(int i = 0; i < count; i++) {
        frameTimeAverage += frameTimes[i];
    }

    frameTimeAverage /= count;

    if(frameTimeAverage > 0) {
        _fps = 1000.0f / frameTimeAverage;
    } else {
        _fps = 30.0f;
    }

//    std::cout << "FPS: " << _fps << "\n";

}