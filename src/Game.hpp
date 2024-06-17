#ifndef GAME_HPP
#define GAME_HPP

#include <ncurses.h>
#include <vector>
#include "game_objects/Player.hpp"
#include "game_objects/Enemy.hpp"

class Game{
    private:
        Player *player;
        std::vector<Enemy*> enemies;
        int enemyMovementDirection;
        // std::vector<Projectile> projectiles;
        int height, width;
        bool running;
        void showWelcomeScreen();
        void showGameScreen();
        WINDOW *gameWindow;
        void init();
        bool verifyTerminalSize();
        void initGameObjects();
        void update();
    public:
        Game(int height, int width);
        void start();
        void stop();
        ~Game();
};

#endif