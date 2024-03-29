#include "GLSLProgram.h"

#include <iostream>
#include <fstream>
#include <vector>

namespace Thanos {

    GLSLProgram::GLSLProgram() : _numAttributes(0), _programID(0), _vertexShaderID(0), _fragmentShaderID(
            0) { }

    GLSLProgram::~GLSLProgram() { }

    void GLSLProgram::addAttribute(const std::string &attributeName) {
        glBindAttribLocation(_programID, _numAttributes++, attributeName.c_str());
    }

    GLint GLSLProgram::getUniformLocation(const std::string &uniformName) {
        GLint location = glGetUniformLocation(_programID, uniformName.c_str());

        if (location == GL_INVALID_INDEX) {
            std::cout << "Uniform " + uniformName + " not found in shader! \n";
        }

        return location;
    }

    void GLSLProgram::compileShader(const std::string &filePath, GLuint &id) {

        //Open the file
        std::ifstream shaderFile(filePath);
        if (shaderFile.fail()) {
            perror(filePath.c_str());
            std::cout << "Failed to open " + filePath << "\n";
        }

        //File contents stores all the text in the file
        std::string fileContents = "";
        //line is used to grab each line of the file
        std::string line;

        //Get all the lines in the file and add it to the contents
        while (std::getline(shaderFile, line)) {
            fileContents += line + "\n";
        }

        shaderFile.close();

        //get a pointer to our file contents c string;
        const char *contentsPtr = fileContents.c_str();
        //tell opengl that we want to use fileContents as the contents of the shader file
        glShaderSource(id, 1, &contentsPtr, nullptr);

        //compile the shader
        glCompileShader(id);

        //check for errors
        GLint success = 0;
        glGetShaderiv(id, GL_COMPILE_STATUS, &success);

        if (success == GL_FALSE) {
            GLint maxLength = 0;
            glGetShaderiv(id, GL_INFO_LOG_LENGTH, &maxLength);

            //The maxLength includes the NULL character
            std::vector<char> errorLog(maxLength);
            glGetShaderInfoLog(id, maxLength, &maxLength, &errorLog[0]);

            //Provide the infolog in whatever manor you deem best.
            //Exit with failure.
            glDeleteShader(id); //Don't leak the shader.

            //Print error log and quit
            std::printf("%s\n", &(errorLog[0]));
            std::cout << "Shader " + filePath + " failed to compile \n";
        }
    }

    void GLSLProgram::compileShaders(const std::string &vertexShaderFilePath,
                                     const std::string &fragmentShaderFilePath) {
        _programID = glCreateProgram();

        _vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
        if (_vertexShaderID == 0) {
            std::cout << "Vertex shader failed to be created!\n";
        }

        //Create the fragment shader object, and store its ID
        _fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
        if (_fragmentShaderID == 0) {
            std::cout << "Fragment shader failed to be created!\n";
        }

        compileShader(vertexShaderFilePath, _vertexShaderID);
        compileShader(fragmentShaderFilePath, _fragmentShaderID);
    }

    void GLSLProgram::linkShaders() {
        glAttachShader(_programID, _vertexShaderID);
        glAttachShader(_programID, _fragmentShaderID);

        glLinkProgram(_programID);

        GLint isLinked = 0;
        glGetProgramiv(_programID, GL_LINK_STATUS, (int *) &isLinked);

        if (isLinked == GL_FALSE) {
            GLint maxLength = 0;
            glGetProgramiv(_programID, GL_INFO_LOG_LENGTH, &maxLength);

            std::vector<GLchar> errorLog(maxLength);
            glGetProgramInfoLog(_programID, maxLength, &maxLength, &errorLog[0]);

            glDeleteProgram(_programID);

            glDeleteShader(_vertexShaderID);
            glDeleteShader(_fragmentShaderID);

            std::printf("%s\n", &(errorLog[0]));
            std::cout << "Shaders failed to linked.\n";
        }

        glDetachShader(_programID, _vertexShaderID);
        glDetachShader(_programID, _fragmentShaderID);
        glDeleteShader(_vertexShaderID);
        glDeleteShader(_fragmentShaderID);
    }

    void GLSLProgram::use() {
        glUseProgram(_programID);

        for (GLuint i = 0; i < _numAttributes; i++) {
            glEnableVertexAttribArray(i);
        }
    }

    void GLSLProgram::unuse() {
        glUseProgram(0);

        for (GLuint i = 0; i < _numAttributes; i++) {
            glDisableVertexAttribArray(i);
        }
    }
}