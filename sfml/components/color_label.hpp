// #pragma once
// #include "element.hpp"
// #include "ui_manager.hpp"
// #include <SFML/Graphics.hpp>
// #include "label.hpp"

// // ── ColorLabel ────────────────────────────────────────────────────────────
// // A Label that exposes set_color() so you can show errors in red,
// // success messages in green, etc.
// //
// // Usage:
// //   ColorLabel err("", 18);
// //   err.set_color(sf::Color::Red);
// //   err.set_text("Invalid ID or password.");
// // ─────────────────────────────────────────────────────────────────────────

// class ColorLabel : public Element {
// private:
//     sf::Text text;

// public:
//     ColorLabel(const char* str = "", unsigned int size = 18)
//         : text(UIManager::instance().get_font(), str, size)
//     {
//         text.setFillColor(sf::Color::White);
//     }

//     void set_text(const std::string& str) {
//         text.setString(str);
//     }

//     void set_color(sf::Color color) {
//         text.setFillColor(color);
//     }

//     void set_position(float x, float y) {
//         position = {x, y};
//         text.setPosition(position);
//     }

//     void render(sf::RenderWindow& window) override {
//         if (!visible) return;
//         window.draw(text);
//     }
// };

#pragma once
#include "element.hpp"
#include "ui_manager.hpp"
#include <SFML/Graphics.hpp>

class ColorLabel : public Element {
private:
    sf::Text text;

public:
    ColorLabel(const char* str = "", unsigned int size = 18)
        : text(UIManager::instance().get_font(), str, size)
    {
        text.setFillColor(sf::Color::White);
    }

    void set_text(const std::string& str) {
        text.setString(str);
    }

    void set_color(sf::Color color) {
        text.setFillColor(color);
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