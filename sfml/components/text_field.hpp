#pragma once
#include "element.hpp"
#include "ui_manager.hpp"
#include <SFML/Graphics.hpp>

class TextField : public Element
{
private:
    sf::RectangleShape box;
    sf::Text text;

    sf::String input;
    bool is_active = false;

public:
    TextField(float width = 250.f, float height = 40.f)
        : text(UIManager::instance().get_font(), "", 20)
    {
        box.setSize({ width, height });
        box.setFillColor(sf::Color(40, 40, 40));
        box.setOutlineThickness(2.f);
        box.setOutlineColor(sf::Color::White);

        text.setFillColor(sf::Color::White);
    }

    void set_position(float x, float y)
    {
        position = { x, y };

        box.setPosition(position);

        text.setPosition({
            x + 10.f,
            y + 5.f
        });
    }

    void handle_event(const sf::Event& event, const sf::RenderWindow& window)
    {
        // Mouse click → activate/deactivate field
        if (event.is<sf::Event::MouseButtonPressed>())
        {
            if (event.getIf<sf::Event::MouseButtonPressed>()->button == sf::Mouse::Button::Left)
            {
                sf::Vector2i mouse = sf::Mouse::getPosition(window);
                sf::Vector2f mpos = window.mapPixelToCoords(mouse);

                is_active = box.getGlobalBounds().contains(mpos);
            }
        }

        // Keyboard typing
        if (is_active && event.is<sf::Event::TextEntered>())
        {
            auto unicode = event.getIf<sf::Event::TextEntered>()->unicode;

            // Backspace
            if (unicode == '\b')
            {
                if (!input.isEmpty())
                {
                    input.erase(input.getSize() - 1, 1);
                }
            }
            // Printable characters only
            else if (unicode >= 32 && unicode < 127)
            {
                input += unicode;
            }

            text.setString(input);
        }
    }

    const sf::String& get_text() const
    {
        return input;
    }

    void clear()
    {
        input.clear();
        text.setString(input);
    }

    void render(sf::RenderWindow& window) override
    {
        if (!visible)
            return;

        if (is_active)
            box.setOutlineColor(sf::Color::Green);
        else
            box.setOutlineColor(sf::Color::White);

        window.draw(box);
        window.draw(text);
    }
};