//
// Created by Trevor Starick on 2015-11-13.
//

#include "ResourceManager.h"

namespace Thanos {
    TextureCache ResourceManager::_textureCache;

    GLTexture ResourceManager::getTexture(std::string texturePath) {
        return _textureCache.getTexture(texturePath);
    }
}