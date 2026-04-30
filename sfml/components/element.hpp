#pragma once
#include <SFML/Graphics.hpp>

class Element {
public:
    sf::Vector2f position;
    bool visible = true;

    virtual ~Element() = default;

    virtual void update(float dt) {}
    virtual void render(sf::RenderWindow& window) = 0;
};
