// #pragma once
// #include "screen.hpp"
// #include "../components/label.hpp"
// #include "../components/color_label.hpp"
// #include "../components/button.hpp"
// #include "../components/text_field.hpp"
// #include "../components/ui_manager.hpp"

// class AdminMenuScreen;

// // ── DischargePatientScreen ────────────────────────────────────────────────
// // Admin enters a Patient ID to discharge (mark as discharged in patients.txt).
// // Cannot discharge if patient has any unpaid bills or pending appointments.
// // ─────────────────────────────────────────────────────────────────────────
// class DischargePatientScreen : public Screen
// {
// private:
//     Label heading;
//     Label divider;
//     Label info_label; // shows patient summary after lookup
//     Label patient_id_label;
//     TextField patient_id_field;
//     Button lookup_btn;
//     Button discharge_btn;
//     Button back_btn;
//     ColorLabel status_label;

// public:
//     DischargePatientScreen()
//         : heading("Discharge Patient"),
//           divider("===================="),
//           info_label(""),
//           patient_id_label("Patient ID:"),
//           lookup_btn("Look Up", 110, 40),
//           discharge_btn("Discharge", 130, 40),
//           back_btn("Back", 100, 40),
//           status_label("")
//     {
//         heading.set_position(50, 20);
//         divider.set_position(50, 48);
//         patient_id_label.set_position(50, 110);
//         patient_id_field.set_position(200, 100);
//         lookup_btn.set_position(470, 100);
//         info_label.set_position(50, 160);
//         discharge_btn.set_position(180, 320);
//         back_btn.set_position(330, 320);
//         status_label.set_position(50, 390);

//         lookup_btn.set_on_click([this]()
//                                 {
//             if (patient_id_field.get_text().isEmpty()) {
//                 status_label.set_color(sf::Color::Red);
//                 status_label.set_text("Please enter a Patient ID.");
//                 return;
//             }
//             // TODO: FileHandler::find_patient(id, "patients.txt") → throw if not found
//             // TODO: show Name, Balance, pending appointments count, unpaid bills count
//             // Stub:
//             info_label.set_text("Name:    [Patient Name]         (stub)\n"
//                                 "Balance: PKR ----\n"
//                                 "Pending Appointments: --\n"
//                                 "Unpaid Bills:         --");
//             status_label.set_color(sf::Color::White);
//             status_label.set_text("Patient found. Review details before discharging."); });

//         discharge_btn.set_on_click([this]()
//                                    {
//             if (patient_id_field.get_text().isEmpty()) {
//                 status_label.set_color(sf::Color::Red);
//                 status_label.set_text("Please look up a patient first.");
//                 return;
//             }
//             // TODO: re-validate patient exists
//             // TODO: if any bill status == "unpaid"     → throw (cannot discharge)
//             // TODO: if any appointment status == "pending" → throw (cannot discharge)
//             // TODO: FileHandler::set_patient_discharged(id, "patients.txt")
//             status_label.set_color(sf::Color::Green);
//             status_label.set_text("Patient discharged successfully. (stub)");
//             patient_id_field.clear();
//             info_label.set_text(""); });

//         back_btn.set_on_click([this]()
//                               { go_back(); });
//     }

//     void handle_event(sf::RenderWindow &window, const sf::Event &event) override
//     {
//         patient_id_field.handle_event(event, window);
//         lookup_btn.handle_event(event, window);
//         discharge_btn.handle_event(event, window);
//         back_btn.handle_event(event, window);
//     }

//     void update() override {}

//     void render(sf::RenderWindow &window) override
//     {
//         heading.render(window);
//         divider.render(window);
//         patient_id_label.render(window);
//         patient_id_field.render(window);
//         lookup_btn.render(window);
//         info_label.render(window);
//         discharge_btn.render(window);
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
#include <fstream>

class DischargePatientScreen : public Screen {
private:
    Label heading, divider, info_label, patient_id_label;
    TextField patient_id_field;
    Button lookup_btn, discharge_btn, back_btn;
    ColorLabel status_label;

    static bool str_eq(const char* a, const char* b) {
        int i = 0;
        while (a[i] && b[i]) { if (a[i] != b[i]) return false; i++; }
        return a[i] == '\0' && b[i] == '\0';
    }
    static int write_str(char* buf, int pos, const char* s) {
        for (int i = 0; s[i]; i++) buf[pos++] = s[i];
        return pos;
    }
    static int write_int(char* buf, int pos, int val) {
        char tmp[32]; int_to_char(val, tmp);
        return write_str(buf, pos, tmp);
    }

public:
    DischargePatientScreen()
        : heading("Discharge Patient"), divider("===================="),
          info_label(""), patient_id_label("Patient ID:"),
          lookup_btn("Look Up", 110, 40), discharge_btn("Discharge", 130, 40),
          back_btn("Back", 100, 40), status_label("")
    {
        heading.set_position(50, 20);
        divider.set_position(50, 48);
        patient_id_label.set_position(50, 110);
        patient_id_field.set_position(200, 100);
        lookup_btn.set_position(470, 100);
        info_label.set_position(50, 160);
        discharge_btn.set_position(180, 320);
        back_btn.set_position(330, 320);
        status_label.set_position(50, 390);

        lookup_btn.set_on_click([this]() {
            if (patient_id_field.get_text().isEmpty()) {
                status_label.set_color(sf::Color::Red);
                status_label.set_text("Please enter a Patient ID.");
                return;
            }

            char id_buf[32];
            sf_string_to_char(patient_id_field.get_text(), id_buf, sizeof(id_buf));
            int pid = 0;
            for (int i = 0; id_buf[i]; i++) pid = pid * 10 + (id_buf[i] - '0');

            Patient* ptr_p = HospitalSystem::instance().get_patients().find(pid);
            if (ptr_p == nullptr) {
                status_label.set_color(sf::Color::Red);
                status_label.set_text("Patient not found.");
                info_label.set_text("");
                return;
            }

            int pending = 0, unpaid = 0;
            Appointment* ptr_a = HospitalSystem::instance().get_appointments().get_data();
            for (int i = 0; i < HospitalSystem::instance().get_appointments().size(); i++)
                if ((ptr_a + i)->get_patient_id() == pid &&
                    str_eq((const char*)(ptr_a + i)->get_status(), "pending"))
                    pending++;

            Bill* ptr_b = HospitalSystem::instance().get_bills().get_data();
            for (int i = 0; i < HospitalSystem::instance().get_bills().size(); i++)
                if ((ptr_b + i)->get_patient_id() == pid &&
                    str_eq((const char*)(ptr_b + i)->get_status(), "unpaid"))
                    unpaid++;

            static char info[256]; int pos = 0;
            char bal_buf[32]; double_to_char(ptr_p->get_balance(), bal_buf);
            pos = write_str(info, pos, "Name:    "); pos = write_str(info, pos, ptr_p->get_name());
            pos = write_str(info, pos, "\nBalance: PKR "); pos = write_str(info, pos, bal_buf);
            pos = write_str(info, pos, "\nPending Appointments: "); pos = write_int(info, pos, pending);
            pos = write_str(info, pos, "\nUnpaid Bills:         "); pos = write_int(info, pos, unpaid);
            info[pos] = '\0';
            info_label.set_text(info);
            status_label.set_color(sf::Color::White);
            status_label.set_text("Review details before discharging.");
        });

        discharge_btn.set_on_click([this]() {
            if (patient_id_field.get_text().isEmpty()) {
                status_label.set_color(sf::Color::Red);
                status_label.set_text("Please look up a patient first.");
                return;
            }

            char id_buf[32];
            sf_string_to_char(patient_id_field.get_text(), id_buf, sizeof(id_buf));
            int pid = 0;
            for (int i = 0; id_buf[i]; i++) pid = pid * 10 + (id_buf[i] - '0');

            Patient* ptr_p = HospitalSystem::instance().get_patients().find(pid);
            if (ptr_p == nullptr) {
                status_label.set_color(sf::Color::Red);
                status_label.set_text("Patient not found.");
                return;
            }

            Bill* ptr_b = HospitalSystem::instance().get_bills().get_data();
            for (int i = 0; i < HospitalSystem::instance().get_bills().size(); i++) {
                if ((ptr_b + i)->get_patient_id() == pid &&
                    str_eq((const char*)(ptr_b + i)->get_status(), "unpaid")) {
                    status_label.set_color(sf::Color::Red);
                    status_label.set_text("Cannot discharge: patient has unpaid bills.");
                    return;
                }
            }

            Appointment* ptr_a = HospitalSystem::instance().get_appointments().get_data();
            for (int i = 0; i < HospitalSystem::instance().get_appointments().size(); i++) {
                if ((ptr_a + i)->get_patient_id() == pid &&
                    str_eq((const char*)(ptr_a + i)->get_status(), "pending")) {
                    status_label.set_color(sf::Color::Red);
                    status_label.set_text("Cannot discharge: patient has pending appointments.");
                    return;
                }
            }

            // Archive to discharged.txt — FileHandler owns file I/O but has no
            // discharge function, so we use ofstream here as the backend does
            std::ofstream fout("discharged.txt", std::ios::app);
            if (fout.is_open()) {
                fout << *ptr_p << "\n";
                for (int i = 0; i < HospitalSystem::instance().get_appointments().size(); i++)
                    if ((ptr_a + i)->get_patient_id() == pid) fout << *(ptr_a + i) << "\n";
                for (int i = 0; i < HospitalSystem::instance().get_bills().size(); i++)
                    if ((ptr_b + i)->get_patient_id() == pid) fout << *(ptr_b + i) << "\n";
                Prescription* ptr_rx = HospitalSystem::instance().get_prescriptions().get_data();
                for (int i = 0; i < HospitalSystem::instance().get_prescriptions().size(); i++)
                    if ((ptr_rx + i)->get_patient_id() == pid) fout << *(ptr_rx + i) << "\n";
                fout.close();
            }

            // Remove from all in-memory storages and persist
            HospitalSystem::instance().get_patients().remove(pid);
            FileHandler::update_patients(HospitalSystem::instance().get_patients(), "patients.txt");

            for (int i = HospitalSystem::instance().get_appointments().size() - 1; i >= 0; i--)
                if ((ptr_a + i)->get_patient_id() == pid)
                    HospitalSystem::instance().get_appointments().remove((ptr_a + i)->get_id());
            FileHandler::update_appointments(HospitalSystem::instance().get_appointments(), "appointments.txt");

            for (int i = HospitalSystem::instance().get_bills().size() - 1; i >= 0; i--)
                if ((ptr_b + i)->get_patient_id() == pid)
                    HospitalSystem::instance().get_bills().remove((ptr_b + i)->get_id());
            FileHandler::update_bills(HospitalSystem::instance().get_bills(), "bills.txt");

            Prescription* ptr_rx = HospitalSystem::instance().get_prescriptions().get_data();
            for (int i = HospitalSystem::instance().get_prescriptions().size() - 1; i >= 0; i--)
                if ((ptr_rx + i)->get_patient_id() == pid)
                    HospitalSystem::instance().get_prescriptions().remove((ptr_rx + i)->get_id());
            FileHandler::update_prescriptions(HospitalSystem::instance().get_prescriptions(), "prescriptions.txt");

            status_label.set_color(sf::Color::Green);
            status_label.set_text("Patient discharged successfully.");
            patient_id_field.clear();
            info_label.set_text("");
        });

        back_btn.set_on_click([this]() { go_back(); });
    }

    void handle_event(sf::RenderWindow& window, const sf::Event& event) override {
        patient_id_field.handle_event(event, window);
        lookup_btn.handle_event(event, window);
        discharge_btn.handle_event(event, window);
        back_btn.handle_event(event, window);
    }
    void update() override {}
    void render(sf::RenderWindow& window) override {
        heading.render(window); divider.render(window);
        patient_id_label.render(window); patient_id_field.render(window);
        lookup_btn.render(window); info_label.render(window);
        discharge_btn.render(window); back_btn.render(window);
        status_label.render(window);
    }
    void go_back();
};