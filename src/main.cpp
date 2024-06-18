#include <ncurses.h>
#include "Game.hpp"


int main(){
    int input;
    Game game = Game(40, 100, 10);
    game.start();

    return 0;
}