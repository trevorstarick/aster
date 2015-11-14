//
// Created by Trevor Starick on 2015-11-13.
//

#ifndef ASTER_RESOURCEMANAGER_H
#define ASTER_RESOURCEMANAGER_H

#include "TextureCache.h"

class ResourceManager {
public:
    static GLTexture getTexture(std::string texturePath);
    static GLuint boundTexture;
private:
    static TextureCache _textureCache;
};


#endif //ASTER_RESOURCEMANAGER_H
