#ifndef ENEMY_HPP
#define ENEMY_HPP

#include "GameObject.hpp"
#include "Sprite.hpp"

class Enemy : public GameObject{
    private:
        int speed;
    public:
        Enemy(int x, int y, int width, int height, Sprite *sprite);
        void move(int x, int y);
        void setSpeed(int speed);
};

#endif