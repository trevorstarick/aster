#include <SDL.h>

#include "Entities.h"

namespace Thanos {
    Player::Player() { }
    Player::~Player() { }

    void Player::init(float speed, glm::vec2 position, Thanos::InputManager *inputManager, Thanos::Camera *camera) {
        _speed = speed;
        _position = position;
        _inputManager = inputManager;
        _camera = camera;
    }

    void Player::update(float deltaTime) {
        if (_inputManager->isKeyDown(SDLK_w)) {
            _position.y += _speed * deltaTime;
        } else if (_inputManager->isKeyDown(SDLK_s)) {
            _position.y -= _speed * deltaTime;
        }

        if (_inputManager->isKeyDown(SDLK_a)) {
            _position.x -= _speed * deltaTime;
        } else if (_inputManager->isKeyDown(SDLK_d)) {
            _position.x += _speed * deltaTime;
        }
    }
}