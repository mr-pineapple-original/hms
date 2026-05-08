// #pragma once
// #include "screen.hpp"
// #include "../components/label.hpp"
// #include "../components/color_label.hpp"
// #include "../components/button.hpp"
// #include "../components/ui_manager.hpp"
// #include "doctormenuscreen.hpp"
// #include "../../src/hospital_system.hpp"

// class TodayAppointmentsScreen : public Screen
// {
// private:
//     char doctor_id[64];

//     Label heading;
//     Label appt_list;
//     ColorLabel status_label;
//     Button back_btn;

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
//         // TODO: get today's date via time()/strftime()
//         // TODO: FileHandler::get_appointments_by_doctor_today(doctor_id, date, arr, count)
//         // Sort by time slot ascending
//         // Build string: Appt ID | Patient Name | Slot | Status
//         appt_list.set_text("ID  | Patient Name         | Slot  | Status\n"
//                            "--------------------------------------------\n"
//                            "(today's appointments load from backend)");
//     }

// public:
//     TodayAppointmentsScreen(const char *did)
//         : heading("Today's Appointments"),
//           appt_list(""),
//           status_label(""),
//           back_btn("Back", 100, 40)
//     {
//         safe_copy(doctor_id, did, sizeof(doctor_id));

//         heading.set_position(50, 20);
//         appt_list.set_position(50, 70);
//         status_label.set_position(50, 500);
//         back_btn.set_position(50, 540);

//         load();

//         back_btn.set_on_click([this]()
//                               { UIManager::instance().set_screen(new DoctorMenuScreen(doctor_id)); });
//     }

//     void handle_event(sf::RenderWindow &window, const sf::Event &event) override
//     {
//         back_btn.handle_event(event, window);
//     }

//     void update() override {}

//     void render(sf::RenderWindow &window) override
//     {
//         heading.render(window);
//         appt_list.render(window);
//         status_label.render(window);
//         back_btn.render(window);
//     }
// };


#pragma once
#include "screen.hpp"
#include "../components/label.hpp"
#include "../components/color_label.hpp"
#include "../components/button.hpp"
#include "../components/ui_manager.hpp"
#include "doctormenuscreen.hpp"
#include "../../src/hospital_system.hpp"

class TodayAppointmentsScreen : public Screen {
private:
    char doctor_id[64];

    Label      heading;
    Label      appt_list;
    ColorLabel status_label;
    Button     back_btn;

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

        // Collect indices for this doctor today
        int indices[100]; int count = 0;
        for (int i = 0; i < total && count < 100; i++) {
            if ((ptr_appts + i)->get_doctor_id() == did_int &&
                char_eq((ptr_appts + i)->get_date(), today))
                indices[count++] = i;
        }

        if (count == 0) { appt_list.set_text("No appointments scheduled for today."); return; }

        // Bubble sort ascending by time slot (HH:MM)
        for (int i = 0; i < count - 1; i++) {
            for (int j = 0; j < count - i - 1; j++) {
                char* t1 = (ptr_appts + indices[j])->get_time();
                char* t2 = (ptr_appts + indices[j+1])->get_time();
                int h1=(t1[0]-'0')*10+(t1[1]-'0'), h2=(t2[0]-'0')*10+(t2[1]-'0');
                int m1=(t1[3]-'0')*10+(t1[4]-'0'), m2=(t2[3]-'0')*10+(t2[4]-'0');
                bool sw = (h1>h2)||(h1==h2&&m1>m2);
                if (sw) { int tmp=indices[j]; indices[j]=indices[j+1]; indices[j+1]=tmp; }
            }
        }

        static char buf[2048]; int pos = 0;
        pos = write_str(buf, pos, "ID  | Patient Name         | Slot  | Status\n");
        pos = write_str(buf, pos, "--------------------------------------------\n");
        for (int i = 0; i < count; i++) {
            Appointment* a = ptr_appts + indices[i];
            Patient* ptr_p = HospitalSystem::instance().get_patients().find(a->get_patient_id());
            pos = write_int(buf, pos, a->get_id());
            pos = write_str(buf, pos, " | ");
            pos = write_str(buf, pos, ptr_p ? ptr_p->get_name() : "Unknown");
            pos = write_str(buf, pos, " | ");
            pos = write_str(buf, pos, a->get_time());
            pos = write_str(buf, pos, " | ");
            pos = write_str(buf, pos, (const char*)a->get_status());
            buf[pos++] = '\n';
        }
        buf[pos] = '\0';
        appt_list.set_text(buf);
    }

public:
    TodayAppointmentsScreen(const char* did)
        : heading("Today's Appointments"),
          appt_list(""),
          status_label(""),
          back_btn("Back", 100, 40)
    {
        safe_copy(doctor_id, did, sizeof(doctor_id));
        heading.set_position(50, 20);
        appt_list.set_position(50, 70);
        status_label.set_position(50, 500);
        back_btn.set_position(50, 540);
        load();
        back_btn.set_on_click([this]() {
            UIManager::instance().set_screen(new DoctorMenuScreen(doctor_id));
        });
    }

    void handle_event(sf::RenderWindow& window, const sf::Event& event) override {
        back_btn.handle_event(event, window);
    }
    void update() override {}
    void render(sf::RenderWindow& window) override {
        heading.render(window);
        appt_list.render(window);
        status_label.render(window);
        back_btn.render(window);
    }
};