#include "Player.hpp"


Player::Player(int x, int y, std::shared_ptr<Sprite> sprite) : GameObject(x, y, sprite){
    this->health = 100;
    this->score = 0;
    this->speed = 1;
}

Player::Player(int x, int y, std::shared_ptr<Sprite> sprite, int speed) : GameObject(x, y, sprite, speed){
    this->health = 100;
    this->score = 0;
    this->speed = speed;
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

int Player::getHealth(){
    return health;
}

int Player::getScore(){
    return score;
}
