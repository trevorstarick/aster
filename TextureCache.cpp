//
// Created by Trevor Starick on 2015-11-13.
//

#include <iostream>
#include "TextureCache.h"
#include "ImageLoader.h"

TextureCache::TextureCache() { }
TextureCache::~TextureCache() { }

GLTexture TextureCache::getTexture(std::string texturePath) {
    auto mit = _textureMap.find(texturePath);

    if(mit == _textureMap.end()) {
        GLTexture newTexture = ImageLoader::loadPNG(texturePath);

        _textureMap.insert(make_pair(texturePath, newTexture));

        std::cout << "Loaded Regular Texture. \n";

        return newTexture;
    }
    std::cout << "Loaded Cached Texture. \n";


    return mit->second;
}