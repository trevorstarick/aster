//
// Created by Trevor Starick on 2015-11-24.
//

#include "WorldGen.h"
#include <random>

namespace Thanos {
    void WorldGen::init() {
        std::random_device rd;
        std::mt19937 gen(rd());

        _idLookupTable[0] = "";
        _idLookupTable[1] = "textures/PNG/tileGrass.png";
        _idLookupTable[2] = "textures/PNG/tileMagic.png";

        for(int y = 0; y < _width; y++) {
            for(int x = 0; x < _height; x++) {
                int rand = gen() % 10;

                if(rand == 4) {
                    _worldMap.push_back(2);
                } else {
                    _worldMap.push_back(1);
                }
            }
        }
    }
}