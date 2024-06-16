#ifndef GAMEOBJECT_HPP
#define GAMEOBJECT_HPP

#include <string>
#include "Sprite.hpp"

class GameObject{
    private:
        int x;
        int y;
        int width;
        int height;
        Sprite *sprite;
        std::pair<int, int> previousPosition;
    public:
        GameObject(int x, int y, int width, int height, Sprite *sprite);
        bool move(int x, int y);
        void draw();
        bool setPosition(int x, int y);
        std::pair<int, int> getPosition();
        std::pair<int, int> getSize();
};


#endif