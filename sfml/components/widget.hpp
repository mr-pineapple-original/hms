#pragma once
#include <SFML/Graphics.hpp>

class Widget {
    public:
        Widget();

    protected:
        sf::Font& get_font();

    private:
        sf::Font font;
        bool loaded;
};
