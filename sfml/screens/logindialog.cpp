#include "logindialog.hpp"
#include "loginscreen.hpp"
#include <iostream>

LoginDialog::LoginDialog(UserRole user_role)
    : role(user_role),
      heading("Login"),
      id_label("ID:"),
      password_label("Password:"),
      login_btn("Login"),
      back_btn("Back")
{
    if (role == PATIENT) heading = Label("Patient Login");
    else if (role == DOCTOR) heading = Label("Doctor Login");
    else heading = Label("Admin Login");

    heading.set_position(100, 50);
    id_label.set_position(100, 130);
    password_label.set_position(100, 200);
    id_field.set_position(220, 120);
    password_field.set_position(220, 190);
    login_btn.set_position(150, 280);
    back_btn.set_position(300, 280);

    login_btn.set_on_click([this]() {
        std::cout << "Login attempt\n";
        std::cout << "ID: " << id_field.get_text().toAnsiString() << "\n";
        std::cout << "Password: " << password_field.get_text().toAnsiString() << "\n";
    });

    back_btn.set_on_click([this]() {
        UIManager::instance().set_screen(new LoginScreen());
    });
}

void LoginDialog::handle_event(sf::RenderWindow& window, const sf::Event& event) {
    id_field.handle_event(event, window);
    password_field.handle_event(event, window);
    login_btn.handle_event(event, window);
    back_btn.handle_event(event, window);
}

void LoginDialog::update() {}
void LoginDialog::render(sf::RenderWindow& window) {
    heading.render(window);
    id_label.render(window);
    password_label.render(window);
    id_field.render(window);
    password_field.render(window);
    login_btn.render(window);
    back_btn.render(window);
}
