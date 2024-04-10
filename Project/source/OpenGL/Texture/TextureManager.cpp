#include <pch.h>
#include <OpenGL/Texture/TextureManager.h>

TextureManager& TextureManager::getInstance()
{
    static TextureManager tm;
    return tm;
}

void TextureManager::loadTexture2D(const string& key, const string& fileName, bool generateMipmaps)
{
    if (containsTexture(key)) {
        return;
    }

    auto texturePtr = make_unique<Texture>();
    if (!texturePtr->loadTexture2D(fileName, generateMipmaps))
    {
        auto msg = "Could not load texture with key '" + key + "' from file '" + fileName + "'!";
        throw runtime_error(msg.c_str());
    }
    _textureCache[key] = move(texturePtr);
}

const Texture& TextureManager::getTexture(const string& key) const
{
    if (!containsTexture(key))
    {
        auto msg = "Attempting to get non-existing texture with key '" + key + "'!";
        throw runtime_error(msg.c_str());
    }

    return *_textureCache.at(key).get();
}

bool TextureManager::deleteTexture(const string& key)
{
    if (containsTexture(key))
    {
        _textureCache.erase(key);
        return true;
    }

    return false;
}

void TextureManager::clearTextureCache()
{
    _textureCache.clear();
}

bool TextureManager::containsTexture(const string& key) const
{
    return _textureCache.count(key) > 0;
}

string TextureManager::containsTextureWithPath(const string& filePath) const
{
    for (const auto& keyTexturePair : _textureCache)
    {
        const auto& key = keyTexturePair.first;
        const auto& texture = keyTexturePair.second;
        if (texture->getFilePath() == filePath) {
            return key;
        }
    }

    return "";
}
