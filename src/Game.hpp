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
        std::pair<int, int> currentEnemyMovement;
        int enemyUpdateCounter;
        int enemyUpdateRate;
        // std::vector<Projectile> projectiles;
        int height, width;
        bool running;
        void showWelcomeScreen();
        void showGameScreen();
        void updateEnemies();
        void updateEnemiesDirection(std::pair<int, int> nextEnemyMovement);
        WINDOW *gameWindow;
        void init();
        bool verifyTerminalSize();
        void initGameObjects();
        void update();
    public:
        Game(int height, int width, int enemyUpdateRate);
        void start();
        void stop();
        ~Game();
};

#endif