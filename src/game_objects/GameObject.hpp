#ifndef GAMEOBJECT_HPP
#define GAMEOBJECT_HPP

#include <string>
#include <memory>
#include "sprite/Sprite.hpp"

class GameObject{
    protected:
        int x;
        int y;
        int speed;
        std::shared_ptr<Sprite> sprite;
        std::pair<int, int> previousPosition;
    public:
        GameObject(int x, int y, std::shared_ptr<Sprite> sprite, int speed);
        GameObject(int x, int y, std::shared_ptr<Sprite> sprite);
        void move(int x, int y);
        void draw();
        void setPosition(int x, int y);
        std::pair<int, int> getPosition();
        std::pair<int, int> getSize();
        ~GameObject();
};


#endif