//
// Created by Trevor Starick on 2015-11-14.
//

#ifndef ASTER_WINDOW_H
#define ASTER_WINDOW_H

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

#include <string>

namespace Thanos {
    enum WindowFlags {
        INVISIBLE   = 0x1,
        FULLSCREEN  = 0x2,
        BORDERLESS  = 0x4
    };

    class Window {
    public:
        Window();
        ~Window();

        int create(std::string windowName, int screenWidth, int screenHeight, unsigned int currentFlags);
        void swapBuffer();

//    private:
        SDL_Window *_sdlWindow;
        int _screenWidth, _screenHeight;
    };
}

#endif //ASTER_WINDOW_H
