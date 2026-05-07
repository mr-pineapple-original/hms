#pragma once
#include "screen.hpp"
#include "../components/label.hpp"
#include "../components/color_label.hpp"
#include "../components/button.hpp"
#include "../components/text_field.hpp"
#include "../components/ui_manager.hpp"

// ── AddDoctorScreen ───────────────────────────────────────────────────────
// Admin enters doctor details; saved to doctors.txt via FileHandler.
// ─────────────────────────────────────────────────────────────────────────
class AddDoctorScreen : public Screen {
private:
    Label     heading;
    Label     divider;

    Label     name_label;       TextField name_field;
    Label     spec_label;       TextField spec_field;
    Label     fee_label;        TextField fee_field;
    Label     contact_label;    TextField contact_field;
    Label     pass_label;       TextField pass_field;

    Button      add_btn;
    Button      back_btn;
    ColorLabel  status_label;

public:
    AddDoctorScreen()
        : heading("Add Doctor"),
          divider("===================="),
          name_label("Name:"),
          spec_label("Specialization:"),
          fee_label("Consultation Fee (PKR):"),
          contact_label("Contact (11 digits):"),
          pass_label("Password (min 6):"),
          add_btn("Add Doctor", 160, 40),
          back_btn("Back", 100, 40),
          status_label("")
    {
        heading.set_position(50, 20);
        divider.set_position(50, 48);

        float lx = 50, fx = 280, y = 90, step = 60;
        name_label.set_position   (lx, y);  name_field.set_position   (fx, y - 8);  y += step;
        spec_label.set_position   (lx, y);  spec_field.set_position   (fx, y - 8);  y += step;
        fee_label.set_position    (lx, y);  fee_field.set_position    (fx, y - 8);  y += step;
        contact_label.set_position(lx, y);  contact_field.set_position(fx, y - 8);  y += step;
        pass_label.set_position   (lx, y);  pass_field.set_position   (fx, y - 8);  y += step;

        add_btn.set_position (160, y + 10);
        back_btn.set_position(340, y + 10);
        status_label.set_position(50, y + 70);

        add_btn.set_on_click([this]() {
            if (name_field.get_text().isEmpty()    || spec_field.get_text().isEmpty()    ||
                fee_field.get_text().isEmpty()     || contact_field.get_text().isEmpty() ||
                pass_field.get_text().isEmpty()) {
                status_label.set_color(sf::Color::Red);
                status_label.set_text("All fields are required.");
                return;
            }
            // TODO: validate contact == 11 digits, fee > 0, password >= 6 (Validator)
            // TODO: generate new doctor ID (max existing + 1 from doctors.txt)
            // TODO: FileHandler::append_doctor(name, spec, fee, contact, password, "doctors.txt")
            status_label.set_color(sf::Color::Green);
            status_label.set_text("Doctor added successfully. (stub)");
            name_field.clear(); spec_field.clear(); fee_field.clear();
            contact_field.clear(); pass_field.clear();
        });

        back_btn.set_on_click([this]() {
            // TODO: UIManager::instance().set_screen(new AdminMenuScreen());
        });
    }

    void handle_event(sf::RenderWindow& window, const sf::Event& event) override {
        name_field.handle_event   (event, window);
        spec_field.handle_event   (event, window);
        fee_field.handle_event    (event, window);
        contact_field.handle_event(event, window);
        pass_field.handle_event   (event, window);
        add_btn.handle_event      (event, window);
        back_btn.handle_event     (event, window);
    }

    void update() override {}

    void render(sf::RenderWindow& window) override {
        heading.render(window);
        divider.render(window);
        name_label.render(window);    name_field.render(window);
        spec_label.render(window);    spec_field.render(window);
        fee_label.render(window);     fee_field.render(window);
        contact_label.render(window); contact_field.render(window);
        pass_label.render(window);    pass_field.render(window);
        add_btn.render(window);
        back_btn.render(window);
        status_label.render(window);
    }
};
