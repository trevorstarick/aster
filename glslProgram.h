//
// Created by Trevor Starick on 2015-11-12.
//

#ifndef ASTER_GLSLPROGRAM_H
#define ASTER_GLSLPROGRAM_H

#include <string>

#ifdef __APPLE__
# define __gl_h_
# define GL_DO_NOT_WARN_IF_MULTI_GL_VERSION_HEADERS_INCLUDED

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

class glslProgram {

public:

    glslProgram();
    ~glslProgram();

    void compileShaders(const std::string &vertexShaderFilePath, const std::string &fragmentShaderFilePath);
    void linkShaders();
    void addAttribute(const std::string &attributeName);
    GLint getUniformLocation(const std::string &uniformName);

    void use();
    void unuse();

private:
    void compileShader(const std::string &filePath, GLuint &id);

    GLuint _numAttributes;
    GLuint _programID;
    GLuint _vertexShaderID;
    GLuint _fragmentShaderID;
};


#endif //ASTER_GLSLPROGRAM_H
