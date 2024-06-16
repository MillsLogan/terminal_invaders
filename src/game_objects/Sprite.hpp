#ifndef SPRITE_HPP
#define SPRITE_HPP

#include <vector>
#include <string>

class Sprite{
    // TODO possibly add some kind of color attribute/animations
    private:
        std::string color;
        std::vector<std::string> sprite;
        std::vector<std::string> clearSprite;
    public:
        Sprite(std::string color, std::vector<std::string> sprite);
        void draw(int x, int y);
        void clear(int x, int y);
};



#endif