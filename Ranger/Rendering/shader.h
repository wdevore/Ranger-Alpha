//
// Created by William DeVore on 3/10/16.
//

#ifndef RANGERALPHA_SHADER_H
#define RANGERALPHA_SHADER_H

#define GLEW_STATIC
#include <GL/glew.h>
// #include "/usr/local/include/GL/glew.h"

#include <string>

namespace Ranger {
class Shader {
public:
    Shader() = default;

    virtual ~Shader() = default;

    virtual void load() = 0;

    GLuint program() const
    {
        return _program;
    }

    // Uses the current shader
    void use();

    virtual void postUse() = 0;

    bool compileEnabled{ true };

protected:
    void _load(const std::string& vertexPath = "", const std::string& fragmentPath = "",
        const std::string& geometryPath = "");

    void _compile();

private:
    void _access();

    void _checkCompileErrors(GLuint shader, std::string type);

    // ------------------------------------------------------------------------
    // Properties
    // ------------------------------------------------------------------------
protected:
    GLuint _program;

private:
    // 1. Retrieve the vertex/fragment source code from filePath
    std::string _vertexCode;
    std::string _fragmentCode;
    std::string _geometryCode;

    std::string _vertexPath;
    std::string _fragmentPath;
    std::string _geometryPath;
};
}

#endif //RANGERALPHA_SHADER_H
