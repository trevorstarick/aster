//
// Created by Trevor Starick on 2015-11-13.
//

#ifndef ASTER_IMAGELOADER_H
#define ASTER_IMAGELOADER_H

#include <string>
#include "GLTexture.h"

namespace Thanos {

    class ImageLoader {
    public:
        static GLTexture loadPNG(std::string filePath);
    };

}

#endif //ASTER_IMAGELOADER_H
