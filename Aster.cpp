#include "Aster.h"

#include <iostream>
#include <string>

Aster::Aster() :
        _screenWidth(1024),
        _screenHeight(768),
        _time(0.0f),
        _gameState(GameState::PLAY),
        _fps(0),
        _player(nullptr){
    _camera.init(_screenWidth, _screenHeight);
}

Aster::~Aster() {}

void Aster::run() {
    init();
    gameLoop();
}

void Aster::init() {
    Thanos::init();

    _worldGen = new Thanos::WorldGen();
    _worldGen->init();

    _window.create("Thanos v0.0.1", _screenWidth, _screenHeight, 0);

    _colorProgram.compileShaders("shaders/colorShading.vert", "shaders/colorShading.frag");
    _colorProgram.addAttribute("vertexPosition");
    _colorProgram.addAttribute("vertexColor");
    _colorProgram.addAttribute("vertexUV");
    _colorProgram.linkShaders();

    _spriteBatch.init();

	for (int i = 0; i < SDL_NumJoysticks(); ++i) {
		if (SDL_IsGameController(i)) {
			printf("Joystick %i is supported by the game controller interface!\n", i);
		}

		SDL_Joystick *js = SDL_JoystickOpen(i);

		_joysticks.push_back(js);
	}

    _player = new Thanos::Player();
    _player->init(5.0f, glm::vec2(0, 0), &_inputManager, &_camera);

}

void Aster::gameLoop() {
    const float DESIRED_FPS = 60.0f;
    const float MAX_DELTA_TIME = 1.0f;
    const int MAX_PHYSICS_STEPS = 6;

    Thanos::FpsLimiter fpsLimiter;
    fpsLimiter.setMaxFPS(60.0f);

    float previousTicks = SDL_GetTicks();

    while(_gameState != GameState::EXIT) {
        fpsLimiter.begin();

        float newTicks = SDL_GetTicks();
        float frameTime = newTicks - previousTicks;
        previousTicks = newTicks;

        float sumDeltaTime  = frameTime / DESIRED_FPS;

        _inputManager.update();
        inputLoop();

        int i = 0;

        while(sumDeltaTime > 0.0f && i < MAX_PHYSICS_STEPS) {
            float deltaTime = std::min(sumDeltaTime, MAX_DELTA_TIME);

            _player->update(deltaTime);

            sumDeltaTime -= deltaTime;
            i += 1;
        }

        _camera.setPosition(_player->getPosition());
        _camera.update();

        draw();

        _fps = fpsLimiter.end();
    }
}

void Aster::inputLoop() {
    SDL_Event event;

    const float CAMERA_SPEED = 10.0f;
    const float SCALE_SPEED = 0.02f;

    const float MAX_ZOOM = 2.0f;
    const float MIN_ZOOM = 0.5f;

    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_QUIT:
                _gameState = GameState::EXIT;
                break;
//			case SDL_JOYAXISMOTION:
//				break;
//			case SDL_JOYBUTTONDOWN:
//				break;
//			case SDL_JOYHATMOTION:
//				break;
            case SDL_MOUSEMOTION:
                _inputManager.setMouseCoords(event.motion.x, event.motion.y);
                break;
            case SDL_KEYDOWN:
                _inputManager.pressKey(event.key.keysym.sym);
                break;
            case SDL_KEYUP:
                _inputManager.releaseKey(event.key.keysym.sym);
                break;
            case SDL_MOUSEBUTTONDOWN:
                _inputManager.pressKey(event.button.button);
                break;
            case SDL_MOUSEBUTTONUP:
                _inputManager.releaseKey(event.button.button);
                break;
            case SDL_MOUSEWHEEL:
                break;
            default:
                break;
        }
    }
};


void Aster::draw() {
    glClearDepth(1.0f);
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

    _colorProgram.use();

    glActiveTexture(GL_TEXTURE0);

    GLint textureLocation = _colorProgram.getUniformLocation("samplerTexture");
    glUniform1i(textureLocation, 0);

    glm::mat4 cameraMatrix = _camera.getCameraMatrix();
    GLint pLocation = _colorProgram.getUniformLocation("P");
    glUniformMatrix4fv(pLocation, 1 , GL_FALSE, &(cameraMatrix[0][0]));

    _spriteBatch.begin(Thanos::GlyphSortType::FRONT_TO_BACK);

    static Thanos::GLTexture texture = Thanos::ResourceManager::getTexture("textures/PNG/tileGrass.png");
    static Thanos::GLTexture texture2 = Thanos::ResourceManager::getTexture("textures/PNG/tileStone.png");

    Thanos::ColorRGBA8 color;

    int tileWidth = 65;
    int tileHeight = 89;

    int tileModTop = (int)((89 + 54) * 0.5f);
    int tileModBot = (int)((89 + 7) * 0.5f);

    int yIncr = 48;

//    int mapWidth = (int)(_screenWidth / tileWidth);
//    int mapHeight = (int)(_screenHeight / yIncr);

    int mapWidth = 2;
    int mapHeight = 3;

    int xPos, yPos, xMod;

    yPos = -yIncr;

    color = Thanos::ColorRGBA8(255, 255, 255, 255);

    for(int y = 0; y < mapHeight-2; y++) {

        yPos += yIncr;

        if(y % 2 == 0) {
            xMod = tileWidth / 2;
        } else {
            xMod = 0;
        }

        for(int x = 0; x < mapWidth-1; x++) {

            xPos = (tileWidth * x);
            xPos -= ((mapWidth * tileWidth) - (tileWidth / 2)) / 2;
            xPos += xMod;



            _spriteBatch.draw(
                    glm::vec4(xPos, yPos - ((mapHeight * yIncr) - yIncr) / 2, tileWidth, tileHeight),
                    glm::vec4(0.0f, 0.0f, 1.0f, 1.0f),
                    texture.id, (float)-y, color);

        }

    }

    _spriteBatch.end();
    _spriteBatch.renderBatch();

    glBindTexture(GL_TEXTURE_2D, 0);
    _colorProgram.unuse();

    _window.swapBuffer();
}

void Aster::calculateFPS() {
    static const int NUM_SAMPLES = 10;
    static int frameTimes[NUM_SAMPLES];
    static int currentFrame = 0;

    static int prevTicks = SDL_GetTicks();

    int currentTicks;
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
        _fps = 1000.0f/ frameTimeAverage;
    } else {
        _fps = 30.0f;
    }
}