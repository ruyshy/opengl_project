#include <pch.h>
#include <OpenGL/TextRender/TextRendering.h>

#include <Manager/ResourceManager.h>
#include <rc/shader_resource.h>
#include <rc/font_resource.h>

TextRendering::TextRendering(UINT ID, mat4 projection_matrix, mat4 view_matrix, vec2 position, float scale) :
    mpFile_path(0), mpProjectionMatrix(projection_matrix), mpViewMatrix(view_matrix), mTextScale(scale), mPosition(position)
{
    mpShader = new Shader(
        ResourceManager::GetResourceString(IDR_SHADER_TEXT_VS, Resource::SHADER),
        ResourceManager::GetResourceString(IDR_SHADER_TEXT_FS, Resource::SHADER)
    );

    string font_data = ResourceManager::GetResourceString(ID, Resource::FONT);

    FT_Library ft;
    FT_Face face;
    FT_Init_FreeType(&ft);
    FT_New_Memory_Face(ft, (const FT_Byte*)font_data.c_str(), static_cast<unsigned int>(font_data.size()), 0, &face);
    FT_Set_Pixel_Sizes(face, 0, 50);
    FT_Load_Char(face, 'X', FT_LOAD_RENDER);

    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    for (unsigned char c = 0; c < 128; c++)
    {
        if (FT_Load_Char(face, c, FT_LOAD_RENDER))
        {
            cout << "ERROR::FREETYTPE: Failed to load Glyph" << endl;
            continue;
        }
        unsigned int texture;
        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);
        glTexImage2D(
            GL_TEXTURE_2D,
            0,
            GL_RED,
            face->glyph->bitmap.width,
            face->glyph->bitmap.rows,
            0,
            GL_RED,
            GL_UNSIGNED_BYTE,
            face->glyph->bitmap.buffer
        );

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        Character character = {
            texture,
            glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
            glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
            face->glyph->advance.x
        };
        Characters.insert(std::pair<char, Character>(c, character));

        float xpos = mPosition.x + character.Bearing.x * mTextScale;
        float ypos = mPosition.y - (character.Size.y - character.Bearing.y) * mTextScale;
        float w = character.Size.x * mTextScale;
        float h = character.Size.y * mTextScale;
        
        mSize.x = character.Size.x;
        mSize.y = character.Size.y;

    }
    FT_Done_Face(face);
    FT_Done_FreeType(ft);

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

TextRendering::~TextRendering()
{
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);

    NULLPTR_CHECK_DELETE(mpShader);
}

void TextRendering::SetPosition(vec2 position) { mPosition = position; }
void TextRendering::SetSize(vec2 size) { mSize = size; }

vec2 TextRendering::GetPosition() { return mPosition; }
vec2 TextRendering::GetSize() { return mSize; }

void TextRendering::RenderText(std::string text, glm::vec3 color)
{
    RenderText(text, mPosition.x, mPosition.y, mTextScale, color);
}

void TextRendering::RenderText(std::string text, float x, float y, glm::vec3 color)
{
    RenderText(text, x, y, mTextScale, color);
}

void TextRendering::RenderText(std::string text, float x, float y, float scale, glm::vec3 color)
{
    glDisable(GL_DEPTH_TEST);


    mpShader->use();
    mpShader->setMat4("projection", mpProjectionMatrix);
    mpShader->setVec3("textColor", color);

    glActiveTexture(GL_TEXTURE0);
    glBindVertexArray(VAO);

    std::string::const_iterator c;
    for (c = text.begin(); c != text.end(); c++)
    {
        Character ch = Characters[*c];

        float xpos = x + ch.Bearing.x * scale;
        float ypos = y - (ch.Size.y - ch.Bearing.y) * scale;

        float w = ch.Size.x * scale;
        float h = ch.Size.y * scale;
        float vertices[6][4] = {
            { xpos,     ypos + h,   0.0f, 0.0f },
            { xpos,     ypos,       0.0f, 1.0f },
            { xpos + w, ypos,       1.0f, 1.0f },

            { xpos,     ypos + h,   0.0f, 0.0f },
            { xpos + w, ypos,       1.0f, 1.0f },
            { xpos + w, ypos + h,   1.0f, 0.0f }
        };
        glBindTexture(GL_TEXTURE_2D, ch.TextureID);

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);

        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glDrawArrays(GL_TRIANGLES, 0, 6);
        x += (ch.Advance >> 6) * scale;
    }

    glBindVertexArray(0);
    glBindTexture(GL_TEXTURE_2D, 0);
    glEnable(GL_DEPTH_TEST);
}

void TextRendering::RenderText(std::string text, vec2 pos, float scale, glm::vec3 color)
{
    RenderText(text, pos.x, pos.y, scale, color);
}
