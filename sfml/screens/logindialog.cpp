#include "logindialog.hpp"
#include "loginscreen.hpp"
#include "../../src/file_handler.hpp"
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
    failed_attempts = 0;

    heading.set_position(100, 50);
    id_label.set_position(100, 130);
    password_label.set_position(100, 200);
    id_field.set_position(220, 120);
    password_field.set_position(220, 190);
    login_btn.set_position(150, 280);
    back_btn.set_position(300, 280);

login_btn.set_on_click([this]() {
    std::cout << "Login attempt\n";

    // Convert sf::String to raw char arrays
    sf::String id_input = id_field.get_text();
    sf::String pw_input = password_field.get_text();

    char id_buffer[128];
    char pw_buffer[128];

    std::size_t id_len = std::min(id_input.getSize(), sizeof(id_buffer) - 1);
    std::size_t pw_len = std::min(pw_input.getSize(), sizeof(pw_buffer) - 1);

    for (std::size_t i = 0; i < id_len; ++i) id_buffer[i] = static_cast<char>(id_input[i]);
    id_buffer[id_len] = '\0';

    for (std::size_t i = 0; i < pw_len; ++i) pw_buffer[i] = static_cast<char>(pw_input[i]);
    pw_buffer[pw_len] = '\0';

    bool success = false;

    // Call the right validator depending on role
    if (role == PATIENT) {
        success = FileHandler::validate_patient(id_buffer, pw_buffer, "patients.txt");
    } else if (role == DOCTOR) {
        success = FileHandler::validate_doctor(id_buffer, pw_buffer, "doctors.txt");
    } else if (role == ADMIN) {
        success = FileHandler::validate_admin(id_buffer, pw_buffer, "admins.txt");
    }

    if (success) {
        std::cout << "Login successful!\n";
        // TODO: move to next screen
    } else {
        failed_attempts++;
        std::cout << "Login failed. Attempt " << failed_attempts << "/3\n";

        if (failed_attempts >= 3) {
            std::cout << "Account locked. Contact admin.\n";
            std::ofstream log("security_log.txt", std::ios::app);
            log << "Locked account for role " << role << " with ID " << id_buffer << "\n";
            log.close();
            should_close = true;
        }
    }
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
