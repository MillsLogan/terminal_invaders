#include "Enemy.hpp"
#include "../GameObject.hpp"
#include "../sprite/Sprite.hpp"

Enemy::Enemy(int x, int y, std::shared_ptr<Sprite> sprite, int speed, int left_bound, int right_bound) : GameObject(x, y, sprite, speed){
    this->left_bound = left_bound;
    this->right_bound = right_bound;
    this->movementDirection = std::make_pair(1, 0); // Just indicating a direction not the speed
}

Enemy::Enemy(int x, int y, std::shared_ptr<Sprite> sprite, int left_bound, int right_bound) : GameObject(x, y, sprite){
    this->left_bound = left_bound;
    this->right_bound = right_bound;
    this->movementDirection = std::make_pair(1, 0); // Just indicating a direction not the speed
}

void Enemy::move(){
    if(x == left_bound){
        if(movementDirection.first == 0){ // If just moved down
            movementDirection.first = 1; // Start moving right
            movementDirection.second = 0; // Stop moving down
        }else{ // Else move down
            movementDirection.first = 0; // Stop moving left
            movementDirection.second = 1; // Start moving down
        }
    }else if(x == right_bound){
        if(movementDirection.first == 0){ // If just moved down
            movementDirection.first = -1; // Start moving left
            movementDirection.second = 0; // Stop moving down
        }else{ // Else move down
            movementDirection.first = 0; // Stop moving right
            movementDirection.second = 1; // Start moving down
        }
    }

    GameObject::move(movementDirection.first, movementDirection.second);
}

Enemy::~Enemy(){
    // Destructor
}

