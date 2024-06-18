#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "../GameObject.hpp"
#include "../sprite/Sprite.hpp"

class Player : public GameObject{
    private:
        int health;
        int score;
    public:
        Player(int x, int y, std::shared_ptr<Sprite> sprite, int speed);
        Player(int x, int y, std::shared_ptr<Sprite> sprite);
        void move(int x, int y);
        void setHealth(int health);
        void setScore(int score);
        int getHealth();
        int getScore();
};


#endif