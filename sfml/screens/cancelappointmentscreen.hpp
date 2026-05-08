// #pragma once
// #include "screen.hpp"
// #include "../components/label.hpp"
// #include "../components/color_label.hpp"
// #include "../components/button.hpp"
// #include "../components/text_field.hpp"
// #include "../components/ui_manager.hpp"
// #include "patientmenuscreen.hpp"
// #include "loginscreen.hpp"
// #include "../../src/hospital_system.hpp"
// #include "../../src/patient.hpp"

// // ── CancelAppointmentScreen ───────────────────────────────────────────────
// // Shows patient's pending appointments, prompts for appointment ID to cancel.
// // Refund is issued via overloaded += on Patient.
// // ─────────────────────────────────────────────────────────────────────────

// class CancelAppointmentScreen : public Screen
// {
// private:
//     char patient_id[64];

//     Label heading;
//     Label divider;
//     Label list_heading;
//     Label appt_list; // pending appointments displayed here

//     Label appt_id_label;
//     TextField appt_id_field;

//     Button cancel_btn;
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

//     void load_pending_appointments()
//     {
//         // TODO: FileHandler::get_pending_appointments(patient_id, "appointments.txt", ...)
//         // Build display string: "ID | Doctor Name | Date | Time Slot"
//         appt_list.set_text("ID   Doctor Name            Date         Slot\n"
//                            "---------------------------------------------\n"
//                            "(pending appointments will load from backend)");
//     }

// public:
//     CancelAppointmentScreen(const char *pid)
//         : heading("Cancel Appointment"),
//           divider("=============================="),
//           list_heading("Your Pending Appointments:"),
//           appt_list(""),
//           appt_id_label("Appointment ID to cancel:"),
//           cancel_btn("Cancel Appointment", 200, 40),
//           back_btn("Back", 100, 40),
//           status_label("")
//     {
//         safe_copy(patient_id, pid, sizeof(patient_id));

//         heading.set_position(50, 20);
//         divider.set_position(50, 48);
//         list_heading.set_position(50, 85);
//         appt_list.set_position(50, 115);

//         appt_id_label.set_position(50, 280);
//         appt_id_field.set_position(310, 270);

//         cancel_btn.set_position(180, 340);
//         back_btn.set_position(410, 340);

//         status_label.set_position(50, 410);

//         load_pending_appointments();

//         cancel_btn.set_on_click([this]()
//                                 {
//             sf::String id_input = appt_id_field.get_text();
//             if (id_input.isEmpty()) {
//                 status_label.set_color(sf::Color::Red);
//                 status_label.set_text("Please enter an Appointment ID.");
//                 return;
//             }
 
//             // TODO: char appt_buf[32]; convert id_input → appt_buf
//             // 1. Validate appointment belongs to this patient and status == "pending"
//             //    → if not: status red, "Invalid appointment ID."
//             // 2. Update appointment status to "cancelled" in appointments.txt
//             // 3. patient += doctor_fee  (overloaded +=)
//             // 4. FileHandler::update_patient_balance(...)
//             // 5. Update bill status to "cancelled" in bills.txt
 
//             status_label.set_color(sf::Color::Green);
//             status_label.set_text("Appointment cancelled. PKR [fee] refunded. (stub)");
//             appt_id_field.clear();
//             load_pending_appointments(); });

//         back_btn.set_on_click([this]()
//                               {
//                 // We need to reload patient data to get updated balance
//     int pid = 0;
//     for (int i = 0; patient_id[i] != '\0'; i++)
//         pid = pid * 10 + (patient_id[i] - '0');

//     Patient* ptr_p = HospitalSystem::instance().get_patients().find(pid);
//     if (ptr_p != nullptr)
//         UIManager::instance().set_screen(
//             new PatientMenuScreen(patient_id,
//                                   ptr_p->get_name(),
//                                   ptr_p->get_balance()));
//     else
//         UIManager::instance().set_screen(new LoginScreen()); });
//     }

//     void handle_event(sf::RenderWindow &window, const sf::Event &event) override
//     {
//         appt_id_field.handle_event(event, window);
//         cancel_btn.handle_event(event, window);
//         back_btn.handle_event(event, window);
//     }

//     void update() override {}

//     void render(sf::RenderWindow &window) override
//     {
//         heading.render(window);
//         divider.render(window);
//         list_heading.render(window);
//         appt_list.render(window);
//         appt_id_label.render(window);
//         appt_id_field.render(window);
//         cancel_btn.render(window);
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
#include "patientmenuscreen.hpp"
#include "loginscreen.hpp"
#include "../../src/hospital_system.hpp"
#include "../../src/patient.hpp"
#include "../../src/file_handler.hpp"
 
class CancelAppointmentScreen : public Screen {
private:
    char patient_id[64];
 
    Label      heading;
    Label      divider;
    Label      list_heading;
    Label      appt_list;
    Label      appt_id_label;
    TextField  appt_id_field;
    Button     cancel_btn;
    Button     back_btn;
    ColorLabel status_label;
 
    static void safe_copy(char* dst, const char* src, std::size_t max) {
        std::size_t i = 0;
        while (i < max - 1 && src[i] != '\0') { dst[i] = src[i]; ++i; }
        dst[i] = '\0';
    }
 
    static bool char_eq(const char* a, const char* b) {
        int i = 0;
        while (a[i] && b[i]) { if (a[i] != b[i]) return false; i++; }
        return a[i] == '\0' && b[i] == '\0';
    }
 
    // Append int to buf at pos, return new pos
    static int write_int(char* buf, int pos, int val) {
        char tmp[16]; int ti = 0;
        if (val == 0) { tmp[ti++] = '0'; }
        else { int n = val; char r[16]; int ri = 0; while(n>0){r[ri++]='0'+n%10;n/=10;} while(ri>0)tmp[ti++]=r[--ri]; }
        for (int i = 0; i < ti; i++) buf[pos++] = tmp[i];
        return pos;
    }
 
    static int write_str(char* buf, int pos, const char* s) {
        for (int i = 0; s[i]; i++) buf[pos++] = s[i];
        return pos;
    }
 
    void load_pending_appointments() {
        int pid_int = 0;
        for (int i = 0; patient_id[i]; i++) pid_int = pid_int * 10 + (patient_id[i] - '0');
 
        Appointment* ptr_appts = HospitalSystem::instance().get_appointments().get_data();
        int count = HospitalSystem::instance().get_appointments().size();
 
        static char buf[2048];
        int pos = 0;
        pos = write_str(buf, pos, "ID  | Doctor Name           | Date       | Slot\n");
        pos = write_str(buf, pos, "------------------------------------------------\n");
 
        bool any = false;
        for (int i = 0; i < count; i++) {
            if ((ptr_appts + i)->get_patient_id() != pid_int) continue;
            if (!char_eq((const char*)(ptr_appts + i)->get_status(), "pending")) continue;
            any = true;
 
            pos = write_int(buf, pos, (ptr_appts + i)->get_id());
            pos = write_str(buf, pos, " | ");
 
            Doctor* ptr_d = HospitalSystem::instance().get_doctors().find((ptr_appts + i)->get_doctor_id());
            pos = write_str(buf, pos, ptr_d ? ptr_d->get_name() : "Unknown");
            pos = write_str(buf, pos, " | ");
            pos = write_str(buf, pos, (ptr_appts + i)->get_date());
            pos = write_str(buf, pos, " | ");
            pos = write_str(buf, pos, (ptr_appts + i)->get_time());
            buf[pos++] = '\n';
        }
        buf[pos] = '\0';
 
        if (!any)
            appt_list.set_text("You have no pending appointments.");
        else
            appt_list.set_text(buf);
    }
 
public:
    CancelAppointmentScreen(const char* pid)
        : heading("Cancel Appointment"),
          divider("=============================="),
          list_heading("Your Pending Appointments:"),
          appt_list(""),
          appt_id_label("Appointment ID to cancel:"),
          cancel_btn("Cancel Appointment", 200, 40),
          back_btn("Back", 100, 40),
          status_label("")
    {
        safe_copy(patient_id, pid, sizeof(patient_id));
 
        heading.set_position(50, 20);
        divider.set_position(50, 48);
        list_heading.set_position(50, 85);
        appt_list.set_position(50, 115);
        appt_id_label.set_position(50, 280);
        appt_id_field.set_position(310, 270);
        cancel_btn.set_position(180, 340);
        back_btn.set_position(410, 340);
        status_label.set_position(50, 410);
 
        load_pending_appointments();
 
        cancel_btn.set_on_click([this]() {
            if (appt_id_field.get_text().isEmpty()) {
                status_label.set_color(sf::Color::Red);
                status_label.set_text("Please enter an Appointment ID.");
                return;
            }
 
            // Parse IDs
            int pid_int = 0;
            for (int i = 0; patient_id[i]; i++) pid_int = pid_int * 10 + (patient_id[i] - '0');
 
            sf::String s = appt_id_field.get_text();
            char appt_buf[32];
            std::size_t len = s.getSize() < 31 ? s.getSize() : 31;
            for (std::size_t i = 0; i < len; i++) appt_buf[i] = (char)s[i];
            appt_buf[len] = '\0';
            int appt_id = 0;
            for (int i = 0; appt_buf[i]; i++) appt_id = appt_id * 10 + (appt_buf[i] - '0');
 
            Appointment* ptr_appt = HospitalSystem::instance().get_appointments().find(appt_id);
            if (ptr_appt == nullptr ||
                ptr_appt->get_patient_id() != pid_int ||
                !char_eq((const char*)ptr_appt->get_status(), "pending")) {
                status_label.set_color(sf::Color::Red);
                status_label.set_text("Invalid appointment ID.");
                return;
            }
 
            // Get doctor fee for refund
            Doctor* ptr_d = HospitalSystem::instance().get_doctors().find(ptr_appt->get_doctor_id());
            double fee = ptr_d ? ptr_d->get_fee() : 0.0;
 
            // Mark appointment cancelled
            char cancelled[] = "cancelled";
            ptr_appt->set_appointment(ptr_appt->get_id(), ptr_appt->get_patient_id(),
                                      ptr_appt->get_doctor_id(), ptr_appt->get_date(),
                                      ptr_appt->get_time(), cancelled);
            FileHandler::update_appointments(HospitalSystem::instance().get_appointments(), "appointments.txt");
 
            // Refund using +=
            Patient* ptr_p = HospitalSystem::instance().get_patients().find(pid_int);
            if (ptr_p) {
                *ptr_p += fee;
                FileHandler::update_patients(HospitalSystem::instance().get_patients(), "patients.txt");
            }
 
            // Cancel corresponding bill
            Bill* ptr_bills = HospitalSystem::instance().get_bills().get_data();
            int bill_count  = HospitalSystem::instance().get_bills().size();
            for (int i = 0; i < bill_count; i++) {
                if ((ptr_bills + i)->get_appointment_id() == appt_id) {
                    (ptr_bills + i)->set_bill(
                        (ptr_bills + i)->get_id(), (ptr_bills + i)->get_patient_id(),
                        (ptr_bills + i)->get_appointment_id(), (ptr_bills + i)->get_amount(),
                        cancelled, (ptr_bills + i)->get_date());
                    break;
                }
            }
            FileHandler::update_bills(HospitalSystem::instance().get_bills(), "bills.txt");
 
            status_label.set_color(sf::Color::Green);
            status_label.set_text("Appointment cancelled. Fee refunded to your balance.");
            appt_id_field.clear();
            load_pending_appointments();
        });
 
        back_btn.set_on_click([this]() {
            int pid_int = 0;
            for (int i = 0; patient_id[i]; i++) pid_int = pid_int * 10 + (patient_id[i] - '0');
            Patient* ptr_p = HospitalSystem::instance().get_patients().find(pid_int);
            if (ptr_p != nullptr)
                UIManager::instance().set_screen(
                    new PatientMenuScreen(patient_id, ptr_p->get_name(), ptr_p->get_balance()));
            else
                UIManager::instance().set_screen(new LoginScreen());
        });
    }
 
    void handle_event(sf::RenderWindow& window, const sf::Event& event) override {
        appt_id_field.handle_event(event, window);
        cancel_btn.handle_event(event, window);
        back_btn.handle_event(event, window);
    }
 
    void update() override {}
 
    void render(sf::RenderWindow& window) override {
        heading.render(window);
        divider.render(window);
        list_heading.render(window);
        appt_list.render(window);
        appt_id_label.render(window);
        appt_id_field.render(window);
        cancel_btn.render(window);
        back_btn.render(window);
        status_label.render(window);
    }
};