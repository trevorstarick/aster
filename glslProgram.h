//
// Created by Trevor Starick on 2015-11-12.
//

#pragma once

#ifndef ASTER_GLSLPROGRAM_H
#define ASTER_GLSLPROGRAM_H

#include <string>

#ifdef __APPLE__
#include <OpenGL/gl3.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>
#else
#ifdef _WIN32
  #include <windows.h>
#endif
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#endif

class glslProgram {

public:

    glslProgram();
    ~glslProgram();

    void compileShaders(const std::string &vertexShaderFilePath, const std::string &fragmentShaderFilePath);
    void linkShaders();
    void addAttribute(const std::string& attributeName);

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
