//
// Created by trevorstarick on 2015-11-18.
//

#ifndef ASTER_INPUTMANAGER_H
#define ASTER_INPUTMANAGER_H

#include <unordered_map>

namespace Thanos {

    class InputManager {
    public:
        void pressedKey(unsigned int keyID);
        void releaseKey(unsigned int keyID);
        bool isKeyPressed(unsigned int keyId);

        void pressedJoy(unsigned int joyID, int weight);
        void releaseJoy(unsigned int joyID);
        bool isJoyPressed(unsigned int joyId);
    private:
        std::unordered_map<unsigned int, bool> _keyMap;
        std::unordered_map<unsigned int, int>  _joyMap;
    };

}

#endif //ASTER_INPUTMANAGER_H
