#ifndef GAME_HPP
#define GAME_HPP

#include <ncurses.h>
#include <vector>

class Game{
    private:
        Player player;
        std::vector<Enemy> enemies;
        std::vector<Projectile> projectiles;
        bool running;
    public:
        Game();
        void showWelcomeScreen();
        void start();
        void stop();
        bool isRunning();
};

#endif