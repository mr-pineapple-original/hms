#pragma once
#include "element.hpp"
#include "ui_manager.hpp"
#include <SFML/Graphics.hpp>

class Label : public Element {
private:
    sf::Text text;

public:
    Label(const char* str, unsigned int size = 20)
        : text(UIManager::instance().get_font(), str, size)
    {
        text.setFillColor(sf::Color::White);
    }

    void set_text(const std::string& str) {
        text.setString(str);
    }

    void set_position(float x, float y) {
        position = {x, y};
        text.setPosition(position);
    }

    void render(sf::RenderWindow& window) override {
        if (!visible) return;
        window.draw(text);
    }
};
