#include "Game.hpp"
#include <ncurses.h>
#include <iostream>
#include "game_objects/Player.hpp"
#include "game_objects/Enemy.hpp"
#include <unistd.h>

Game::Game(int height, int width, int enemyUpdateRate){
    this->height = height;
    this->width = width;
    running = false;
    enemyUpdateCounter = 0;
    this->enemyUpdateRate = enemyUpdateRate;
}

void Game::init(){
    initscr();
    cbreak();
    noecho();
    start_color();
    if(!verifyTerminalSize()){
        endwin();
        std::cout << "Terminal size is too small" << std::endl;
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
    
    currentEnemyMovement = std::pair<int, int>(1, 0);

    enemies.push_back(new Enemy(10, 10, 3, 3, new Sprite(gameWindow, "red", enemySprite)));
    enemies.push_back(new Enemy(15, 10, 3, 3, new Sprite(gameWindow, "red", enemySprite)));
    for(int i = 0; i < enemies.size(); i++){
        enemies[i]->draw();
    }

    Sprite *sprite = new Sprite(gameWindow, "cyan", playerSprite);
    player = new Player(10, height - 5, 3, 5, sprite);
    player->draw();
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
        }

        update();

        usleep(1000000/60);
    }
}

void Game::updateEnemiesDirection(std::pair<int, int> nextEnemyMovement){
    // If the enemies have not moved down yet, we can keep moving them the same way/use the new direction variable
    if(currentEnemyMovement != std::pair<int, int>(0,1)){
        currentEnemyMovement = nextEnemyMovement;
        return;
    }
    // If the enemies have moved down, we need to move them in the other direction
    if(enemies[0]->getPosition().first == 1){
        // If the enemy in the leftmost position has reached the leftmost wall, we need to move them to the right
        currentEnemyMovement.first = 1;
    }else{
        // If the enemy in the rightmost position has reached the rightmost wall, we need to move them to the left
        currentEnemyMovement.first = -1;
    }
    currentEnemyMovement.second = 0;
}

void Game::updateEnemies(){
    enemyUpdateCounter++;
    if(enemyUpdateCounter < enemyUpdateRate){
        return;
    }

    enemyUpdateCounter = 0;
    std::pair<int, int> nextEnemyMovement = currentEnemyMovement;
    
    for(auto &enemy : enemies){
        enemy->move(currentEnemyMovement.first, currentEnemyMovement.second);
        if(enemy->getPosition().first == 1 || enemy->getPosition().first == width - 1 - enemy->getSize().first){
            nextEnemyMovement.first = 0;
            nextEnemyMovement.second = 1;
        }
    }

    updateEnemiesDirection(nextEnemyMovement);

    for(int i = 0; i < enemies.size(); i++){
        enemies[i]->draw();
    }
}

void Game::update(){
    player->draw();

    updateEnemies();

    wrefresh(gameWindow);
}

void Game::stop(){
    running = false;
}

Game::~Game(){
    delete player;
    delwin(gameWindow);
    endwin();
}