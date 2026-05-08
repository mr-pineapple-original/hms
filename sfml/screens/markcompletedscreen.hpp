// #pragma once
// #include "screen.hpp"
// #include "../components/label.hpp"
// #include "../components/color_label.hpp"
// #include "../components/button.hpp"
// #include "../components/text_field.hpp"
// #include "../components/ui_manager.hpp"
// #include "doctormenuscreen.hpp"
// #include "../../src/hospital_system.hpp"

// class MarkCompletedScreen : public Screen
// {
// private:
//     char doctor_id[64];

//     Label heading;
//     Label appt_list; // today's pending appointments
//     Label appt_id_label;
//     TextField appt_id_field;
//     Button confirm_btn;
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

//     void load()
//     {
//         // TODO: FileHandler::get_pending_appointments_today(doctor_id, arr, count)
//         appt_list.set_text("ID  | Patient Name         | Slot\n"
//                            "----------------------------------\n"
//                            "(today's pending appointments load from backend)");
//     }

// public:
//     MarkCompletedScreen(const char *did)
//         : heading("Mark Appointment Complete"),
//           appt_list(""),
//           appt_id_label("Appointment ID:"),
//           confirm_btn("Mark Complete", 160, 40),
//           back_btn("Back", 100, 40),
//           status_label("")
//     {
//         safe_copy(doctor_id, did, sizeof(doctor_id));

//         heading.set_position(50, 20);
//         appt_list.set_position(50, 70);
//         appt_id_label.set_position(50, 300);
//         appt_id_field.set_position(210, 290);
//         confirm_btn.set_position(180, 360);
//         back_btn.set_position(360, 360);
//         status_label.set_position(50, 420);

//         load();

//         confirm_btn.set_on_click([this]()
//                                  {
//             if (appt_id_field.get_text().isEmpty()) {
//                 status_label.set_color(sf::Color::Red);
//                 status_label.set_text("Please enter an Appointment ID.");
//                 return;
//             }
//             // TODO: validate appt belongs to this doctor, status==pending, date==today
//             // TODO: FileHandler::update_appointment_status(appt_id, "completed", "appointments.txt")
//             status_label.set_color(sf::Color::Green);
//             status_label.set_text("Appointment marked as completed. (stub)");
//             appt_id_field.clear();
//             load(); });

//         back_btn.set_on_click([this]()
//                               { UIManager::instance().set_screen(new DoctorMenuScreen(doctor_id)); });
//     }

//     void handle_event(sf::RenderWindow &window, const sf::Event &event) override
//     {
//         appt_id_field.handle_event(event, window);
//         confirm_btn.handle_event(event, window);
//         back_btn.handle_event(event, window);
//     }

//     void update() override {}

//     void render(sf::RenderWindow &window) override
//     {
//         heading.render(window);
//         appt_list.render(window);
//         appt_id_label.render(window);
//         appt_id_field.render(window);
//         confirm_btn.render(window);
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

class MarkCompletedScreen : public Screen {
private:
    char doctor_id[64];

    Label      heading;
    Label      appt_list;
    Label      appt_id_label;
    TextField  appt_id_field;
    Button     confirm_btn;
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

    void load() {
        int did_int = 0;
        for (int i = 0; doctor_id[i]; i++) did_int = did_int * 10 + (doctor_id[i] - '0');

        char today[11];
        HospitalSystem::instance().get_today_date(today);

        Appointment* ptr_appts = HospitalSystem::instance().get_appointments().get_data();
        int total = HospitalSystem::instance().get_appointments().size();

        static char buf[2048]; int pos = 0;
        pos = write_str(buf, pos, "ID  | Patient Name         | Slot\n");
        pos = write_str(buf, pos, "----------------------------------\n");

        bool any = false;
        for (int i = 0; i < total; i++) {
            if ((ptr_appts + i)->get_doctor_id() != did_int) continue;
            if (!char_eq((ptr_appts + i)->get_date(), today)) continue;
            if (!char_eq((const char*)(ptr_appts + i)->get_status(), "pending")) continue;
            any = true;
            Patient* ptr_p = HospitalSystem::instance().get_patients().find((ptr_appts + i)->get_patient_id());
            pos = write_int(buf, pos, (ptr_appts + i)->get_id());
            pos = write_str(buf, pos, " | ");
            pos = write_str(buf, pos, ptr_p ? ptr_p->get_name() : "Unknown");
            pos = write_str(buf, pos, " | ");
            pos = write_str(buf, pos, (ptr_appts + i)->get_time());
            buf[pos++] = '\n';
        }
        buf[pos] = '\0';

        appt_list.set_text(any ? buf : "No pending appointments for today.");
    }

public:
    MarkCompletedScreen(const char* did)
        : heading("Mark Appointment Complete"),
          appt_list(""),
          appt_id_label("Appointment ID:"),
          confirm_btn("Mark Complete", 160, 40),
          back_btn("Back", 100, 40),
          status_label("")
    {
        safe_copy(doctor_id, did, sizeof(doctor_id));
        heading.set_position(50, 20);
        appt_list.set_position(50, 70);
        appt_id_label.set_position(50, 300);
        appt_id_field.set_position(210, 290);
        confirm_btn.set_position(180, 360);
        back_btn.set_position(360, 360);
        status_label.set_position(50, 420);
        load();

        confirm_btn.set_on_click([this]() {
            if (appt_id_field.get_text().isEmpty()) {
                status_label.set_color(sf::Color::Red);
                status_label.set_text("Please enter an Appointment ID.");
                return;
            }

            int did_int = 0;
            for (int i = 0; doctor_id[i]; i++) did_int = did_int * 10 + (doctor_id[i] - '0');

            sf::String s = appt_id_field.get_text();
            char appt_buf[32]; std::size_t len = s.getSize() < 31 ? s.getSize() : 31;
            for (std::size_t i = 0; i < len; i++) appt_buf[i] = (char)s[i]; appt_buf[len] = '\0';
            int appt_id = 0;
            for (int i = 0; appt_buf[i]; i++) appt_id = appt_id * 10 + (appt_buf[i] - '0');

            char today[11];
            HospitalSystem::instance().get_today_date(today);

            Appointment* ptr_appt = HospitalSystem::instance().get_appointments().find(appt_id);
            if (ptr_appt == nullptr ||
                ptr_appt->get_doctor_id() != did_int ||
                !char_eq((const char*)ptr_appt->get_status(), "pending") ||
                !char_eq(ptr_appt->get_date(), today)) {
                status_label.set_color(sf::Color::Red);
                status_label.set_text("Invalid appointment ID.");
                return;
            }

            char completed[] = "completed";
            ptr_appt->set_appointment(ptr_appt->get_id(), ptr_appt->get_patient_id(),
                                      ptr_appt->get_doctor_id(), ptr_appt->get_date(),
                                      ptr_appt->get_time(), completed);
            FileHandler::update_appointments(HospitalSystem::instance().get_appointments(), "appointments.txt");

            status_label.set_color(sf::Color::Green);
            status_label.set_text("Appointment marked as completed.");
            appt_id_field.clear();
            load();
        });

        back_btn.set_on_click([this]() {
            UIManager::instance().set_screen(new DoctorMenuScreen(doctor_id));
        });
    }

    void handle_event(sf::RenderWindow& window, const sf::Event& event) override {
        appt_id_field.handle_event(event, window);
        confirm_btn.handle_event(event, window);
        back_btn.handle_event(event, window);
    }
    void update() override {}
    void render(sf::RenderWindow& window) override {
        heading.render(window);
        appt_list.render(window);
        appt_id_label.render(window);
        appt_id_field.render(window);
        confirm_btn.render(window);
        back_btn.render(window);
        status_label.render(window);
    }
};