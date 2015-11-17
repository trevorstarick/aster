//
// Created by Trevor Starick on 2015-11-14.
//

#ifndef ASTER_CAMERA_H
#define ASTER_CAMERA_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace Thanos {

    class Camera {
    public:
        Camera();
        ~Camera();

        void init(int screenWidth, int screenHeight);

        void update();

        void setPosition(const glm::vec2 &newPosition) { _position = newPosition; _needsUpdate = true; }
        void setScale(float newScale) { _scale = newScale; _needsUpdate = true; }

        glm::vec2 getPosition() { return _position; }
        float getScale() { return _scale; }
        glm::mat4 getCameraMatrix() { return _cameraMatrix; }

    private:
        int _screenWidth, _screenHeight;
        bool _needsUpdate;
        float _scale;
        glm::vec2 _position;
        glm::mat4 _cameraMatrix;
        glm::mat4 _orthoMatrix;
    };
}

#endif //ASTER_CAMERA_H
