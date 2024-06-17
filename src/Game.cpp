#include "Game.hpp"
#include <ncurses.h>
#include <iostream>
#include "game_objects/Player.hpp"
#include "game_objects/Enemy.hpp"
#include <unistd.h>

Game::Game(int height, int width){
    this->height = height;
    this->width = width;
    running = false;
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
    
    enemyMovementDirection = 1;

    enemies.push_back(new Enemy(10, 10, 3, 3, new Sprite(gameWindow, "red", enemySprite)));
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
        if(wgetch(gameWindow) == 'q'){
            stop();
        }else if(input == KEY_LEFT){
            player->move(-1, 0);
        }else if(input == KEY_RIGHT){
            player->move(1, 0);
        }
        update();
    }
}

void Game::update(){
    player->draw();

    for(auto &enemy : enemies){
        enemy->move(enemyMovementDirection, 0);
        if(enemy->getPosition().first == 1 || enemy->getPosition().first == width - 1 - enemy->getSize().first){
            enemyMovementDirection *= -1;
        }
    }

    for(int i = 0; i < enemies.size(); i++){
        enemies[i]->draw();
    }

    player->draw();
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