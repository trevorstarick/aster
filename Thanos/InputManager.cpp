//
// Created by trevorstarick on 2015-11-18.
//

#include "InputManager.h"

namespace Thanos {
    void InputManager::pressedKey(unsigned int keyID) {
        _keyMap[keyId] = true;
    }

    void InputManager::releaseKey(unsigned int keyID) {
        _keyMap[keyId] = false;
    }

    void InputManager::pressedJoy(unsigned int joyID, int weight) {
        _joyMap[joyID] = weight;
    }

    void InputManager::releaseJoy(unsigned int joyID) {
        delete _keyMap[joyID];
    }

    bool InputManager::isKeyPressed(unsigned int keyID) {
        auto it = _keyMap.find(keyID);
        if(it != _keyMap.end()) {
            return it->second;
        } else {
            return false;
        }
    };

    bool InputManager::isJoyPressed(unsigned int joyID) {
        auto it = _joyMap.find(joyID);
        if(it != _joyMap.end()) {
            return it->second;
        } else {
            return false;
        }
    };
}
