#include "app.hpp"
#include "screens/loginscreen.hpp"
#include "screens/logindialog.hpp"
#include <memory>

void App::run()
{
    sf::RenderWindow window(sf::VideoMode({800, 600}), "HMS");

    UIManager::instance().set_screen(new LoginScreen());

    while (window.isOpen())
    {
        while (auto event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();

            UIManager::instance().handle_event(window, *event);
        }

        if (UIManager::instance().get_screen()->should_close)
            window.close();

        window.clear();
        UIManager::instance().render(window);
        window.display();
    }
}

