#ifndef ENEMY_HPP
#define ENEMY_HPP

#include "../GameObject.hpp"
#include "../sprite/Sprite.hpp"

class Enemy : public GameObject{
    private:
        int left_bound;
        int right_bound;
        std::pair<int, int> movementDirection;
    public:
        Enemy(int x, int y, std::shared_ptr<Sprite> sprite, int speed, int left_bound, int right_bound);
        Enemy(int x, int y, std::shared_ptr<Sprite> sprite, int left_bound, int right_bound);
        void move();
        ~Enemy();
};

#endif