//
// Created by William DeVore on 10/25/17.
//
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>

#include "../IO/configuration.h"
#include "../Rendering/Shaders/font_shader.h"
#include "../ranger.h"

#include "freetypefont.h"

namespace Ranger {
FreeTypeFont::FreeTypeFont()
{
}

FreeTypeFont::~FreeTypeFont()
{
    std::cout << "FreeTypeFont::~FreeTypeFont" << std::endl;
}

bool FreeTypeFont::initialize()
{
    FT_Library ft;

    FT_Error ftError = FT_Init_FreeType(&ft);
    if (ftError != 0) {
        std::cerr << "Could not init FreeType library" << std::endl;
        return false;
    }

    FT_Face face;

    const ConfigurationPtr& config = App::config();
    std::string fontPath = config->fontPath() + config->fontName();
    ftError = FT_New_Face(ft, fontPath.c_str(), 0, &face);

    if (ftError != 0) {
        std::cerr << "Could not open '" << fontPath << "' FreeType library. Error code: " << ftError << ""
                  << std::endl;
        return false;
    }

    FT_Set_Pixel_Sizes(face, 0, config->fontSize());

    int gened = genCharacters(face, config->fontCharsFromSet());

    if (gened != -1) {
        std::cerr << "Could not generate font characters: (" << gened << ")" << std::endl;
        return false;
    }

    // Now release resources. NOTE: We release in reverse order,
    // first Face then Type.
    ftError = FT_Done_Face(face);
    if (ftError != 0) {
        std::cerr << "Could not free FontFace resources" << std::endl;
    }

    ftError = FT_Done_FreeType(ft);
    if (ftError != 0) {
        std::cerr << "Could not free FreeType resources" << std::endl;
    }

    std::cout << "FreeType initialized" << std::endl;

    _fontShader = std::make_shared<FontShader>();
    _fontShader->load();

    std::cout << "Font shader loaded" << std::endl;

    _colorLoc = glGetUniformLocation(_fontShader->program(), "textColor");

    // Disable byte-alignment restriction
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    // Configure VAO/VBO for texture quads
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    _mvpLoc = glGetUniformLocation(_fontShader->program(), "projection");

    return true;
}

int FreeTypeFont::genCharacters(const FT_Face& face, int charsFromSet)
{
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1); // Disable byte-alignment restriction
    FT_GlyphSlot g = face->glyph;

    for (GLubyte c = 0; c < charsFromSet; c++) {
        // Load character glyph
        if (FT_Load_Char(face, c, FT_LOAD_RENDER)) {
            std::cerr << "ERROR::FREETYTPE: Failed to load Glyph" << std::endl;
            return c;
        }
        // Generate texture
        GLuint texture;
        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);
        glTexImage2D(
            GL_TEXTURE_2D,
            0,
            GL_RED,
            g->bitmap.width,
            g->bitmap.rows,
            0,
            GL_RED,
            GL_UNSIGNED_BYTE,
            g->bitmap.buffer);
        // Set texture options
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        // Now store character for later use
        Character character = {
            texture,
            glm::ivec2(g->bitmap.width, g->bitmap.rows),
            glm::ivec2(g->bitmap_left, g->bitmap_top),
            static_cast<GLuint>(g->advance.x)
        };
        _characters.insert(std::pair<GLchar, Character>(c, std::move(character)));
    }

    return -1;
}

void FreeTypeFont::renderText(const glm::mat4& vp, const std::string& text, GLfloat x, GLfloat y, GLfloat scale, const glm::vec3& color)
{
    // Activate corresponding render state
    _fontShader->use();

    glUniformMatrix4fv(_mvpLoc, 1, GL_FALSE, glm::value_ptr(vp));

    glUniform3f(_colorLoc, color.x, color.y, color.z);

    glActiveTexture(GL_TEXTURE0);
    glBindVertexArray(VAO);

    GLuint vertexCount = sizeof(_vertices);
    _vertices[0][2] = 0.0;
    _vertices[0][3] = 0.0;
    _vertices[1][2] = 0.0;
    _vertices[1][3] = 1.0;
    _vertices[2][2] = 1.0;
    _vertices[2][3] = 1.0;
    _vertices[3][2] = 0.0;
    _vertices[3][3] = 0.0;
    _vertices[4][2] = 1.0;
    _vertices[4][3] = 1.0;
    _vertices[5][2] = 1.0;
    _vertices[5][3] = 0.0;

    // Iterate through all characters
    for (const char& c : text) {
        Character ch = _characters[c];

        GLfloat xpos = x + ch.Bearing.x * scale;
        GLfloat ypos = y - (ch.Size.y - ch.Bearing.y) * scale;

        GLfloat w = ch.Size.x * scale;
        GLfloat h = ch.Size.y * scale;

        // Update VBO for each character
        _vertices[0][0] = xpos;
        _vertices[0][1] = ypos + h;

        _vertices[1][0] = xpos;
        _vertices[1][1] = ypos;

        _vertices[2][0] = xpos + w;
        _vertices[2][1] = ypos;

        _vertices[3][0] = xpos;
        _vertices[3][1] = ypos + h;

        _vertices[4][0] = xpos + w;
        _vertices[4][1] = ypos;

        _vertices[5][0] = xpos + w;
        _vertices[5][1] = ypos + h;

        // GLfloat vertices[6][4] = {
        //     { xpos, ypos + h, 0.0, 0.0 },
        //     { xpos, ypos, 0.0, 1.0 },
        //     { xpos + w, ypos, 1.0, 1.0 },

        //     { xpos, ypos + h, 0.0, 0.0 },
        //     { xpos + w, ypos, 1.0, 1.0 },
        //     { xpos + w, ypos + h, 1.0, 0.0 }
        // };

        // Render glyph texture over quad
        glBindTexture(GL_TEXTURE_2D, ch.TextureID);

        // Update content of VBO memory
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferSubData(GL_ARRAY_BUFFER, 0, vertexCount, _vertices); // Be sure to use glBufferSubData and not glBufferData

        glBindBuffer(GL_ARRAY_BUFFER, 0);

        // Render quad
        glDrawArrays(GL_TRIANGLES, 0, 6);

        // Now advance cursors for next glyph (note that advance is number of 1/64 pixels)
        x += (ch.Advance >> 6) * scale; // Bitshift by 6 to get value in pixels (2^6 = 64 (divide amount of 1/64th pixels by 64 to get amount of pixels))
    }

    glBindVertexArray(0);
    glBindTexture(GL_TEXTURE_2D, 0);
}

GLenum FreeTypeFont::_glCheckError()
{
    GLenum err;
    while ((err = glGetError()) != GL_NO_ERROR)
        std::cerr << "OpenGL Error: " << __FILE__ << "(" << __LINE__ << ")"
                  << "[" << err << "]" << glGetErrorString(err) << std::endl;
    return err;
}

const char* FreeTypeFont::glGetErrorString(GLenum error)
{
    switch (error) {
    case GL_NO_ERROR:
        return "No Error";
    case GL_INVALID_ENUM:
        return "Invalid Enum";
    case GL_INVALID_VALUE:
        return "Invalid Value";
    case GL_INVALID_OPERATION:
        return "Invalid Operation";
    case GL_INVALID_FRAMEBUFFER_OPERATION:
        return "Invalid Framebuffer Operation";
    case GL_OUT_OF_MEMORY:
        return "Out of Memory";
    case GL_STACK_UNDERFLOW:
        return "Stack Underflow";
    case GL_STACK_OVERFLOW:
        return "Stack Overflow";
    case GL_CONTEXT_LOST:
        return "Context Lost";
    default:
        return "Unknown Error";
    }
}
}