#include "widget.hpp"
#include <stdexcept>

Widget::Widget()
{
    loaded = font.openFromFile("assets/fonts/jetbrains.ttf");

    if (!loaded)
    {
        throw std::runtime_error("failed to load font");
    }
}

sf::Font& Widget::get_font()
{
    return font;
}
