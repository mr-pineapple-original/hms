#pragma once
#include "screen.hpp"
#include "../components/label.hpp"
#include "../components/color_label.hpp"
#include "../components/button.hpp"
#include "../components/ui_manager.hpp"

// ── ViewDoctorsScreen ─────────────────────────────────────────────────────
// Loads and displays all doctors from doctors.txt.
// ─────────────────────────────────────────────────────────────────────────
class ViewDoctorsScreen : public Screen {
private:
    Label      heading;
    Label      divider;
    Label      col_header;
    Label      doctor_list;
    ColorLabel status_label;
    Button     back_btn;

    void load() {
        // TODO: FileHandler::get_all_doctors("doctors.txt", arr, count)
        // Build display: ID | Name | Specialization | Fee | Contact
        col_header.set_text("ID  | Name            | Specialization  | Fee (PKR) | Contact");
        doctor_list.set_text("-------------------------------------------------------------------\n"
                             "(doctor records will load from backend)");
    }

public:
    ViewDoctorsScreen()
        : heading("All Doctors"),
          divider("===================="),
          col_header(""),
          doctor_list(""),
          status_label(""),
          back_btn("Back", 100, 40)
    {
        heading.set_position    (50,  20);
        divider.set_position    (50,  48);
        col_header.set_position (50,  80);
        doctor_list.set_position(50, 108);
        status_label.set_position(50, 500);
        back_btn.set_position   (50, 540);

        load();

        back_btn.set_on_click([this]() {
            // TODO: UIManager::instance().set_screen(new AdminMenuScreen());
        });
    }

    void handle_event(sf::RenderWindow& window, const sf::Event& event) override {
        back_btn.handle_event(event, window);
    }

    void update() override {}

    void render(sf::RenderWindow& window) override {
        heading.render(window);
        divider.render(window);
        col_header.render(window);
        doctor_list.render(window);
        status_label.render(window);
        back_btn.render(window);
    }
};
