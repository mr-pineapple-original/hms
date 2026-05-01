#pragma once
#include <SFML/Graphics.hpp>

class ScreenBase {
public:
    virtual void handleEvent(sf::RenderWindow& window, sf::Event& event) = 0;
    virtual void update() = 0;
    virtual void draw(sf::RenderWindow& window) = 0;
    virtual ~ScreenBase() {}
};
