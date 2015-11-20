//

// Created by Trevor Starick on 2015-11-14.
//

#include <iostream>
#include <stdio.h>

#include "Window.h"

namespace Thanos {
    Window::Window() {}
    Window::~Window() {}

    int Window::create(std::string  windowName,
                       int          screenWidth,
                       int          screenHeight,
                       unsigned int currentFlags) {
        Uint32 flags = SDL_WINDOW_OPENGL | SDL_WINDOW_ALLOW_HIGHDPI;

        if (currentFlags & INVISIBLE) {
            flags |= SDL_WINDOW_HIDDEN;
        }

        if (currentFlags & FULLSCREEN) {
            flags |= SDL_WINDOW_FULLSCREEN_DESKTOP;
        }

        if (currentFlags & BORDERLESS) {
            flags |= SDL_WINDOW_BORDERLESS;
        }

        if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
            std::cout << "SDL could not be initialized!\n";
        }

        _sdlWindow = SDL_CreateWindow(
                windowName.c_str(),
                SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                screenWidth, screenHeight,
                flags
        );

        if (_sdlWindow == nullptr) {
            std::cout << "SDL_Window could not be initialized!\n";
        }

        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK,  SDL_GL_CONTEXT_PROFILE_CORE);

        SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER,          1);

		SDL_GLContext glContext = SDL_GL_CreateContext(_sdlWindow);

#ifdef _WIN32
		GLenum gl3wError = gl3wInit();

		if (gl3wError != 0) {
			printf("Error initializing GL3W!");
		}
#endif

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        int glVersionMajor;
        int glVersionMinor;

        glGetIntegerv(GL_MAJOR_VERSION, &glVersionMajor);
        glGetIntegerv(GL_MINOR_VERSION, &glVersionMinor);

        printf("\n=== Software Specifications ===\n");
        printf("Platform: %s\n",               SDL_GetPlatform());
        printf("Video driver: %s\n",           SDL_GetCurrentVideoDriver());
        printf("Audio driver: %s\n",           SDL_GetCurrentAudioDriver());

        printf("\n=== Hardware Specifications ===\n");
        printf("CPU cores: %d\n",              SDL_GetCPUCount());
        printf("RAM amount: %dMB\n",           SDL_GetSystemRAM());

        printf("\n=== OpenGL Implementation ===\n");
        printf("Vendor: %s\n",                 glGetString(GL_VENDOR));
        printf("GL Version: %s\n",             glGetString(GL_VERSION));
        printf("GL Version (Strict): %d.%d\n", glVersionMajor, glVersionMinor);
        printf("GLSL Version: %s\n",
               glGetString(GL_SHADING_LANGUAGE_VERSION));

        if (glContext == nullptr) {
            std::cout << "GL Context could not be created!\n";
        }

        glClearColor((119.0f / 255.0f), (33.0f / 255.0f), (111.0f / 255.0f), 1.0f);
//        glClearColor((94.0f/255.0f), (129.0f/255.0f), (162.0f/255.0f), 1.0f);
        // glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

        SDL_GL_SetSwapInterval(0);

        return 0;

    }

    void Window::swapBuffer() {
        SDL_GL_SwapWindow(_sdlWindow);
    }
}
