//
// Created by Trevor Starick on 2015-11-13.
//

#ifndef ASTER_TEXTURECACHE_H
#define ASTER_TEXTURECACHE_H


#include <map>
#include <string>
#include "GLTexture.h"

class TextureCache {
public:
    TextureCache();
    ~TextureCache();
    GLTexture getTexture(std::string texturePath);

private:
    std::map<std::string, GLTexture> _textureMap;
};

#endif //ASTER_TEXTURECACHE_H
