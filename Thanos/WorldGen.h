//
// Created by Trevor Starick on 2015-11-24.
//

#ifndef ASTER_WORLDGEN_H
#define ASTER_WORLDGEN_H

#include <vector>
#include <map>
#include <string>

enum SHAPES {
    CIRCLE,
    SQUARE,
    TOP_TRIANGLE,
    BOT_TRIANGLE
};

namespace Thanos {

    class WorldGen {
        public:
            void init();
            void update();
        private:
            int _width = 5;
            int _height = 5;
            int _radius = 3;
            int _shape = SHAPES::CIRCLE;

            std::map<int, std::string> _idLookupTable;
            std::vector<int> _worldMap;
    };

}

#endif //ASTER_WORLDGEN_H
