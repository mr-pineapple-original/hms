#include "app.hpp"
#include "screens/loginscreen.hpp"
#include <memory>

void App::run()
{
    sf::RenderWindow window(sf::VideoMode({800, 600}), "HMS");

    std::unique_ptr<Screen> screen = std::make_unique<LoginScreen>();

    while (window.isOpen())
    {
        while (auto event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();

            screen->handle_event(window, *event);
        }

        if (screen->should_close)
            window.close();

        window.clear();
        screen->render(window);
        window.display();
    }
}
