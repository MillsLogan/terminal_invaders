#include "Projectile.hpp"

Projectile::Projectile(int x, int y, std::shared_ptr<Sprite> sprite, int speed, std::pair<int, int> direction) : GameObject(x, y, sprite){
    this->direction = direction;
}

Projectile::Projectile(int x, int y, std::shared_ptr<Sprite> sprite, std::pair<int, int> direction) : GameObject(x, y, sprite){
    this->direction = direction;
}

void Projectile::setDirection(std::pair<int, int> direction){
    this->direction = direction;
}

void Projectile::setDirection(int x, int y){
    setDirection(std::make_pair(x, y));
}

std::pair<int, int> Projectile::getDirection(){
    return direction;
}

void Projectile::move(){
    GameObject::move(direction.first, direction.second);
}

void Projectile::setDirectionAndMove(int x, int y){
    setDirection(std::make_pair(x, y));
    GameObject::move(x, y);
}

void Projectile::setDirectionAndMove(std::pair<int, int> direction){
    setDirection(direction);
    GameObject::move(direction.first, direction.second);
}