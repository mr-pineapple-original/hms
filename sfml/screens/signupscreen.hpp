#pragma once
#include "screen.hpp"
#include "../components/label.hpp"
#include "../components/color_label.hpp"
#include "../components/button.hpp"
#include "../components/text_field.hpp"
#include "../components/ui_manager.hpp"

// ── SignupScreen ──────────────────────────────────────────────────────────
// Patient self-registration.
// TODO: connect FileHandler::append_patient() and Validator when ready.
// ─────────────────────────────────────────────────────────────────────────
class SignupScreen : public Screen {
private:
    Label      heading;
    Label      divider;

    Label      name_label;       TextField name_field;
    Label      age_label;        TextField age_field;
    Label      gender_label;     TextField gender_field;    // M or F
    Label      contact_label;    TextField contact_field;   // 11 digits
    Label      pass_label;       TextField pass_field;      // min 6 chars

    Button     signup_btn;
    Button     back_btn;
    ColorLabel status_label;

public:
    SignupScreen()
        : heading("Patient Signup"),
          divider("===================="),
          name_label("Name:"),
          age_label("Age:"),
          gender_label("Gender (M/F):"),
          contact_label("Contact (11 digits):"),
          pass_label("Password (min 6):"),
          signup_btn("Create Account", 180, 40),
          back_btn("Back", 100, 40),
          status_label("")
    {
        heading.set_position(50, 20);
        divider.set_position(50, 48);

        float lx = 50, fx = 280, y = 90, step = 60;
        name_label.set_position   (lx, y);  name_field.set_position   (fx, y - 8);  y += step;
        age_label.set_position    (lx, y);  age_field.set_position    (fx, y - 8);  y += step;
        gender_label.set_position (lx, y);  gender_field.set_position (fx, y - 8);  y += step;
        contact_label.set_position(lx, y);  contact_field.set_position(fx, y - 8);  y += step;
        pass_label.set_position   (lx, y);  pass_field.set_position   (fx, y - 8);  y += step;

        signup_btn.set_position(160, y + 10);
        back_btn.set_position  (360, y + 10);
        status_label.set_position(50, y + 70);

        signup_btn.set_on_click([this]() {
            if (name_field.get_text().isEmpty()    || age_field.get_text().isEmpty()    ||
                gender_field.get_text().isEmpty()  || contact_field.get_text().isEmpty() ||
                pass_field.get_text().isEmpty()) {
                status_label.set_color(sf::Color::Red);
                status_label.set_text("All fields are required.");
                return;
            }
            // TODO: Validator::validate_contact(contact_buf)  → 11 digits
            // TODO: Validator::validate_password(pass_buf)    → min 6 chars
            // TODO: Validator::validate_age(age_buf)          → positive int
            // TODO: Validator::validate_gender(gender_buf)    → 'M' or 'F'
            // TODO: generate new patient ID (read max ID from patients.txt, +1)
            // TODO: FileHandler::append_patient(id, name, age, gender, contact, password,
            //                                   balance=0, "patients.txt")
            status_label.set_color(sf::Color::Green);
            status_label.set_text("Account created successfully! Please login. (stub)");
            name_field.clear(); age_field.clear(); gender_field.clear();
            contact_field.clear(); pass_field.clear();
        });

        back_btn.set_on_click([this]() {
            UIManager::instance().set_screen(new LoginDialog(PATIENT));
        });
    }

    void handle_event(sf::RenderWindow& window, const sf::Event& event) override {
        name_field.handle_event   (event, window);
        age_field.handle_event    (event, window);
        gender_field.handle_event (event, window);
        contact_field.handle_event(event, window);
        pass_field.handle_event   (event, window);
        signup_btn.handle_event   (event, window);
        back_btn.handle_event     (event, window);
    }

    void update() override {}

    void render(sf::RenderWindow& window) override {
        heading.render(window);
        divider.render(window);
        name_label.render(window);    name_field.render(window);
        age_label.render(window);     age_field.render(window);
        gender_label.render(window);  gender_field.render(window);
        contact_label.render(window); contact_field.render(window);
        pass_label.render(window);    pass_field.render(window);
        signup_btn.render(window);
        back_btn.render(window);
        status_label.render(window);
    }
};

