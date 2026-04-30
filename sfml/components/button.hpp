#pragma once
#include "element.hpp"
#include "ui_manager.hpp"
#include <SFML/Graphics.hpp>
#include <functional>

class Button : public Element {
private:
    sf::RectangleShape box;
    sf::Text text;

    std::function<void()> on_click;
    bool is_hovered = false;

public:
    Button(const char* str, float width = 120.f, float height = 40.f)
        : text(UIManager::instance().get_font(), str, 20)
    {
        box.setSize({width, height});
        box.setFillColor(sf::Color(70, 70, 70));

        text.setFillColor(sf::Color::White);

        auto bounds = text.getLocalBounds();
        text.setOrigin({bounds.size.x / 2.f, bounds.size.y / 2.f});
    }

    void set_position(float x, float y) {
        position = {x, y};
        box.setPosition(position);

        auto size = box.getSize();
        text.setPosition({
            x + size.x / 2.f,
            y + size.y / 2.f
        });
    }

    void set_on_click(std::function<void()> fn) {
        on_click = std::move(fn);
    }

    void handle_event(const sf::Event& event, const sf::RenderWindow& window) {
        if (event.is<sf::Event::MouseButtonPressed>()) {
            if (event.getIf<sf::Event::MouseButtonPressed>()->button == sf::Mouse::Button::Left) {
                sf::Vector2i mouse = sf::Mouse::getPosition(window);
                sf::Vector2f mpos = window.mapPixelToCoords(mouse);

                if (box.getGlobalBounds().contains(mpos)) {
                    if (on_click) on_click();
                }
            }
        }
    }

    void render(sf::RenderWindow& window) override {
        if (!visible) return;

        window.draw(box);
        window.draw(text);
    }
};
