#include "GameObject.hpp"
#include <ncurses.h>

GameObject::GameObject(int x, int y, std::shared_ptr<Sprite> sprite){
    this->x = x;
    this->y = y;
    this->sprite = sprite;
    this->speed = 1;
    this->previousPosition = std::make_pair(-1, -1);
}

GameObject::GameObject(int x, int y, std::shared_ptr<Sprite> sprite, int speed){
    this->x = x;
    this->y = y;
    this->sprite = sprite;
    this->speed = speed;
    this->previousPosition = std::make_pair(-1, -1);
}

void GameObject::move(int x, int y){
    int newX = this->x + x * speed;
    int newY = this->y + y * speed;
    setPosition(newX, newY);
}

void GameObject::setPosition(int x, int y){
    this->x = x;
    this->y = y;
}

std::pair<int, int> GameObject::getPosition(){
    return std::make_pair(x, y);
}

std::pair<int, int> GameObject::getSize(){
    return std::make_pair(sprite->getWidth(), sprite->getHeight());
}

void GameObject::draw(){
    if(x == previousPosition.first && y == previousPosition.second){
        return;
    }else{
        sprite->clear(previousPosition.first, previousPosition.second);
        sprite->draw(x, y);
        previousPosition = std::make_pair(x, y);
    }
}

GameObject::~GameObject(){
    sprite->clear(previousPosition.first, previousPosition.second);
}
