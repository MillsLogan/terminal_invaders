#include "Sprite.hpp"
#include <ncurses.h>


Sprite::Sprite(WINDOW *windowReference, std::string color, std::vector<std::string> sprite){
    this->windowReference = windowReference;
    this->color = color;
    this->sprite = sprite;
    this->clearSprite = initClearSprite();
}

std::vector<std::string> Sprite::initClearSprite(){
    std::vector<std::string> clearSprite;
    for(int i = 0; i < sprite.size(); i++){
        clearSprite.push_back("");

        for(int j = 0; j < sprite[i].size(); j++){
            clearSprite[i] += " ";
        }
    }

    return clearSprite;
}

void Sprite::draw(int x, int y){
    wattron(windowReference, COLOR_PAIR(1));
    for(int i = 0; i < sprite.size(); i++){
        mvwprintw(windowReference, y + i, x, sprite[i].c_str());
    }
    wattroff(windowReference, COLOR_PAIR(1));
}

void Sprite::clear(int x, int y){
    for(int i = 0; i < clearSprite.size(); i++){
        mvwprintw(windowReference, y + i, x, clearSprite[i].c_str());
    }
}