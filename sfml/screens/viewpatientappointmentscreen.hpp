// #pragma once
// #include "screen.hpp"
// #include "../components/label.hpp"
// #include "../components/color_label.hpp"
// #include "../components/button.hpp"
// #include "../components/ui_manager.hpp"
// #include "patientmenuscreen.hpp"
// #include "loginscreen.hpp"
// #include "../../src/hospital_system.hpp"
// #include "../../src/patient.hpp"
// // ── PatientAppointmentScreen ────────────────────────────────────────────────
// // Shows all appointments for this patient sorted by date ascending.
// // TODO: connect to FileHandler::get_appointments_by_patient(...)
// // ─────────────────────────────────────────────────────────────────────────

// class PatientAppointmentScreen : public Screen
// {
// private:
//     char patient_id[64];

//     Label heading;
//     Label divider;
//     Label col_header;
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
//         // TODO: FileHandler::get_all_appointments(patient_id, "appointments.txt", arr, count)
//         // Sort by date ascending (implement manually)
//         // Build display string: ID | Doctor Name | Spec | Date | Slot | Status
//         appt_list.set_text("ID  | Doctor            | Date        | Slot  | Status\n"
//                            "--------------------------------------------------------\n"
//                            "(appointments will load from backend)");
//     }

// public:
//     PatientAppointmentScreen(const char *pid)
//         : heading("My Appointments"),
//           divider("===================="),
//           col_header(""),
//           appt_list(""),
//           status_label(""),
//           back_btn("Back", 100, 40)
//     {
//         safe_copy(patient_id, pid, sizeof(patient_id));

//         heading.set_position(50, 20);
//         divider.set_position(50, 48);
//         appt_list.set_position(50, 80);
//         status_label.set_position(50, 500);
//         back_btn.set_position(50, 540);

//         load();

//         back_btn.set_on_click([this]()
//                               {
//     int pid = 0;
//     for (int i = 0; patient_id[i] != '\0'; i++)
//         pid = pid * 10 + (patient_id[i] - '0');
//     Patient* ptr_p = HospitalSystem::instance().get_patients().find(pid);
//     if (ptr_p != nullptr)
//         UIManager::instance().set_screen(new PatientMenuScreen(patient_id, ptr_p->get_name(), ptr_p->get_balance()));
//     else
//         UIManager::instance().set_screen(new LoginScreen()); });
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
#include "patientmenuscreen.hpp"
#include "loginscreen.hpp"
#include "../../src/hospital_system.hpp"
#include "../../src/patient.hpp"
 
class PatientAppointmentScreen : public Screen {
private:
    char patient_id[64];
 
    Label      heading;
    Label      divider;
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
        int pid_int = 0;
        for (int i = 0; patient_id[i]; i++) pid_int = pid_int * 10 + (patient_id[i] - '0');
 
        Appointment* ptr_appts = HospitalSystem::instance().get_appointments().get_data();
        int total = HospitalSystem::instance().get_appointments().size();
 
        // Collect indices for this patient
        int indices[100]; int count = 0;
        for (int i = 0; i < total && count < 100; i++)
            if ((ptr_appts + i)->get_patient_id() == pid_int)
                indices[count++] = i;
 
        if (count == 0) { appt_list.set_text("No appointments found."); return; }
 
        // Bubble sort ascending by date (DD-MM-YYYY)
        for (int i = 0; i < count - 1; i++) {
            for (int j = 0; j < count - i - 1; j++) {
                char* d1 = (ptr_appts + indices[j])->get_date();
                char* d2 = (ptr_appts + indices[j+1])->get_date();
                int y1=(d1[6]-'0')*1000+(d1[7]-'0')*100+(d1[8]-'0')*10+(d1[9]-'0');
                int y2=(d2[6]-'0')*1000+(d2[7]-'0')*100+(d2[8]-'0')*10+(d2[9]-'0');
                int m1=(d1[3]-'0')*10+(d1[4]-'0'), m2=(d2[3]-'0')*10+(d2[4]-'0');
                int day1=(d1[0]-'0')*10+(d1[1]-'0'), day2=(d2[0]-'0')*10+(d2[1]-'0');
                bool sw = (y1>y2)||(y1==y2&&m1>m2)||(y1==y2&&m1==m2&&day1>day2);
                if (sw) { int tmp=indices[j]; indices[j]=indices[j+1]; indices[j+1]=tmp; }
            }
        }
 
        static char buf[2048]; int pos = 0;
        pos = write_str(buf, pos, "ID | Doctor           | Date       | Slot  | Status\n");
        pos = write_str(buf, pos, "----------------------------------------------------\n");
 
        for (int i = 0; i < count; i++) {
            Appointment* a = ptr_appts + indices[i];
            Doctor* ptr_d = HospitalSystem::instance().get_doctors().find(a->get_doctor_id());
            pos = write_int(buf, pos, a->get_id());
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
    PatientAppointmentScreen(const char* pid)
        : heading("My Appointments"),
          divider("===================="),
          appt_list(""),
          status_label(""),
          back_btn("Back", 100, 40)
    {
        safe_copy(patient_id, pid, sizeof(patient_id));
 
        heading.set_position(50, 20);
        divider.set_position(50, 48);
        appt_list.set_position(50, 80);
        status_label.set_position(50, 500);
        back_btn.set_position(50, 540);
 
        load();
 
        back_btn.set_on_click([this]() {
            int pid_int = 0;
            for (int i = 0; patient_id[i]; i++) pid_int = pid_int * 10 + (patient_id[i] - '0');
            Patient* ptr_p = HospitalSystem::instance().get_patients().find(pid_int);
            if (ptr_p != nullptr)
                UIManager::instance().set_screen(new PatientMenuScreen(patient_id, ptr_p->get_name(), ptr_p->get_balance()));
            else
                UIManager::instance().set_screen(new LoginScreen());
        });
    }
 
    void handle_event(sf::RenderWindow& window, const sf::Event& event) override {
        back_btn.handle_event(event, window);
    }
 
    void update() override {}
 
    void render(sf::RenderWindow& window) override {
        heading.render(window);
        divider.render(window);
        appt_list.render(window);
        status_label.render(window);
        back_btn.render(window);
    }
};