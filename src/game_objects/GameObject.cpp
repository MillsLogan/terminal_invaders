#include "GameObject.hpp"
#include <ncurses.h>

GameObject::GameObject(int x, int y, int width, int height, Sprite* sprite){
    this->x = x;
    this->y = y;
    this->width = width;
    this->height = height;
    this->sprite = sprite;
    this->previousPosition = std::make_pair(-1, -1);
}

void GameObject::move(int x, int y){
    int newX = this->x + x;
    int newY = this->y + y;
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
    return std::make_pair(width, height);
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
    delete sprite;
}

