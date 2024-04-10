#pragma once
#ifndef TEXTUREMANAGER_H_
#define TEXTUREMANAGER_H_

#include <OpenGL/Texture/Texture.h>

class TextureManager
{
public:
    static TextureManager& getInstance();
    void loadTexture2D(const string& key, const string& fileName, bool generateMipmaps = true);
    const Texture& getTexture(const string& key) const;
    bool containsTexture(const string& key) const;
    string containsTextureWithPath(const string& filePath) const;
    bool deleteTexture(const string& key);
    void clearTextureCache();

private:
    TextureManager() {}
	TextureManager(const TextureManager&) = delete;
	void operator=(const TextureManager&) = delete;

    map<string, unique_ptr<Texture>> _textureCache;
};

#endif // !TEXTUREMANAGER_H_
