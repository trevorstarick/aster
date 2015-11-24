//
// Created by Trevor Starick on 2015-11-24.
//

#ifndef ASTER_ENTITIES_H
#define ASTER_ENTITIES_H

#include <vector>
#include <glm/glm.hpp>

#include "InputManager.h"
#include "Camera.h"

namespace Thanos {
    class Player {
        public:
            Player();
            ~Player();

            void init(float speed, glm::vec2 position, Thanos::InputManager *inputManager, Thanos::Camera *camera);
            void update(float deltaTime);
            glm::vec2 getPosition() const { return _position; }


        private:
            Thanos::InputManager *_inputManager;
            Thanos::Camera *_camera;
            float _speed;
            glm::vec2 _position;

    };
}
#endif //ASTER_ENTITIES_H
