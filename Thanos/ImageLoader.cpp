//
// Created by Trevor Starick on 2015-11-13.
//

#include <iostream>
#include "ImageLoader.h"
#include "picopng.h"
#include "IOManager.h"


namespace Thanos {

    GLTexture ImageLoader::loadPNG(std::string filePath) {
        GLTexture texture = {};

        std::vector<unsigned char> in, out;
        unsigned long height, width;

        if (IOManager::readFileToBuffer(filePath, in) == false) {
            std::cout << "Failed to load PNG file to buffer!\n";
        };

        int errorCode = decodePNG(out, width, height, &(in[0]), in.size());
        if (errorCode != 0) {
            std::cout << "DecodePNG failed with error: " + std::to_string(errorCode) + "\n";
        }

        glGenTextures(1, &(texture.id));
        glBindTexture(GL_TEXTURE_2D, texture.id);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, &(out[0]));

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

        glGenerateMipmap(GL_TEXTURE_2D);

        glBindTexture(GL_TEXTURE_2D, 0);

        texture.width = width;
        texture.height = height;

        return texture;
    }

}