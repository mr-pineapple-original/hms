#pragma once
#include <SFML/Graphics.hpp>
#include <stdexcept>

class UIManager {
private:
    sf::Font font;

    UIManager() {
        if (!font.openFromFile("assets/fonts/jetbrains.ttf")) {
            throw std::runtime_error("Failed to load font");
        }
    }

public:
    UIManager(const UIManager&) = delete;
    UIManager& operator=(const UIManager&) = delete;

    static UIManager& instance() {
        static UIManager instance;
        return instance;
    }

    const sf::Font& get_font() const {
        return font;
    }
};
