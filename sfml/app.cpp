#include <SFML/Graphics.hpp>
#include "app.hpp"
#include "components/label.hpp"
#include "components/button.hpp"
#include <iostream>

void App::run()
{
    sf::RenderWindow window(sf::VideoMode({800, 600}), "HMS");

    Label label("Hello");
    label.set_position(100, 100);

    Button btn("Click Me");
    btn.set_position(200, 200);

    btn.set_on_click([]() {
        std::cout << "Button clicked\n";
    });

    while (window.isOpen())
    {
        while (auto event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();

            btn.handle_event(*event, window); // REQUIRED
        }

        window.clear();

        label.render(window);
        btn.render(window);

        window.display();
    }
}
