//
// Created by Trevor Starick on 2015-11-12.
//

#include "Thanos.h"

void error(std::string errorString) {
    std::cout << errorString << std::endl;
    std::cout << "Ripperino!";
    int foo; std::cin >> foo;

    exit(1);
}

Thanos::Thanos() {
    _window = nullptr;
    _windowTitle = "Thanos v0.0.1";

    _screenWidth = 1024;
    _screenHeight = 768;

    _gameState = GameState::PLAY;
}

Thanos::~Thanos() {

}

void Thanos::run() {
    init();

    _sprite.init(-1.0f, -1.0f, 1.0f, 1.0f);

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

    GLuint vertexArrayID;
    glGenVertexArrays(1, &vertexArrayID);
    glBindVertexArray(vertexArrayID);
    #else

    SDL_GLContext glContext = SDL_GL_CreateContext(_window);

    #endif

    int glVersionMajor;
    int glVersionMinor;
    glGetIntegerv(GL_MAJOR_VERSION, &glVersionMajor);
    glGetIntegerv(GL_MINOR_VERSION, &glVersionMinor);
    printf("\n=== OpenGL Implementation ===\n");
    printf("Vendor: %s\n", glGetString(GL_VENDOR));
    printf("GL Version: %s\n", glGetString(GL_VERSION));
    printf("GL Version (Strict): %d.%d\n", glVersionMajor, glVersionMinor);
    printf("GLSL Version: %s\n", glGetString(GL_SHADING_LANGUAGE_VERSION));

    if(glContext == nullptr) {
        error("GL Context could not be created.");
    }

    // Todo: Add glew support for non OSX

    glClearColor(1.0f, 0.0f, 1.0f, 1.0f);
    initShaders();

}

void Thanos::initShaders() {
    _colorProgram.compileShaders("shaders/colorShading.vert", "shaders/colorShading.frag");
    _colorProgram.addAttribute("vertexPosition");
    _colorProgram.linkShaders();
}

void Thanos::gameLoop() {

    while(_gameState != GameState::EXIT) {
        input();
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

    _sprite.draw();

    _colorProgram.unuse();

    SDL_GL_SwapWindow(_window);
}