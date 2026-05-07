#pragma once
#include "screen.hpp"
#include "../components/label.hpp"
#include "../components/color_label.hpp"
#include "../components/button.hpp"
#include "../components/text_field.hpp"
#include "../components/ui_manager.hpp"

// ── DischargePatientScreen ────────────────────────────────────────────────
// Admin enters a Patient ID to discharge (mark as discharged in patients.txt).
// Cannot discharge if patient has any unpaid bills or pending appointments.
// ─────────────────────────────────────────────────────────────────────────
class DischargePatientScreen : public Screen {
private:
    Label      heading;
    Label      divider;
    Label      info_label;      // shows patient summary after lookup
    Label      patient_id_label;
    TextField  patient_id_field;
    Button     lookup_btn;
    Button     discharge_btn;
    Button     back_btn;
    ColorLabel status_label;

public:
    DischargePatientScreen()
        : heading("Discharge Patient"),
          divider("===================="),
          info_label(""),
          patient_id_label("Patient ID:"),
          lookup_btn("Look Up", 110, 40),
          discharge_btn("Discharge", 130, 40),
          back_btn("Back", 100, 40),
          status_label("")
    {
        heading.set_position        (50,  20);
        divider.set_position        (50,  48);
        patient_id_label.set_position(50, 110);
        patient_id_field.set_position(200, 100);
        lookup_btn.set_position     (470, 100);
        info_label.set_position     (50,  160);
        discharge_btn.set_position  (180, 320);
        back_btn.set_position       (330, 320);
        status_label.set_position   (50,  390);

        lookup_btn.set_on_click([this]() {
            if (patient_id_field.get_text().isEmpty()) {
                status_label.set_color(sf::Color::Red);
                status_label.set_text("Please enter a Patient ID.");
                return;
            }
            // TODO: FileHandler::find_patient(id, "patients.txt") → throw if not found
            // TODO: show Name, Balance, pending appointments count, unpaid bills count
            // Stub:
            info_label.set_text("Name:    [Patient Name]         (stub)\n"
                                "Balance: PKR ----\n"
                                "Pending Appointments: --\n"
                                "Unpaid Bills:         --");
            status_label.set_color(sf::Color::White);
            status_label.set_text("Patient found. Review details before discharging.");
        });

        discharge_btn.set_on_click([this]() {
            if (patient_id_field.get_text().isEmpty()) {
                status_label.set_color(sf::Color::Red);
                status_label.set_text("Please look up a patient first.");
                return;
            }
            // TODO: re-validate patient exists
            // TODO: if any bill status == "unpaid"     → throw (cannot discharge)
            // TODO: if any appointment status == "pending" → throw (cannot discharge)
            // TODO: FileHandler::set_patient_discharged(id, "patients.txt")
            status_label.set_color(sf::Color::Green);
            status_label.set_text("Patient discharged successfully. (stub)");
            patient_id_field.clear();
            info_label.set_text("");
        });

        back_btn.set_on_click([this]() {
            // TODO: UIManager::instance().set_screen(new AdminMenuScreen());
        });
    }

    void handle_event(sf::RenderWindow& window, const sf::Event& event) override {
        patient_id_field.handle_event(event, window);
        lookup_btn.handle_event      (event, window);
        discharge_btn.handle_event   (event, window);
        back_btn.handle_event        (event, window);
    }

    void update() override {}

    void render(sf::RenderWindow& window) override {
        heading.render(window);
        divider.render(window);
        patient_id_label.render(window);
        patient_id_field.render(window);
        lookup_btn.render(window);
        info_label.render(window);
        discharge_btn.render(window);
        back_btn.render(window);
        status_label.render(window);
    }
};
