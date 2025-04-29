#include <ncurses.h>
#include "Game.hpp"


int main(){
    Game game = Game(40, 100, 10);
    game.start();
    endwin(); // Clean up on game win
    return 0;
}