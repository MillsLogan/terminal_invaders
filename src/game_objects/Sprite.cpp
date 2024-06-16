#include "Sprite.hpp"
#include <ncurses.h>


Sprite::Sprite(std::string color, std::vector<std::string> sprite){
    this->color = color;
    this->sprite = sprite;
    this->clearSprite = std::vector<std::string>();
    for(int i = 0; i < sprite.size(); i++){
        std::string row = "";
        for(int j = 0; j < sprite[i].size(); j++){
            row += " ";
        }
        clearSprite.push_back(row);
    }
}

void Sprite::draw(int x, int y){
    attron(COLOR_PAIR(1));
    for(int i = 0; i < sprite.size(); i++){
        mvprintw(y + i, x, sprite[i].c_str());
    }
}

void Sprite::clear(int x, int y){
    attron(COLOR_PAIR(0));
    for(int i = 0; i < clearSprite.size(); i++){
        mvprintw(y + i, x, clearSprite[i].c_str());
    }
}