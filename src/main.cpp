#include <ncurses.h>
#include "Game.hpp"


int main(){
    int input;
    Game game = Game(40, 200, 2);
    game.start();

    return 0;
}