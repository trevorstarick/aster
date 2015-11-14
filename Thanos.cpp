//
// Created by Trevor Starick on 2015-11-12.
//

#include "Thanos.h"

#include <stdio.h>

void error(std::string errorString) {
    std::cout << errorString << std::endl;
    std::cout << "Ripperino!";
    int foo; std::cin >> foo;

    exit(1);
}

Thanos::Thanos() : _mod(2), _screenWidth(1024), _screenHeight(768), _time(0), _window(nullptr) {
    _windowTitle = "Thanos v0.0.1";

    _gameState = GameState::PLAY;
}

Thanos::~Thanos() {

}

void Thanos::run() {
    init();

    double width, height, x, y;

    //top 49
    //bottom 40

    double tileModTop = ((89.0f + 54.0f) * (0.5 * _mod)) / (float)_screenHeight;
//    double tileModBot = ((89.0f + 12.0f) * (0.5 * mod)) / (float)_screenHeight;
    double tileModBot = ((89.0f + 7.0f) * (0.5 * _mod)) / (float)_screenHeight;



    width = (65.0f / (float)_screenWidth) * _mod;
    height = (89.0f / (float)_screenHeight) * _mod;

    x = 0 - (width / 2);
    y = 0 - (height / 2);

    _sprites.push_back(new SpriteKit());
    _sprites.back()->init(x + (width * 1.5), y + (tileModTop + (height * 0.5)), width, height, "textures/PNG/tileGrass.png");

    _sprites.push_back(new SpriteKit());
    _sprites.back()->init(x + (width * 0.5), y + (tileModTop + (height * 0.5)), width, height, "textures/PNG/tileGrass.png");

    _sprites.push_back(new SpriteKit());
    _sprites.back()->init(x - (width * 0.5), y + (tileModTop + (height * 0.5)), width, height, "textures/PNG/tileGrass.png");

    _sprites.push_back(new SpriteKit());
    _sprites.back()->init(x - (width * 1.5), y + (tileModTop + (height * 0.5)), width, height, "textures/PNG/tileGrass.png");


    _sprites.push_back(new SpriteKit());
    _sprites.back()->init(x + (width * 2), y + tileModTop, width, height, "textures/PNG/tileGrass.png");

    _sprites.push_back(new SpriteKit());
    _sprites.back()->init(x + width, y + tileModBot, width, height, "textures/PNG/tileGrass.png");

    _sprites.push_back(new SpriteKit());
    _sprites.back()->init(x, y + tileModTop, width, height, "textures/PNG/tileGrass.png");

    _sprites.push_back(new SpriteKit());
    _sprites.back()->init(x - width, y + tileModTop, width, height, "textures/PNG/tileGrass.png");

    _sprites.push_back(new SpriteKit());
    _sprites.back()->init(x - (width * 2), y + tileModBot, width, height, "textures/PNG/tileGrass.png");


    _sprites.push_back(new SpriteKit());
    _sprites.back()->init(x + (width * 2.5), y, width, height, "textures/PNG/tileGrass.png");

    _sprites.push_back(new SpriteKit());
    _sprites.back()->init(x + (width * 1.5), y, width, height, "textures/PNG/tileGrass.png");

    _sprites.push_back(new SpriteKit());
    _sprites.back()->init(x + (width * 0.5), y, width, height, "textures/PNG/tileGrass.png");

    _sprites.push_back(new SpriteKit());
    _sprites.back()->init(x - (width * 0.5), y, width, height, "textures/PNG/tileGrass.png");

    _sprites.push_back(new SpriteKit());
    _sprites.back()->init(x - (width * 0.5), y, width, height, "textures/PNG/tileWater_tile.png");

    _sprites.push_back(new SpriteKit());
    _sprites.back()->init(x - (width * 1.5), y, width, height, "textures/PNG/tileGrass.png");


    _sprites.push_back(new SpriteKit());
    _sprites.back()->init(x + width, y - tileModTop, width, height, "textures/PNG/tileDirt.png");

    _sprites.push_back(new SpriteKit());
    _sprites.back()->init(x, y - tileModTop, width, height, "textures/PNG/tileDirt.png");

    _sprites.push_back(new SpriteKit());
    _sprites.back()->init(x - width, y - tileModTop, width, height, "textures/PNG/tileDirt.png");



    _sprites.push_back(new SpriteKit());
    _sprites.back()->init(x + (width * 0.5), y - (tileModTop * 0.75f + height), width, height, "textures/PNG/tileWater.png");



    gameLoop();
}

void Thanos::init() {
    //Initialize SDL
    if(SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        error("SDL could not be initialized.");
    };

    _window = SDL_CreateWindow(
            _windowTitle.c_str(),
            SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
            _screenWidth, _screenHeight,
            SDL_WINDOW_OPENGL|SDL_WINDOW_ALLOW_HIGHDPI
    );

    if(_window == nullptr) {
        error("SDL_Window could not be initialized.");
    }


    #ifdef __APPLE__
    // Needed for OSX compatibility
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);


    SDL_GLContext glContext = SDL_GL_CreateContext(_window);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

//    glViewport(0, 0, _screenWidth * _mod, _screenHeight * _mod);

    GLuint vertexArrayID;

    glGenVertexArrays(1, &vertexArrayID);
    glBindVertexArray(vertexArrayID);
    #else

    SDL_GLContext glContext = SDL_GL_CreateContext(_window);
    glewExperimental = GL_TRUE;
    GLenum glewError = glewInit();

    if( glewError != GLEW_OK ) {
        printf( "Error initializing GLEW! %s\n", glewGetErrorString( glewError ) );
    }

    #endif

    int glVersionMajor;
    int glVersionMinor;

    glGetIntegerv(GL_MAJOR_VERSION, &glVersionMajor);
    glGetIntegerv(GL_MINOR_VERSION, &glVersionMinor);

    printf("\n=== Software Specifications ===\n");
    printf("Platform: %s\n", SDL_GetPlatform());
    printf("Video driver: %s\n", SDL_GetCurrentVideoDriver());
    printf("Audio driver: %s\n", SDL_GetCurrentAudioDriver());

    printf("\n=== Hardware Specifications ===\n");
    printf("CPU cores: %d\n", SDL_GetCPUCount());
    printf("RAM amount: %dMB\n", SDL_GetSystemRAM());

    printf("\n=== OpenGL Implementation ===\n");
    printf("Vendor: %s\n", glGetString(GL_VENDOR));
    printf("GL Version: %s\n", glGetString(GL_VERSION));
    printf("GL Version (Strict): %d.%d\n", glVersionMajor, glVersionMinor);
    printf("GLSL Version: %s\n", glGetString(GL_SHADING_LANGUAGE_VERSION));

    if(glContext == nullptr) {
        error("GL Context could not be created.");
    }

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    initShaders();

}

void Thanos::initShaders() {
    _colorProgram.compileShaders("shaders/colorShading.vert", "shaders/colorShading.frag");
    _colorProgram.addAttribute("vertexPosition");
    _colorProgram.addAttribute("vertexColor");
    _colorProgram.addAttribute("vertexUV");
    _colorProgram.linkShaders();
}

void Thanos::gameLoop() {

    while(_gameState != GameState::EXIT) {
        input();
        _time += 0.01;
        draw();
    }
}

void Thanos::input() {

    SDL_Event event;
    while(SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_QUIT:
                _gameState = GameState::EXIT;
                break;
            case SDL_KEYDOWN:
//                std::cout << "Keypress: " << event.key.keysym.sym << "\n";
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

void Thanos::draw() {
    glClearDepth(1.0f);
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

    _colorProgram.use();

    glActiveTexture(GL_TEXTURE0);

    GLint textureLocation = _colorProgram.getUniformLocation("samplerTexture");
    glUniform1i(textureLocation, 0);

//    GLuint timeLocation = _colorProgram.getUniformLocation("time");
//    glUniform1f(timeLocation, _time);

    for(int i = 0; i < _sprites.size(); i++) {
        _sprites[i]->draw();
    }

    glBindTexture(GL_TEXTURE_2D, 0);
    _colorProgram.unuse();

    SDL_GL_SwapWindow(_window);
}