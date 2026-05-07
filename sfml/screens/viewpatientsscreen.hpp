#pragma once
#include "screen.hpp"
#include "../components/label.hpp"
#include "../components/color_label.hpp"
#include "../components/button.hpp"
#include "../components/ui_manager.hpp"

// ── ViewPatientsScreen ────────────────────────────────────────────────────
// Loads and displays all patients from patients.txt.
// ─────────────────────────────────────────────────────────────────────────
class ViewPatientsScreen : public Screen {
private:
    Label      heading;
    Label      divider;
    Label      col_header;
    Label      patient_list;
    ColorLabel status_label;
    Button     back_btn;

    void load() {
        // TODO: FileHandler::get_all_patients("patients.txt", arr, count)
        // Build display: ID | Name | Age | Gender | Contact | Balance
        col_header.set_text("ID  | Name            | Age | Gender | Contact     | Balance (PKR)");
        patient_list.set_text("--------------------------------------------------------------------\n"
                              "(patient records will load from backend)");
    }

public:
    ViewPatientsScreen()
        : heading("All Patients"),
          divider("===================="),
          col_header(""),
          patient_list(""),
          status_label(""),
          back_btn("Back", 100, 40)
    {
        heading.set_position     (50,  20);
        divider.set_position     (50,  48);
        col_header.set_position  (50,  80);
        patient_list.set_position(50, 108);
        status_label.set_position(50, 500);
        back_btn.set_position    (50, 540);

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
        patient_list.render(window);
        status_label.render(window);
        back_btn.render(window);
    }
};
