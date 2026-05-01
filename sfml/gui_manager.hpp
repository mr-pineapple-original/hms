
#include "menu_login.hpp"
#include "menu_patient.hpp"
#include "menu_doctor.hpp"
#include "menu_admin.hpp"

GuiManager::GuiManager() {
    window.create(sf::VideoMode(1024, 768), "MediCore Hospital Management System");
    currentScreen = new LoginMenu();
}

void GuiManager::run() {
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            currentScreen->handleEvent(window, event);
        }
        currentScreen->update();
        window.clear(sf::Color(245, 245, 250));
        currentScreen->draw(window);
        window.display();
    }
}
