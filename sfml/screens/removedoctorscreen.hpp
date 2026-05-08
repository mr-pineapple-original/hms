// #pragma once
// #include "screen.hpp"
// #include "../components/label.hpp"
// #include "../components/color_label.hpp"
// #include "../components/button.hpp"
// #include "../components/text_field.hpp"
// #include "../components/ui_manager.hpp"

// // ── RemoveDoctorScreen ────────────────────────────────────────────────────
// // Admin enters a Doctor ID to remove. Cannot remove if doctor has any
// // pending (future) appointments.
// // ─────────────────────────────────────────────────────────────────────────
// class RemoveDoctorScreen : public Screen
// {
// private:
//     Label heading;
//     Label divider;
//     Label doc_id_label;
//     TextField doc_id_field;
//     Button remove_btn;
//     Button back_btn;
//     ColorLabel status_label;

// public:
//     RemoveDoctorScreen()
//         : heading("Remove Doctor"),
//           divider("===================="),
//           doc_id_label("Doctor ID:"),
//           remove_btn("Remove Doctor", 160, 40),
//           back_btn("Back", 100, 40),
//           status_label("")
//     {
//         heading.set_position(50, 20);
//         divider.set_position(50, 48);
//         doc_id_label.set_position(50, 110);
//         doc_id_field.set_position(200, 100);
//         remove_btn.set_position(160, 170);
//         back_btn.set_position(340, 170);
//         status_label.set_position(50, 240);

//         remove_btn.set_on_click([this]()
//                                 {
//             if (doc_id_field.get_text().isEmpty()) {
//                 status_label.set_color(sf::Color::Red);
//                 status_label.set_text("Please enter a Doctor ID.");
//                 return;
//             }
//             // TODO: FileHandler::find_doctor(id, "doctors.txt") → throw if not found
//             // TODO: Check appointments.txt — if any appointment for this doctor
//             //       has status == "pending" → throw (cannot remove active doctor)
//             // TODO: FileHandler::remove_doctor(id, "doctors.txt")
//             status_label.set_color(sf::Color::Green);
//             status_label.set_text("Doctor removed successfully. (stub)");
//             doc_id_field.clear(); });

//         back_btn.set_on_click([this]()
//                               { go_back(); });
//     }

//     void handle_event(sf::RenderWindow &window, const sf::Event &event) override
//     {
//         doc_id_field.handle_event(event, window);
//         remove_btn.handle_event(event, window);
//         back_btn.handle_event(event, window);
//     }

//     void update() override {}

//     void render(sf::RenderWindow &window) override
//     {
//         heading.render(window);
//         divider.render(window);
//         doc_id_label.render(window);
//         doc_id_field.render(window);
//         remove_btn.render(window);
//         back_btn.render(window);
//         status_label.render(window);
//     }
//     void go_back();
// };



#pragma once
#include "screen.hpp"
#include "../components/label.hpp"
#include "../components/color_label.hpp"
#include "../components/button.hpp"
#include "../components/text_field.hpp"
#include "../components/ui_manager.hpp"
#include "../../src/hospital_system.hpp"
#include "../../src/file_handler.hpp"
#include "../components/sf_string_utils.hpp"

class RemoveDoctorScreen : public Screen {
private:
    Label heading, divider, doc_id_label;
    TextField doc_id_field;
    Button remove_btn, back_btn;
    ColorLabel status_label;

    static bool str_eq(const char* a, const char* b) {
        int i = 0;
        while (a[i] && b[i]) { if (a[i] != b[i]) return false; i++; }
        return a[i] == '\0' && b[i] == '\0';
    }

public:
    RemoveDoctorScreen()
        : heading("Remove Doctor"), divider("===================="),
          doc_id_label("Doctor ID:"),
          remove_btn("Remove Doctor", 160, 40), back_btn("Back", 100, 40),
          status_label("")
    {
        heading.set_position(50, 20);
        divider.set_position(50, 48);
        doc_id_label.set_position(50, 110);
        doc_id_field.set_position(200, 100);
        remove_btn.set_position(160, 170);
        back_btn.set_position(340, 170);
        status_label.set_position(50, 240);

        remove_btn.set_on_click([this]() {
            if (doc_id_field.get_text().isEmpty()) {
                status_label.set_color(sf::Color::Red);
                status_label.set_text("Please enter a Doctor ID.");
                return;
            }

            char id_buf[32];
            sf_string_to_char(doc_id_field.get_text(), id_buf, sizeof(id_buf));
            int doc_id = 0;
            for (int i = 0; id_buf[i]; i++) doc_id = doc_id * 10 + (id_buf[i] - '0');

            Doctor* ptr_d = HospitalSystem::instance().get_doctors().find(doc_id);
            if (ptr_d == nullptr) {
                status_label.set_color(sf::Color::Red);
                status_label.set_text("Doctor not found.");
                return;
            }

            Appointment* ptr_appts = HospitalSystem::instance().get_appointments().get_data();
            int total = HospitalSystem::instance().get_appointments().size();
            for (int i = 0; i < total; i++) {
                if ((ptr_appts + i)->get_doctor_id() == doc_id &&
                    str_eq((const char*)(ptr_appts + i)->get_status(), "pending")) {
                    status_label.set_color(sf::Color::Red);
                    status_label.set_text("Cannot remove: doctor has pending appointments.");
                    return;
                }
            }

            HospitalSystem::instance().get_doctors().remove(doc_id);
            FileHandler::update_doctors(HospitalSystem::instance().get_doctors(), "doctors.txt");

            status_label.set_color(sf::Color::Green);
            status_label.set_text("Doctor removed successfully.");
            doc_id_field.clear();
        });

        back_btn.set_on_click([this]() { go_back(); });
    }

    void handle_event(sf::RenderWindow& window, const sf::Event& event) override {
        doc_id_field.handle_event(event, window);
        remove_btn.handle_event(event, window);
        back_btn.handle_event(event, window);
    }
    void update() override {}
    void render(sf::RenderWindow& window) override {
        heading.render(window); divider.render(window);
        doc_id_label.render(window); doc_id_field.render(window);
        remove_btn.render(window); back_btn.render(window);
        status_label.render(window);
    }
    void go_back();
};