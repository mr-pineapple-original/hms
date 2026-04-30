#include <SFML/Graphics.hpp>
#include "app.hpp"
#include "components/heading.cpp"

void App::run()
{
    
    sf::RenderWindow window(sf::VideoMode({800, 600}), "HMS");

    while (window.isOpen())
    {
        while (auto event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
        }

        window.clear();
        window.display();
    }
}
