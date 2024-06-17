#include "Enemy.hpp"
#include "GameObject.hpp"
#include "Sprite.hpp"

Enemy::Enemy(int x, int y, int width, int height, Sprite *sprite) : GameObject(x, y, width, height, sprite){
    this->speed = 1;
}

void Enemy::move(int x, int y){
    GameObject::move(x * speed, y * speed);
}

void Enemy::setSpeed(int speed){
    this->speed = speed;
}
