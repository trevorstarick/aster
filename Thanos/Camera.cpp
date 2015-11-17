//
// Created by Trevor Starick on 2015-11-14.
//

#include <iostream>
#include "Camera.h"

namespace  Thanos {
Camera::Camera() :
        _position(0.0f, 0.0f),
        _cameraMatrix(1.0f),
        _orthoMatrix(1.0f),
        _scale(1.0f),
        _needsUpdate(true),
        _screenWidth(500),
        _screenHeight(500) { }

Camera::~Camera() { }

void Camera::init(int screenWidth, int screenHeight){
    _screenWidth = screenWidth;
    _screenHeight = screenHeight;

    _orthoMatrix = glm::ortho(0.0f, (float)_screenWidth, 0.0f, (float)_screenHeight);
};

void Camera::update() {
    if(_needsUpdate) {
        glm::vec3 translate(-_position.x + _screenWidth / 2, -_position.y + _screenHeight / 2, 0.0f);
        _cameraMatrix = glm::translate(_orthoMatrix, translate);

        glm::vec3 scale(_scale, _scale, 0.0f);
        _cameraMatrix = glm::scale(glm::mat4(1.0f), scale) * _cameraMatrix;

        _needsUpdate = false;
    }
}

}