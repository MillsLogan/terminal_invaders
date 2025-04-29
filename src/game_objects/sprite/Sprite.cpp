#include "Sprite.hpp"
#include <ncurses.h>
#include <string>


Sprite::Sprite(WINDOW *windowReference, int color, std::vector<std::string> sprite){
    this->windowReference = windowReference;
    this->color = color;
    this->sprite = sprite;
    this->clearSprite = initClearSprite();
}

std::vector<std::string> Sprite::initClearSprite(){
    std::vector<std::string> clearSprite;
    for(unsigned long i = 0; i < sprite.size(); i++){
        clearSprite.push_back("");

        for(unsigned long j = 0; j < sprite[i].size(); j++){
            clearSprite[i] += " ";
        }
    }

    return clearSprite;
}

void Sprite::draw(int x, int y){
    wattron(windowReference, COLOR_PAIR(color));
    for(unsigned long i = 0; i < sprite.size(); i++){
        mvwprintw(windowReference, y + i, x, sprite[i].c_str());
    }
    wattroff(windowReference, COLOR_PAIR(color));
}

void Sprite::clear(int x, int y){
    for(unsigned long i = 0; i < clearSprite.size(); i++){
        mvwprintw(windowReference, y + i, x, clearSprite[i].c_str());
    }
}

int Sprite::getWidth(){
    return sprite[0].size();
}

int Sprite::getHeight(){
    return sprite.size();
}