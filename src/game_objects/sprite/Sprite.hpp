#ifndef SPRITE_HPP
#define SPRITE_HPP

#include <vector>
#include <string>
#include <ncurses.h>

class Sprite{
    // TODO possibly add some kind of color attribute/animations
    private:
        WINDOW *windowReference;
        int color;
        std::vector<std::string> sprite;
        std::vector<std::string> clearSprite;
        std::vector<std::string> initClearSprite();
    public:
        Sprite(WINDOW *windowReference, int color, std::vector<std::string> sprite);
        void draw(int x, int y);
        void clear(int x, int y);
        int getWidth();
        int getHeight();
};



#endif