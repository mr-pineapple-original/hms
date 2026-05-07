#include "logindialog.hpp"
#include "loginscreen.hpp"
// #include "../../src/file_handler.hpp"   // Uncomment when backend is ready
#include <iostream>
#include <fstream>

LoginDialog::LoginDialog(UserRole user_role)
    : role(user_role),
      heading("Login"),
      id_label("ID:"),
      password_label("Password:"),
      error_label(""),
      attempts_label(""),
      login_btn("Login"),
      back_btn("Back")
{
    // Set heading based on role
    if (role == PATIENT)      heading = Label("Patient Login");
    else if (role == DOCTOR)  heading = Label("Doctor Login");
    else                      heading = Label("Admin Login");

    // Layout — centered in an 800x600 window
    heading.set_position(275, 80);
    id_label.set_position(170, 195);
    password_label.set_position(170, 265);
    id_field.set_position(270, 185);
    password_field.set_position(270, 255);
    login_btn.set_position(220, 340);
    back_btn.set_position(360, 340);
    error_label.set_position(190, 400);    // red error text below buttons
    attempts_label.set_position(190, 430); // attempt counter

    // ── Login button handler ──────────────────────────────────────────────
    login_btn.set_on_click([this]() {
        if (locked) return;

        sf::String id_input = id_field.get_text();
        sf::String pw_input = password_field.get_text();

        // Convert sf::String → char buffer
        char id_buf[128], pw_buf[128];
        std::size_t id_len = std::min(id_input.getSize(), sizeof(id_buf) - 1);
        std::size_t pw_len = std::min(pw_input.getSize(), sizeof(pw_buf) - 1);
        for (std::size_t i = 0; i < id_len; ++i) id_buf[i] = static_cast<char>(id_input[i]);
        id_buf[id_len] = '\0';
        for (std::size_t i = 0; i < pw_len; ++i) pw_buf[i] = static_cast<char>(pw_input[i]);
        pw_buf[pw_len] = '\0';

        // ── Validation (stub — replace with real FileHandler calls) ────────
        bool success = false;
        // TODO: uncomment once FileHandler is ready
        // if      (role == PATIENT) success = FileHandler::validate_patient(id_buf, pw_buf, "patients.txt");
        // else if (role == DOCTOR)  success = FileHandler::validate_doctor (id_buf, pw_buf, "doctors.txt");
        // else                      success = FileHandler::validate_admin  (id_buf, pw_buf, "admin.txt");

        // Temporary stub so UI flow can be tested without backend
        success = (id_buf[0] != '\0' && pw_buf[0] != '\0'); // any non-empty input passes

        if (success) {
            error_label.set_text("Login successful!");
            attempts_label.set_text("");
            // TODO: navigate to the correct menu screen, e.g.:
            // if (role == PATIENT) UIManager::instance().set_screen(new PatientMenuScreen(id_buf));
            // else if (role == DOCTOR) UIManager::instance().set_screen(new DoctorMenuScreen(id_buf));
            // else UIManager::instance().set_screen(new AdminMenuScreen());
        } else {
            failed_attempts++;
            char attempt_msg[64];
            // Build "Attempt X/3" string manually (no std::string)
            attempt_msg[0] = 'A'; attempt_msg[1] = 't'; attempt_msg[2] = 't';
            attempt_msg[3] = 'e'; attempt_msg[4] = 'm'; attempt_msg[5] = 'p';
            attempt_msg[6] = 't'; attempt_msg[7] = ' ';
            attempt_msg[8] = '0' + static_cast<char>(failed_attempts);
            attempt_msg[9] = '/'; attempt_msg[10] = '3'; attempt_msg[11] = '\0';
            attempts_label.set_text(attempt_msg);

            if (failed_attempts >= 3) {
                locked = true;
                error_label.set_text("Account locked. Contact admin.");
                attempts_label.set_text("");

                // Log to security_log.txt
                std::ofstream log("security_log.txt", std::ios::app);
                if (log.is_open()) {
                    log << "LOCKED,role=" << role << ",id=" << id_buf << "\n";
                    log.close();
                }
                should_close = false; // keep window open so message is visible
            } else {
                error_label.set_text("Invalid ID or password.");
            }
        }
    });

    // ── Back button handler ───────────────────────────────────────────────
    back_btn.set_on_click([this]() {
        UIManager::instance().set_screen(new LoginScreen());
    });
}

void LoginDialog::handle_event(sf::RenderWindow& window, const sf::Event& event) {
    if (locked) {
        // Only allow Back when locked
        back_btn.handle_event(event, window);
        return;
    }
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

    if (!locked) {
        login_btn.render(window);
    }
    back_btn.render(window);

    error_label.render(window);
    attempts_label.render(window);
}
