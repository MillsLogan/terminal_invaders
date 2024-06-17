#include "Player.hpp"


Player::Player(int x, int y, int width, int height, Sprite *sprite) : GameObject(x, y, width, height, sprite){
    this->health = 100;
    this->score = 0;
    this->speed = 1;
}

void Player::move(int x, int y){
    GameObject::move(x * speed, y * speed);
}

void Player::setHealth(int health){
    this->health = health;
}

void Player::setScore(int score){
    this->score = score;
}

void Player::setSpeed(int speed){
    this->speed = speed;
}

int Player::getHealth(){
    return health;
}

int Player::getScore(){
    return score;
}