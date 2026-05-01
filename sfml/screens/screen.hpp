#pragma once
#include <SFML/Graphics.hpp>

class Screen {
public:
    bool should_close = false;

    virtual ~Screen() = default;

    virtual void handle_event(sf::RenderWindow&, const sf::Event&) = 0;
    virtual void update() = 0;
    virtual void render(sf::RenderWindow&) = 0;
};
