//
// Created by Trevor Starick on 2015-11-12.
//

#pragma once

#ifndef ASTER_SPRITEKIT_H
#define ASTER_SPRITEKIT_H

#ifdef __APPLE__
    #include <OpenGL/gl3.h>
    #include <OpenGL/glu.h>
#else
    #ifdef _WIN32
        #include <windows.h>
    #endif

    #include <GL/glew.h>

    #include <GL/gl.h>
    #include <GL/glu.h>
#endif

class SpriteKit {
public:
    SpriteKit();
    ~SpriteKit();

    void init(float x, float y, float width, float height);
    void draw();

private:
    float _x;
    float _y;
    float _width;
    float _height;

    GLuint _vboID;

};


#endif //ASTER_SPRITEKIT_H
