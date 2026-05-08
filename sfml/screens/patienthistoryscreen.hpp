// #pragma once
// #include "screen.hpp"
// #include "../components/label.hpp"
// #include "../components/color_label.hpp"
// #include "../components/button.hpp"
// #include "../components/text_field.hpp"
// #include "../components/ui_manager.hpp"
// #include "doctormenuscreen.hpp"
// #include "../../src/hospital_system.hpp"

// class PatientHistoryScreen : public Screen
// {
// private:
//     char doctor_id[64];

//     Label heading;
//     Label patient_id_label;
//     TextField patient_id_field;
//     Button search_btn;
//     Label records_list;
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
//     PatientHistoryScreen(const char *did)
//         : heading("View Patient Medical History"),
//           patient_id_label("Patient ID:"),
//           search_btn("Search", 100, 40),
//           records_list(""),
//           back_btn("Back", 100, 40),
//           status_label("")
//     {
//         safe_copy(doctor_id, did, sizeof(doctor_id));

//         heading.set_position(50, 20);
//         patient_id_label.set_position(50, 90);
//         patient_id_field.set_position(180, 80);
//         search_btn.set_position(450, 80);
//         records_list.set_position(50, 140);
//         status_label.set_position(50, 500);
//         back_btn.set_position(50, 540);

//         search_btn.set_on_click([this]()
//                                 {
//             if (patient_id_field.get_text().isEmpty()) {
//                 status_label.set_color(sf::Color::Red);
//                 status_label.set_text("Please enter a Patient ID.");
//                 return;
//             }
//             // TODO: validate patient exists AND has at least one completed appt with this doctor
//             //       if not → "Access denied. You can only view records of your own patients."
//             // TODO: FileHandler::get_prescriptions_by_patient_and_doctor(patient_id, doctor_id, arr, count)
//             // Sort by date descending
//             // Build display string
//             records_list.set_text("Date        | Medicines              | Notes\n"
//                                   "---------------------------------------------\n"
//                                   "(records load from backend)");
//             status_label.set_color(sf::Color::White);
//             status_label.set_text(""); });

//         back_btn.set_on_click([this]()
//                               { UIManager::instance().set_screen(new DoctorMenuScreen(doctor_id)); });
//     }

//     void handle_event(sf::RenderWindow &window, const sf::Event &event) override
//     {
//         patient_id_field.handle_event(event, window);
//         search_btn.handle_event(event, window);
//         back_btn.handle_event(event, window);
//     }

//     void update() override {}

//     void render(sf::RenderWindow &window) override
//     {
//         heading.render(window);
//         patient_id_label.render(window);
//         patient_id_field.render(window);
//         search_btn.render(window);
//         records_list.render(window);
//         status_label.render(window);
//         back_btn.render(window);
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

class PatientHistoryScreen : public Screen {
private:
    char doctor_id[64];

    Label      heading;
    Label      patient_id_label;
    TextField  patient_id_field;
    Button     search_btn;
    Label      records_list;
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

    static int write_str(char* buf, int pos, const char* s) {
        for (int i = 0; s[i]; i++) buf[pos++] = s[i];
        return pos;
    }

    static void sf_to_char(const sf::String& s, char* buf, std::size_t max) {
        std::size_t len = s.getSize() < max - 1 ? s.getSize() : max - 1;
        for (std::size_t i = 0; i < len; i++) buf[i] = (char)s[i];
        buf[len] = '\0';
    }

public:
    PatientHistoryScreen(const char* did)
        : heading("View Patient Medical History"),
          patient_id_label("Patient ID:"),
          search_btn("Search", 100, 40),
          records_list(""),
          back_btn("Back", 100, 40),
          status_label("")
    {
        safe_copy(doctor_id, did, sizeof(doctor_id));

        heading.set_position(50, 20);
        patient_id_label.set_position(50, 90);
        patient_id_field.set_position(180, 80);
        search_btn.set_position(450, 80);
        records_list.set_position(50, 140);
        status_label.set_position(50, 500);
        back_btn.set_position(50, 540);

        search_btn.set_on_click([this]() {
            if (patient_id_field.get_text().isEmpty()) {
                status_label.set_color(sf::Color::Red);
                status_label.set_text("Please enter a Patient ID.");
                return;
            }

            int did_int = 0;
            for (int i = 0; doctor_id[i]; i++) did_int = did_int * 10 + (doctor_id[i] - '0');

            char pid_buf[32];
            sf_to_char(patient_id_field.get_text(), pid_buf, sizeof(pid_buf));
            int patient_id = 0;
            for (int i = 0; pid_buf[i]; i++) patient_id = patient_id * 10 + (pid_buf[i] - '0');

            // Validate patient exists
            Patient* ptr_patient = HospitalSystem::instance().get_patients().find(patient_id);
            if (ptr_patient == nullptr) {
                status_label.set_color(sf::Color::Red);
                status_label.set_text("Access denied. You can only view records of your own patients.");
                records_list.set_text("");
                return;
            }

            // Validate doctor has at least one completed appointment with this patient
            Appointment* ptr_appts = HospitalSystem::instance().get_appointments().get_data();
            int total = HospitalSystem::instance().get_appointments().size();
            bool has_completed = false;

            for (int i = 0; i < total; i++) {
                if ((ptr_appts + i)->get_patient_id() == patient_id &&
                    (ptr_appts + i)->get_doctor_id()  == did_int &&
                    char_eq((const char*)(ptr_appts + i)->get_status(), "completed")) {
                    has_completed = true;
                    break;
                }
            }

            if (!has_completed) {
                status_label.set_color(sf::Color::Red);
                status_label.set_text("Access denied. You can only view records of your own patients.");
                records_list.set_text("");
                return;
            }

            // Collect prescriptions for this patient by this doctor
            Prescription* ptr_rx = HospitalSystem::instance().get_prescriptions().get_data();
            int rx_total = HospitalSystem::instance().get_prescriptions().size();

            int indices[100]; int count = 0;
            for (int i = 0; i < rx_total && count < 100; i++) {
                if ((ptr_rx + i)->get_patient_id() == patient_id &&
                    (ptr_rx + i)->get_doctor_id()  == did_int)
                    indices[count++] = i;
            }

            if (count == 0) {
                status_label.set_color(sf::Color::Red);
                status_label.set_text("No medical records found for this patient.");
                records_list.set_text("");
                return;
            }

            // Bubble sort descending by date (DD-MM-YYYY)
            for (int i = 0; i < count - 1; i++) {
                for (int j = 0; j < count - i - 1; j++) {
                    char* d1 = (ptr_rx + indices[j])->get_date();
                    char* d2 = (ptr_rx + indices[j+1])->get_date();
                    int y1=(d1[6]-'0')*1000+(d1[7]-'0')*100+(d1[8]-'0')*10+(d1[9]-'0');
                    int y2=(d2[6]-'0')*1000+(d2[7]-'0')*100+(d2[8]-'0')*10+(d2[9]-'0');
                    int m1=(d1[3]-'0')*10+(d1[4]-'0'), m2=(d2[3]-'0')*10+(d2[4]-'0');
                    int day1=(d1[0]-'0')*10+(d1[1]-'0'), day2=(d2[0]-'0')*10+(d2[1]-'0');
                    bool sw = (y1<y2)||(y1==y2&&m1<m2)||(y1==y2&&m1==m2&&day1<day2);
                    if (sw) { int tmp=indices[j]; indices[j]=indices[j+1]; indices[j+1]=tmp; }
                }
            }

            static char buf[4096]; int pos = 0;
            pos = write_str(buf, pos, "Date       | Medicines                    | Notes\n");
            pos = write_str(buf, pos, "--------------------------------------------------\n");
            for (int i = 0; i < count; i++) {
                Prescription* p = ptr_rx + indices[i];
                pos = write_str(buf, pos, p->get_date());
                pos = write_str(buf, pos, " | ");
                pos = write_str(buf, pos, p->get_medicine());
                pos = write_str(buf, pos, " | ");
                pos = write_str(buf, pos, p->get_doctor_note());
                buf[pos++] = '\n';
            }
            buf[pos] = '\0';

            records_list.set_text(buf);
            status_label.set_color(sf::Color::White);
            status_label.set_text("");
        });

        back_btn.set_on_click([this]() {
            UIManager::instance().set_screen(new DoctorMenuScreen(doctor_id));
        });
    }

    void handle_event(sf::RenderWindow& window, const sf::Event& event) override {
        patient_id_field.handle_event(event, window);
        search_btn.handle_event(event, window);
        back_btn.handle_event(event, window);
    }
    void update() override {}
    void render(sf::RenderWindow& window) override {
        heading.render(window);
        patient_id_label.render(window);
        patient_id_field.render(window);
        search_btn.render(window);
        records_list.render(window);
        status_label.render(window);
        back_btn.render(window);
    }
};