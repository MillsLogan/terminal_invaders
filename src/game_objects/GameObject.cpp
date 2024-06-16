#include "GameObject.hpp"
#include <ncurses.h>

GameObject::GameObject(int x, int y, int width, int height, Sprite* sprite){
    this->x = x;
    this->y = y;
    this->width = width;
    this->height = height;
    this->sprite = sprite;
    this->previousPosition = std::make_pair(x, y);
}

bool GameObject::move(int x, int y){
    int newX = this->x + x;
    int newY = this->y + y;
    return setPosition(newX, newY);
}

bool GameObject::setPosition(int x, int y){
    if(x < 0 || x >= COLS || y < 0 || y >= LINES){
        return false;
    }
    this->x = x;
    this->y = y;
    return true;
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

