#pragma once
#include "screen.hpp"
#include "logindialog.hpp"
#include "../components/label.hpp"
#include "../components/color_label.hpp"
#include "../components/button.hpp"
#include "../components/text_field.hpp"
#include "../components/ui_manager.hpp"
#include "../components/sf_string_utils.hpp"
#include "../../src/hospital_system.hpp"
#include "../../src/file_handler.hpp"
#include "../../src/char_array_functions.hpp"
#include "../components/userrole.hpp"

class AdminSignupScreen : public Screen {
private:
    Label      heading;
    Label      divider;

    Label      name_label;   TextField  name_field;
    Label      pass_label;   TextField  pass_field;

    Button     signup_btn;
    Button     back_btn;
    ColorLabel status_label;

public:
    AdminSignupScreen()
        : heading("Admin Signup"),
          divider("===================="),
          name_label("Name:"),
          pass_label("Password:"),
          signup_btn("Create Account", 180, 40),
          back_btn("Back", 100, 40),
          status_label("")
    {
        heading.set_position(50, 20);
        divider.set_position(50, 48);

        float lx = 50, fx = 280, y = 120, step = 70;
        name_label.set_position(lx, y);  name_field.set_position(fx, y - 8);  y += step;
        pass_label.set_position(lx, y);  pass_field.set_position(fx, y - 8);  y += step;

        signup_btn.set_position  (160, y + 10);
        back_btn.set_position    (360, y + 10);
        status_label.set_position(50,  y + 70);

        signup_btn.set_on_click([this]() {

            if (name_field.get_text().isEmpty() || pass_field.get_text().isEmpty())
            {
                status_label.set_color(sf::Color::Red);
                status_label.set_text("All fields are required.");
                return;
            }

            char name_buf[64];
            char pass_buf[64];

            sf_string_to_char(name_field.get_text(), name_buf, sizeof(name_buf));
            sf_string_to_char(pass_field.get_text(), pass_buf, sizeof(pass_buf));

            int new_id = FileHandler::generate_new_id(
                             HospitalSystem::instance().get_admins());

            Admin new_admin(new_id, pass_buf, name_buf);

            HospitalSystem::instance().get_admins().add(new_admin);
            FileHandler::append_admin(new_admin, "admin.txt");

            char success_msg[80];
            const char* prefix = "Admin account created! Your ID is: ";
            int pos = 0;
            for (int i = 0; prefix[i] != '\0'; i++)
                success_msg[pos++] = prefix[i];
            char id_buf[16];
            int_to_char(new_id, id_buf);
            for (int i = 0; id_buf[i] != '\0'; i++)
                success_msg[pos++] = id_buf[i];
            success_msg[pos] = '\0';

            status_label.set_color(sf::Color::Green);
            status_label.set_text(success_msg);

            name_field.clear();
            pass_field.clear();
        });

        back_btn.set_on_click([this]() {
            UIManager::instance().set_screen(new LoginDialog(ADMIN));
        });
    }

    void handle_event(sf::RenderWindow& window, const sf::Event& event) override {
        name_field.handle_event(event, window);
        pass_field.handle_event(event, window);
        signup_btn.handle_event(event, window);
        back_btn.handle_event  (event, window);
    }

    void update() override {}

    void render(sf::RenderWindow& window) override {
        heading.render(window);
        divider.render(window);
        name_label.render(window);  name_field.render(window);
        pass_label.render(window);  pass_field.render(window);
        signup_btn.render(window);
        back_btn.render(window);
        status_label.render(window);
    }
};