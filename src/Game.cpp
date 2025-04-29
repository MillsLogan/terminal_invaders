#include "Game.hpp"
#include <ncurses.h>
#include <iostream>
#include "game_objects/player/Player.hpp"
#include "game_objects/enemies/Enemy.hpp"
#include <unistd.h>
#include <memory>
#include <algorithm>

Game::Game(int height, int width, int enemyUpdateRate){
    this->height = height;
    this->width = width;
    running = false;
    enemyUpdateCounter = 0;
    this->enemyUpdateRate = enemyUpdateRate;
    this->sprites = std::unordered_map<std::string, std::shared_ptr<Sprite> >();
    this->projectileTimeout = 50;
    this->projectileTimeoutCounter = this->projectileTimeout;
}

void Game::init(){
    initscr();
    cbreak();
    noecho();
    start_color();
    
    while(!verifyTerminalSize()){
        endwin();
        std::cout << "Terminal size is too small" << std::endl;
        std::cout << "Please resize the terminal window to at least " << height << "x" << width << std::endl;
        std::cout << "Press any key to continue" << std::endl;
        std::cout << "Current size: " << LINES << "x" << COLS << std::endl;
        exit(1);
    }

    gameWindow = newwin(height, width, (LINES - height)/2, (COLS - width)/2);
    box(gameWindow, 0, 0);
    keypad(gameWindow, TRUE);
    curs_set(0);
}

bool Game::verifyTerminalSize(){
    return COLS >= width && LINES >= height;
}

void Game::showWelcomeScreen(){
    init();
    init_pair(1, COLOR_CYAN, COLOR_BLACK);
    init_pair(2, COLOR_RED, COLOR_BLACK);
    init_pair(3, COLOR_YELLOW, COLOR_BLACK);

    wattron(gameWindow, COLOR_PAIR(1));

    mvwprintw(gameWindow, 1, 1, "Welcome to the game");
    mvwprintw(gameWindow, 2, 1, "Press any key to start");
    mvwprintw(gameWindow, 3, 1, "Press 'q' at anytime to quit");

    wattroff(gameWindow, COLOR_PAIR(1));
    wrefresh(gameWindow);
    wgetch(gameWindow);
}

void Game::showGameScreen(){
    wclear(gameWindow);
    box(gameWindow, 0, 0);
    initGameObjects();
    wrefresh(gameWindow);
}

void Game::initGameObjects(){
    std::vector<std::string> playerSprite;
    playerSprite.push_back("  ^  ");
    playerSprite.push_back(" / \\ ");
    playerSprite.push_back("/___\\");

    std::vector<std::string> enemySprite;
    enemySprite.push_back("/0\\");
    std::vector<std::string> beamSprite;
    beamSprite.push_back("|");

    sprites["player"] = std::make_shared<Sprite>(Sprite(gameWindow, 1, playerSprite));
    sprites["enemy"] = std::make_shared<Sprite>(Sprite(gameWindow, 2, enemySprite));
    sprites["beam"] = std::make_shared<Sprite>(Sprite(gameWindow, 3, beamSprite));

    for(int i = 1; i <= 5; i++){
        for(int j = 1; j <= 11; j++){
            enemies.push_back(Enemy(j * 5, i * 3, sprites["enemy"], 1 + j * 5, width - 5 - (11 - j) * 5));
        }
    }
    
    
    for(auto &enemy : enemies){
        enemy.draw();
    }

    player = new Player(10, height - 5, sprites["player"]);
    player->draw();
    wrefresh(gameWindow);
}

void Game::start(){
    running = true;
    showWelcomeScreen();
    showGameScreen();
    nodelay(gameWindow, TRUE);
    int input;
    while(running){
        input = wgetch(gameWindow);
        if(input == 'q'){
            stop();
        }else if(input == KEY_LEFT){
            player->move(-1, 0);
        }else if(input == KEY_RIGHT){
            player->move(1, 0);
        }else if(input == KEY_UP){
            if(projectileTimeoutCounter == projectileTimeout){
                projectileTimeoutCounter = 0;
                projectiles.push_back(Projectile(player->getPosition().first + 1, player->getPosition().second - 1, sprites["beam"], std::make_pair(0, -1)));
            }
        }

        if(projectileTimeoutCounter < projectileTimeout){
            projectileTimeoutCounter++;
        }

        update();
        if(enemies.size() == 0){
            stop();
            wclear(gameWindow);
            mvwprintw(gameWindow, height/2, width/2, "You win!");
            wrefresh(gameWindow);
            nodelay(gameWindow, FALSE);
            wgetch(gameWindow);
            std::cout << "You win!" << std::endl;
            break;
        }
        usleep(1000000/60);
    }
}

void Game::updateEnemies(){
    enemyUpdateCounter++;
    if(enemyUpdateCounter < enemyUpdateRate){
        return;
    }

    enemyUpdateCounter = 0;
    
    for(Enemy &enemy : enemies){
        enemy.move();
        if (enemy.getPosition().second > height - 6) {
            running = false;
            wclear(gameWindow);
            mvwprintw(gameWindow, height/2, width/2, "Game Over");
            wrefresh(gameWindow);
            wgetch(gameWindow);
            endwin();
            std::cout << "Game Over" << std::endl;
            exit(0);            
        }
    }

    for(Enemy &enemy : enemies){
        enemy.draw();
    }
}

void Game::updateProjectiles(){
    for(auto it = projectiles.begin(); it != projectiles.end();){
        it->move();
        if(it->getPosition().second < 1 || it->getPosition().second > height-1){
            it = projectiles.erase(it);
        }else{
            it->draw();
        }
        it++;
    }
}

void Game::update(){
    player->draw();

    updateProjectiles();
    updateEnemies();
    checkCollisions();
    updateStats();

    wrefresh(gameWindow);
}

void Game::checkCollisions(){
    for(auto it = projectiles.begin(); it != projectiles.end();){
        for(auto enemy = enemies.begin(); enemy != enemies.end();){
            if(it->getPosition().first >= enemy->getPosition().first && it->getPosition().first < enemy->getPosition().first + enemy->getSize().first){
                if(it->getPosition().second >= enemy->getPosition().second && it->getPosition().second < enemy->getPosition().second + enemy->getSize().second){
                    it = projectiles.erase(it);
                    enemy = enemies.erase(enemy);
                    break;
                }
            }
            enemy++;
        }
        it++;
    }
}

void Game::updateStats(){
    mvwprintw(gameWindow, 1, 1, "Press 'q' to quit");
    mvwprintw(gameWindow, 2, 1, "Player position: %d, %d", player->getPosition().first, player->getPosition().second);
    mvwprintw(gameWindow, 3, 1, "Enemies: %ld", enemies.size());
    mvwprintw(gameWindow, 4, 1, "Projectiles: %ld", projectiles.size());
}

void Game::stop(){
    running = false;
}

Game::~Game(){
    delete player;
    delwin(gameWindow);
    endwin();
}