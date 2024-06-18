#ifndef GAME_HPP
#define GAME_HPP

#include <ncurses.h>
#include <vector>
#include "game_objects/player/Player.hpp"
#include "game_objects/enemies/Enemy.hpp"
#include "game_objects/projectiles/Projectile.hpp"
#include <list>
#include <memory>
#include <unordered_map>

class Game{
    private:
        int enemyUpdateCounter;
        int enemyUpdateRate;
        bool running;
        
        int height, width;
        WINDOW* gameWindow;

        Player *player;
        std::list<Enemy> enemies;
        std::list<Projectile> projectiles;
        std::unordered_map<std::string, std::shared_ptr<Sprite> > sprites;
        
        void updateProjectiles();
        void showWelcomeScreen();
        void showGameScreen();
        void updateEnemies();
        void init();
        bool verifyTerminalSize();
        void initGameObjects();
        void update();
        void updateStats();
        void checkCollisions();
    public:
        Game(int height, int width, int enemyUpdateRate);
        void start();
        void stop();
        ~Game();
};

#endif