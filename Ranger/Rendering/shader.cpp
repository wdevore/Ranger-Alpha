//
// Created by William DeVore on 3/10/16.
//

#include "shader.h"
#include <fstream>
#include <iostream>
#include <sstream>

namespace Ranger {
void Shader::_load(const std::string& vertexPath, const std::string& fragmentPath, const std::string& geometryPath)
{
    _vertexPath = vertexPath;
    _fragmentPath = fragmentPath;
    _geometryPath = geometryPath;

    _access();
    _compile();
}

void Shader::_access()
{
    std::ifstream vShaderFile;
    std::ifstream fShaderFile;
    std::ifstream gShaderFile;

    // ensures ifstream objects can throw exceptions:
    vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    gShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

    try {
        // Open files
        vShaderFile.open(_vertexPath);
        fShaderFile.open(_fragmentPath);

        std::stringstream vShaderStream, fShaderStream;
        // Read file's buffer contents into streams
        vShaderStream << vShaderFile.rdbuf();
        fShaderStream << fShaderFile.rdbuf();

        // close file handlers
        vShaderFile.close();
        fShaderFile.close();

        // Convert stream into string
        _vertexCode = vShaderStream.str();
        _fragmentCode = fShaderStream.str();

        // If geometry shader path is present, then load a geometry shader
        if (_geometryPath != "") {
            gShaderFile.open(_geometryPath);
            std::stringstream gShaderStream;
            gShaderStream << gShaderFile.rdbuf();
            gShaderFile.close();
            _geometryCode = gShaderStream.str();
        }
    } catch (std::ifstream::failure e) {
        std::cerr << "ERROR::SHADER::FAILED_TO_READ_FILE" << std::endl;
    }
}

void Shader::_compile()
{
    if (!compileEnabled)
        return;

    const GLchar* vShaderCode = _vertexCode.c_str();
    const GLchar* fShaderCode = _fragmentCode.c_str();

    // 2. Compile shaders
    GLuint vertex, fragment;
    GLint success;
    GLchar infoLog[512];

    // Vertex Shader
    vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vShaderCode, NULL);
    glCompileShader(vertex);
    _checkCompileErrors(vertex, "VERTEX");

    // Fragment Shader
    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fShaderCode, NULL);
    glCompileShader(fragment);
    _checkCompileErrors(fragment, "FRAGMENT");

    // If geometry shader is given, compile geometry shader
    GLuint geometry;
    if (_geometryPath != "") {
        const GLchar* gShaderCode = _geometryCode.c_str();
        geometry = glCreateShader(GL_GEOMETRY_SHADER);
        glShaderSource(geometry, 1, &gShaderCode, NULL);
        glCompileShader(geometry);
        _checkCompileErrors(geometry, "GEOMETRY");
    }

    // Shader Program
    _program = glCreateProgram();

    glAttachShader(_program, vertex);
    glAttachShader(_program, fragment);
    if (_geometryPath != "")
        glAttachShader(_program, geometry);

    glLinkProgram(_program);
    _checkCompileErrors(_program, "PROGRAM");

    // Delete the shaders as they're linked into our program now and are no longer necessary
    glDeleteShader(vertex);
    glDeleteShader(fragment);
    if (_geometryPath != "")
        glDeleteShader(geometry);
}

void Shader::_checkCompileErrors(GLuint shader, std::string type)
{
    GLint success;
    GLchar infoLog[1024];
    if (type != "PROGRAM") {
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if (!success) {
            glGetShaderInfoLog(shader, 1024, NULL, infoLog);
            std::cerr << "| ERROR::::SHADER-COMPILATION-ERROR of type: " << type << "|\n"
                      << infoLog << "\n| -- --------------------------------------------------- -- |" << std::endl;
        }
    } else {
        glGetProgramiv(shader, GL_LINK_STATUS, &success);
        if (!success) {
            glGetProgramInfoLog(shader, 1024, NULL, infoLog);
            std::cerr << "| ERROR::::PROGRAM-LINKING-ERROR of type: " << type << "|\n"
                      << infoLog << "\n| -- --------------------------------------------------- -- |" << std::endl;
        }
    }
}

void Shader::use()
{
    glUseProgram(_program);

    postUse();
}
}
