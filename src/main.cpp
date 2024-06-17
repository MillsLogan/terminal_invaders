#include <ncurses.h>
#include <iostream>
#include "game_objects/GameObject.hpp"
#include "game_objects/Sprite.hpp"
#include "Game.hpp"

int main(){
    int input;
    Game game = Game(40, 200, 5);
    game.start();
    return 0;
}