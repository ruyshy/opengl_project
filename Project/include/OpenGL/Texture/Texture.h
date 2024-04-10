#pragma once

#ifndef TEXTURE_H_
#define TEXTURE_H_

class Texture
{
public:
    ~Texture();

    bool createFromData(const unsigned char* data, GLsizei width, GLsizei height, GLenum format, bool generateMipmaps = false);
    bool loadTexture2D(const std::string& filePath, bool generateMipmaps = true);
    void bind(GLenum textureUnit = 0) const;
    void deleteTexture();
    GLuint getID() const;
    std::string getFilePath() const;
    GLsizei getWidth() const;
    GLsizei getHeight() const;

    bool isLoaded() const;

    bool resize(GLsizei newWidth, GLsizei newHeight);
    static int getNumTextureImageUnits();
    
private:
    GLuint textureID_ = 0; 
    GLsizei width_ = 0; 
    GLsizei height_ = 0; 
    GLenum format_ {0}; 
    std::string filePath_;

    bool isLoadedCheck() const;
};

#endif // !TEXTURE_H_
