//
// Created by Trevor Starick on 2015-11-12.
//

#ifndef ASTER_SPRITEKIT_H
#define ASTER_SPRITEKIT_H

# define __gl_h_
# define GL_DO_NOT_WARN_IF_MULTI_GL_VERSION_HEADERS_INCLUDED

#include <OpenGL/gl3.h>
#include <OpenGL/glu.h>

#include "GLTexture.h"

#include <string>

namespace Thanos {
    class SpriteKit {
    public:
        SpriteKit();
        ~SpriteKit();

        void init(double x, double y, double width, double height, std::string texturePath);

        void draw();

    //private:
        float _x;
        float _y;
        float _width;
        float _height;

        GLuint _vboID;

        GLTexture _texture;

    };
}

#endif //ASTER_SPRITEKIT_H
