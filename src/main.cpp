#include <ncurses.h>
#include <iostream>
#include "game_objects/GameObject.hpp"
#include "game_objects/Sprite.hpp"

void setupNcurses(){
    initscr();
    start_color();
    cbreak();
    keypad(stdscr, TRUE);
    curs_set(0);
    noecho();
}

int main(){
    setupNcurses();
    int input;
    init_pair(1, COLOR_CYAN, COLOR_BLACK);
    printw("Press 'q' to quit\n");
    std::vector<std::string> sprite = std::vector<std::string>();
    sprite.push_back(" 0 ");
    sprite.push_back("/|\\");
    sprite.push_back("/ \\");
    Sprite* playerSprite = new Sprite("green", sprite);
    GameObject player(0, 0, 3, 3, playerSprite);
    
    while((input = getch()) != 'q'){
        switch(input){
            case KEY_UP:
                player.move(0, -1);
                break;
            case KEY_DOWN:
                player.move(0, 1);
                break;
            case KEY_LEFT:
                player.move(-1, 0);
                break;
            case KEY_RIGHT:
                player.move(1, 0);
                break;
        }
        player.draw();
    }

    endwin();
    return 0;
}