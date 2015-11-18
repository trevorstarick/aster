#ifndef ASTER_GLSLPROGRAM_H
#define ASTER_GLSLPROGRAM_H

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

#include <string>


namespace Thanos {

    class GLSLProgram {

    public:

        GLSLProgram();
        ~GLSLProgram();

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
}

#endif //ASTER_GLSLPROGRAM_H
