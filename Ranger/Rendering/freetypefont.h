//
// Created by William DeVore on 10/25/17.
//

#ifndef RANGERALPHA_FREETYPEFONT_H
#define RANGERALPHA_FREETYPEFONT_H
#include <memory>

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <map>

#include <ft2build.h>
#include FT_FREETYPE_H

// Prototypes

namespace Ranger {
class Shader;

struct Character {
    GLuint TextureID; // ID handle of the glyph texture
    glm::ivec2 Size; // Size of glyph
    glm::ivec2 Bearing; // Offset from baseline to left/top of glyph
    GLuint Advance; // Offset to advance to next glyph
};

class FreeTypeFont final {

public:
    FreeTypeFont();
    ~FreeTypeFont();

    bool initialize();

    void renderText(const glm::mat4& vp, const std::string& text, GLfloat x, GLfloat y, GLfloat scale, const glm::vec3& color);

private:
    int genCharacters(const FT_Face& face, int charFromSet);

private:
    const char* glGetErrorString(GLenum error);
    GLenum _glCheckError();

    std::shared_ptr<Shader> _fontShader;
    std::string _fontName{ "Ranger/Assets/geo.ttf" };

    GLuint _mvpLoc;

    GLfloat _vertices[6][4];

    FT_UInt _fontSize{ 48 };
    FT_ULong _charsFromSet{ 128 };
    std::map<GLchar, Character> _characters;
    GLuint _colorLoc{};
    GLuint VAO, VBO;
};
}

#endif //RANGERALPHA_FREETYPEFONT_H
