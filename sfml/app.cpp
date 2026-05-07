#include "app.hpp"
#include "screens/loginscreen.hpp"
#include "screens/logindialog.hpp"
#include "screens/patientmenuscreen.hpp"
#include "screens/doctormenuscreen.hpp"
#include "screens/adminmenuscreen.hpp"
#include "components/ui_manager.hpp"
#include "../src/hospital_system.hpp"


// void App::run()
// {
//     sf::RenderWindow window(sf::VideoMode({800, 600}), "MediCore HMS");

//     // Start at the role-selection login screen
//     UIManager::instance().set_screen(new LoginScreen());

//     while (window.isOpen())
//     {
//         while (auto event = window.pollEvent())
//         {
//             if (event->is<sf::Event::Closed>())
//                 window.close();

//             UIManager::instance().handle_event(window, *event);
//         }

//         // The LoginScreen sets should_close when Exit is chosen
//         Screen* current = UIManager::instance().get_screen();
//         if (current && current->should_close)
//             window.close();

//         window.clear(sf::Color(30, 30, 30));  // dark background
//         UIManager::instance().render(window);
//         window.display();
//     }
// }


void App::run()
{
    sf::RenderWindow window(sf::VideoMode({800, 600}), "MediCore HMS");

    // Load all data once at startup
    HospitalSystem::instance().load_data();

    UIManager::instance().set_screen(new LoginScreen());

    while (window.isOpen())
    {
        while (auto event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();

            UIManager::instance().handle_event(window, *event);
        }

        Screen* current = UIManager::instance().get_screen();
        if (current && current->should_close)
            window.close();

        window.clear(sf::Color(30, 30, 30));
        UIManager::instance().render(window);
        window.display();
    }

    // Save everything cleanly on exit
    HospitalSystem::instance().save_data();
}