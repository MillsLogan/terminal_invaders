#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "GameObject.hpp"
#include "Sprite.hpp"

class Player : public GameObject{
    private:
        int health;
        int score;
        int speed;
    public:
        Player(int x, int y, int width, int height, Sprite *sprite);
        void move(int x, int y);
        void setHealth(int health);
        void setScore(int score);
        void setSpeed(int speed);
        int getHealth();
        int getScore();
};


#endif