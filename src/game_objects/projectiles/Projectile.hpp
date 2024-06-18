#ifndef PROJECTILE_HPP
#define PROJECTILE_HPP

#include "../GameObject.hpp"
#include "../sprite/Sprite.hpp"

class Projectile : public GameObject{
    private:
        std::pair<int, int> direction;
    public:
        Projectile(int x, int y, std::shared_ptr<Sprite> sprite, int speed, std::pair<int, int> direction);
        Projectile(int x, int y, std::shared_ptr<Sprite> sprite, std::pair<int, int> direction);
        void setDirection(std::pair<int, int> direction);
        void setDirection(int x, int y);
        std::pair<int, int> getDirection();
        void move();
        void setDirectionAndMove(int x, int y);
        void setDirectionAndMove(std::pair<int, int> direction);
};

#endif