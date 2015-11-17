//
// Created by Trevor Starick on 2015-11-14.
//

#ifndef ASTER_WINDOW_H
#define ASTER_WINDOW_H

# define __gl_h_
# define GL_DO_NOT_WARN_IF_MULTI_GL_VERSION_HEADERS_INCLUDED

#include <SDL2/SDL.h>

#include <OpenGL/gl3.h>
#include <OpenGL/glu.h>

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
