#pragma once
#include <SFML/Graphics.hpp>
#include "widget.hpp"

class Heading : public Widget {
    public:
        Heading();

        void set_text(const char* text);
        void set_position(float x, float y);
        void set_size(unsigned int size);

        void draw(sf::RenderWindow& window);

    private:
        sf::Text text;
        sf::Font font;

        const char* text_buffer;
};
