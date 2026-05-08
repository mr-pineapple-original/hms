// #pragma once
// #include "screen.hpp"
// #include "../components/label.hpp"
// #include "../components/color_label.hpp"
// #include "../components/button.hpp"
// #include "../components/ui_manager.hpp"

// // ── ViewAppointmentsScreen (Admin) ────────────────────────────────────────
// // Loads ALL appointments from appointments.txt, sorted by date ascending.
// // ─────────────────────────────────────────────────────────────────────────
// class ViewAppointmentsScreen : public Screen
// {
// private:
//     Label heading;
//     Label divider;
//     Label col_header;
//     Label appt_list;
//     ColorLabel status_label;
//     Button back_btn;

//     void load()
//     {
//         // TODO: FileHandler::get_all_appointments("appointments.txt", arr, count)
//         // Sort by date ascending (implement manually, no std::sort)
//         // Build display: ApptID | PatientName | DoctorName | Date | Slot | Status
//         col_header.set_text("ID  | Patient         | Doctor          | Date       | Slot  | Status");
//         appt_list.set_text("------------------------------------------------------------------------\n"
//                            "(all appointments will load from backend)");
//     }

// public:
//     ViewAppointmentsScreen()
//         : heading("All Appointments"),
//           divider("===================="),
//           col_header(""),
//           appt_list(""),
//           status_label(""),
//           back_btn("Back", 100, 40)
//     {
//         heading.set_position(50, 20);
//         divider.set_position(50, 48);
//         col_header.set_position(50, 80);
//         appt_list.set_position(50, 108);
//         status_label.set_position(50, 500);
//         back_btn.set_position(50, 540);

//         load();

//         back_btn.set_on_click([this]()
//                               { go_back(); });
//     }

//     void handle_event(sf::RenderWindow &window, const sf::Event &event) override
//     {
//         back_btn.handle_event(event, window);
//     }

//     void update() override {}

//     void render(sf::RenderWindow &window) override
//     {
//         heading.render(window);
//         divider.render(window);
//         col_header.render(window);
//         appt_list.render(window);
//         status_label.render(window);
//         back_btn.render(window);
//     }
//     void go_back();
// };



#pragma once
#include "screen.hpp"
#include "../components/label.hpp"
#include "../components/color_label.hpp"
#include "../components/button.hpp"
#include "../components/ui_manager.hpp"
#include "../../src/hospital_system.hpp"
#include "../components/sf_string_utils.hpp"

class ViewAppointmentsScreen : public Screen {
private:
    Label heading, divider, col_header, appt_list;
    ColorLabel status_label;
    Button back_btn;

    static int write_str(char* buf, int pos, const char* s) {
        for (int i = 0; s[i]; i++) buf[pos++] = s[i];
        return pos;
    }
    static int write_int(char* buf, int pos, int val) {
        char tmp[32]; int_to_char(val, tmp);
        return write_str(buf, pos, tmp);
    }

    void load() {
        int total = HospitalSystem::instance().get_appointments().size();
        if (total == 0) { appt_list.set_text("No appointments found."); return; }

        Appointment* ptr_a = HospitalSystem::instance().get_appointments().get_data();

        int indices[512];
        int count = total < 512 ? total : 512;
        for (int i = 0; i < count; i++) indices[i] = i;

        // Bubble sort descending by date
        for (int i = 0; i < count - 1; i++) {
            for (int j = 0; j < count - i - 1; j++) {
                char* d1 = (ptr_a + indices[j])->get_date();
                char* d2 = (ptr_a + indices[j+1])->get_date();
                int y1=(d1[6]-'0')*1000+(d1[7]-'0')*100+(d1[8]-'0')*10+(d1[9]-'0');
                int y2=(d2[6]-'0')*1000+(d2[7]-'0')*100+(d2[8]-'0')*10+(d2[9]-'0');
                int m1=(d1[3]-'0')*10+(d1[4]-'0'), m2=(d2[3]-'0')*10+(d2[4]-'0');
                int day1=(d1[0]-'0')*10+(d1[1]-'0'), day2=(d2[0]-'0')*10+(d2[1]-'0');
                bool sw = (y1<y2)||(y1==y2&&m1<m2)||(y1==y2&&m1==m2&&day1<day2);
                if (sw) { int tmp=indices[j]; indices[j]=indices[j+1]; indices[j+1]=tmp; }
            }
        }

        static char buf[8192]; int pos = 0;
        for (int i = 0; i < count; i++) {
            Appointment* a = ptr_a + indices[i];
            Patient* ptr_p = HospitalSystem::instance().get_patients().find(a->get_patient_id());
            Doctor*  ptr_d = HospitalSystem::instance().get_doctors().find(a->get_doctor_id());
            pos = write_int(buf, pos, a->get_id());
            pos = write_str(buf, pos, " | ");
            pos = write_str(buf, pos, ptr_p ? ptr_p->get_name() : "Unknown");
            pos = write_str(buf, pos, " | ");
            pos = write_str(buf, pos, ptr_d ? ptr_d->get_name() : "Unknown");
            pos = write_str(buf, pos, " | ");
            pos = write_str(buf, pos, a->get_date());
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
    ViewAppointmentsScreen()
        : heading("All Appointments"), divider("===================="),
          col_header("ID  | Patient         | Doctor          | Date       | Slot  | Status"),
          appt_list(""), status_label(""), back_btn("Back", 100, 40)
    {
        heading.set_position(50, 20);
        divider.set_position(50, 48);
        col_header.set_position(50, 80);
        appt_list.set_position(50, 108);
        status_label.set_position(50, 500);
        back_btn.set_position(50, 540);
        load();
        back_btn.set_on_click([this]() { go_back(); });
    }

    void handle_event(sf::RenderWindow& window, const sf::Event& event) override {
        back_btn.handle_event(event, window);
    }
    void update() override {}
    void render(sf::RenderWindow& window) override {
        heading.render(window); divider.render(window);
        col_header.render(window); appt_list.render(window);
        status_label.render(window); back_btn.render(window);
    }
    void go_back();
};