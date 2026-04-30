#include "heading.hpp"

Heading::Heading()
    : text(get_font(), "", 32)
{
    text.setFillColor(sf::Color::White);
}

void Heading::set_text(const char* t)
{
    text.setString(t);
}

void Heading::set_position(float x, float y)
{
    text.setPosition({x, y});
}

void Heading::set_size(unsigned int s)
{
    text.setCharacterSize(s);
}

void Heading::draw(sf::RenderWindow& window)
{
    window.draw(text);
}
