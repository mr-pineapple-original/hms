#include "loginscreen.hpp"
#include "logindialog.hpp"
#include <iostream>

LoginScreen::LoginScreen()
    : heading("Medicore (HMS)"),
      label("Login as: "),
      patient_btn("1. Patient"),
      doctor_btn("2. Doctor"),
      admin_btn("3. Admin"),
      exit_btn("4. Exit")
{
    heading.set_position(50, 50);
    label.set_position(100, 100);
    patient_btn.set_position(150, 150);
    doctor_btn.set_position(150, 200);
    admin_btn.set_position(150, 250);
    exit_btn.set_position(150, 300);

    patient_btn.set_on_click([]() {
        std::cout << "Loging as Patient: " << std::endl;
        UIManager::instance().set_screen(new LoginDialog(PATIENT));
    });
    doctor_btn.set_on_click([]() {
        std::cout << "Loging as Doctor: " << std::endl;
        UIManager::instance().set_screen(new LoginDialog(DOCTOR));
    });
    admin_btn.set_on_click([]() {
        std::cout << "Loging as Admin: " << std::endl;
        UIManager::instance().set_screen(new LoginDialog(ADMIN));
    });
    exit_btn.set_on_click([this]() {
        std::cout << "Exiting!" << std::endl;
        should_close = true;
    });
}

void LoginScreen::handle_event(sf::RenderWindow& window, const sf::Event& event) {
    patient_btn.handle_event(event, window);
    doctor_btn.handle_event(event, window);
    admin_btn.handle_event(event, window);
    exit_btn.handle_event(event, window);
}

void LoginScreen::update() {}
void LoginScreen::render(sf::RenderWindow& window) {
    label.render(window);
    heading.render(window);
    patient_btn.render(window);
    doctor_btn.render(window);
    admin_btn.render(window);
    exit_btn.render(window);
}
