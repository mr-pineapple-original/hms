// #pragma once
// #include "screen.hpp"
// #include "../components/label.hpp"
// #include "../components/color_label.hpp"
// #include "../components/button.hpp"
// #include "../components/text_field.hpp"
// #include "../components/ui_manager.hpp"
// #include "doctormenuscreen.hpp"
// #include "../../src/hospital_system.hpp"

// class WritePrescriptionScreen : public Screen
// {
// private:
//     char doctor_id[64];

//     Label heading;
//     Label appt_id_label;
//     TextField appt_id_field;
//     Label medicines_label;
//     TextField medicines_field; // e.g. Paracetamol 500mg;Amoxicillin 250mg
//     Label notes_label;
//     TextField notes_field;
//     Button save_btn;
//     Button back_btn;
//     ColorLabel status_label;

//     static void safe_copy(char *dst, const char *src, std::size_t max)
//     {
//         std::size_t i = 0;
//         while (i < max - 1 && src[i] != '\0')
//         {
//             dst[i] = src[i];
//             ++i;
//         }
//         dst[i] = '\0';
//     }

// public:
//     WritePrescriptionScreen(const char *did)
//         : heading("Write Prescription"),
//           appt_id_label("Appointment ID:"),
//           medicines_label("Medicines (Name Dose;...):"),
//           notes_label("Notes:"),
//           save_btn("Save Prescription", 180, 40),
//           back_btn("Back", 100, 40),
//           status_label("")
//     {
//         safe_copy(doctor_id, did, sizeof(doctor_id));

//         heading.set_position(50, 20);

//         appt_id_label.set_position(50, 90);
//         appt_id_field.set_position(220, 80);

//         medicines_label.set_position(50, 160);
//         medicines_field.set_position(50, 190); // wider field below label

//         notes_label.set_position(50, 260);
//         notes_field.set_position(50, 290);

//         save_btn.set_position(180, 370);
//         back_btn.set_position(380, 370);
//         status_label.set_position(50, 430);

//         save_btn.set_on_click([this]()
//                               {
//             if (appt_id_field.get_text().isEmpty() || medicines_field.get_text().isEmpty()) {
//                 status_label.set_color(sf::Color::Red);
//                 status_label.set_text("Appointment ID and medicines are required.");
//                 return;
//             }
//             // TODO: validate appt belongs to this doctor and status == "completed"
//             // TODO: check prescriptions.txt — if already exists → error
//             // TODO: FileHandler::append_prescription(appt_id, doctor_id, patient_id, date, medicines, notes)
//             status_label.set_color(sf::Color::Green);
//             status_label.set_text("Prescription saved. (stub)");
//             appt_id_field.clear();
//             medicines_field.clear();
//             notes_field.clear(); });

//         back_btn.set_on_click([this]()
//                               { UIManager::instance().set_screen(new DoctorMenuScreen(doctor_id)); });
//     }

//     void handle_event(sf::RenderWindow &window, const sf::Event &event) override
//     {
//         appt_id_field.handle_event(event, window);
//         medicines_field.handle_event(event, window);
//         notes_field.handle_event(event, window);
//         save_btn.handle_event(event, window);
//         back_btn.handle_event(event, window);
//     }

//     void update() override {}

//     void render(sf::RenderWindow &window) override
//     {
//         heading.render(window);
//         appt_id_label.render(window);
//         appt_id_field.render(window);
//         medicines_label.render(window);
//         medicines_field.render(window);
//         notes_label.render(window);
//         notes_field.render(window);
//         save_btn.render(window);
//         back_btn.render(window);
//         status_label.render(window);
//     }
// };



#pragma once
#include "screen.hpp"
#include "../components/label.hpp"
#include "../components/color_label.hpp"
#include "../components/button.hpp"
#include "../components/text_field.hpp"
#include "../components/ui_manager.hpp"
#include "doctormenuscreen.hpp"
#include "../../src/hospital_system.hpp"
#include "../../src/file_handler.hpp"

class WritePrescriptionScreen : public Screen {
private:
    char doctor_id[64];

    Label      heading;
    Label      appt_id_label;
    TextField  appt_id_field;
    Label      medicines_label;
    TextField  medicines_field;
    Label      notes_label;
    TextField  notes_field;
    Button     save_btn;
    Button     back_btn;
    ColorLabel status_label;

    static void safe_copy(char* dst, const char* src, std::size_t max) {
        std::size_t i = 0;
        while (i < max - 1 && src[i]) { dst[i] = src[i]; ++i; }
        dst[i] = '\0';
    }

    static bool char_eq(const char* a, const char* b) {
        int i = 0;
        while (a[i] && b[i]) { if (a[i] != b[i]) return false; i++; }
        return a[i] == '\0' && b[i] == '\0';
    }

    static void sf_to_char(const sf::String& s, char* buf, std::size_t max) {
        std::size_t len = s.getSize() < max - 1 ? s.getSize() : max - 1;
        for (std::size_t i = 0; i < len; i++) buf[i] = (char)s[i];
        buf[len] = '\0';
    }

public:
    WritePrescriptionScreen(const char* did)
        : heading("Write Prescription"),
          appt_id_label("Appointment ID:"),
          medicines_label("Medicines (Name Dose;...):"),
          notes_label("Notes:"),
          save_btn("Save Prescription", 180, 40),
          back_btn("Back", 100, 40),
          status_label("")
    {
        safe_copy(doctor_id, did, sizeof(doctor_id));

        heading.set_position(50, 20);
        appt_id_label.set_position(50, 90);
        appt_id_field.set_position(220, 80);
        medicines_label.set_position(50, 160);
        medicines_field.set_position(50, 190);
        notes_label.set_position(50, 260);
        notes_field.set_position(50, 290);
        save_btn.set_position(180, 370);
        back_btn.set_position(380, 370);
        status_label.set_position(50, 430);

        save_btn.set_on_click([this]() {
            if (appt_id_field.get_text().isEmpty() || medicines_field.get_text().isEmpty()) {
                status_label.set_color(sf::Color::Red);
                status_label.set_text("Appointment ID and medicines are required.");
                return;
            }

            int did_int = 0;
            for (int i = 0; doctor_id[i]; i++) did_int = did_int * 10 + (doctor_id[i] - '0');

            char appt_buf[32];
            sf_to_char(appt_id_field.get_text(), appt_buf, sizeof(appt_buf));
            int appt_id = 0;
            for (int i = 0; appt_buf[i]; i++) appt_id = appt_id * 10 + (appt_buf[i] - '0');

            // Validate appointment belongs to this doctor and is completed
            Appointment* ptr_appt = HospitalSystem::instance().get_appointments().find(appt_id);
            if (ptr_appt == nullptr ||
                ptr_appt->get_doctor_id() != did_int ||
                !char_eq((const char*)ptr_appt->get_status(), "completed")) {
                status_label.set_color(sf::Color::Red);
                status_label.set_text("Invalid appointment ID.");
                return;
            }

            // Check if prescription already exists
            Prescription* ptr_rx = HospitalSystem::instance().get_prescriptions().get_data();
            int rx_count = HospitalSystem::instance().get_prescriptions().size();
            for (int i = 0; i < rx_count; i++) {
                if ((ptr_rx + i)->get_appointment_id() == appt_id) {
                    status_label.set_color(sf::Color::Red);
                    status_label.set_text("Prescription already written for this appointment.");
                    return;
                }
            }

            char med_buf[500], notes_buf[300];
            sf_to_char(medicines_field.get_text(), med_buf,   sizeof(med_buf));
            sf_to_char(notes_field.get_text(),     notes_buf, sizeof(notes_buf));

            char today[11];
            HospitalSystem::instance().get_today_date(today);

            int new_id = FileHandler::generate_new_id(HospitalSystem::instance().get_prescriptions());

            Prescription new_rx(new_id, appt_id,
                                ptr_appt->get_patient_id(),
                                did_int, today, med_buf, notes_buf);

            HospitalSystem::instance().get_prescriptions().add(new_rx);
            FileHandler::append_prescription(new_rx, "prescriptions.txt");

            status_label.set_color(sf::Color::Green);
            status_label.set_text("Prescription saved.");
            appt_id_field.clear();
            medicines_field.clear();
            notes_field.clear();
        });

        back_btn.set_on_click([this]() {
            UIManager::instance().set_screen(new DoctorMenuScreen(doctor_id));
        });
    }

    void handle_event(sf::RenderWindow& window, const sf::Event& event) override {
        appt_id_field.handle_event(event, window);
        medicines_field.handle_event(event, window);
        notes_field.handle_event(event, window);
        save_btn.handle_event(event, window);
        back_btn.handle_event(event, window);
    }
    void update() override {}
    void render(sf::RenderWindow& window) override {
        heading.render(window);
        appt_id_label.render(window);
        appt_id_field.render(window);
        medicines_label.render(window);
        medicines_field.render(window);
        notes_label.render(window);
        notes_field.render(window);
        save_btn.render(window);
        back_btn.render(window);
        status_label.render(window);
    }
};