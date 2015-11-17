//
// Created by Trevor Starick on 2015-11-13.
//

#ifndef ASTER_GLTEXTURE_H
#define ASTER_GLTEXTURE_H

# define __gl_h_
# define GL_DO_NOT_WARN_IF_MULTI_GL_VERSION_HEADERS_INCLUDED
#include <OpenGL/gl3.h>
#include <OpenGL/glu.h>

namespace Thanos {
    struct GLTexture {
        GLuint id;

        int width;
        int height;
    };
}
#endif //ASTER_GLTEXTURE_H
