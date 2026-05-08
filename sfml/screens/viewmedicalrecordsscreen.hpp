// #pragma once
// #include "screen.hpp"
// #include "patientmenuscreen.hpp"
// #include "loginscreen.hpp"
// #include "../components/label.hpp"
// #include "../components/color_label.hpp"
// #include "../components/button.hpp"
// #include "../components/ui_manager.hpp"
// #include "../../src/hospital_system.hpp"
// #include "../../src/patient.hpp"

// // ── ViewRecordsScreen ─────────────────────────────────────────────────────
// // Shows all prescriptions for this patient grouped by appointment,
// // sorted by date descending.
// // TODO: connect to FileHandler::get_prescriptions_by_patient(...)
// // ─────────────────────────────────────────────────────────────────────────

// class ViewRecordsScreen : public Screen
// {
// private:
//     char patient_id[64];

//     Label heading;
//     Label divider;
//     Label records_list;
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
//         // TODO: FileHandler::get_prescriptions_by_patient(patient_id, "prescriptions.txt", arr, count)
//         // Sort by date descending (implement manually)
//         // Build display: Date | Doctor Name | Medicines | Notes
//         records_list.set_text("Date        | Doctor            | Medicines       | Notes\n"
//                               "----------------------------------------------------------\n"
//                               "(medical records will load from backend)");
//     }

// public:
//     ViewRecordsScreen(const char *pid)
//         : heading("My Medical Records"),
//           divider("===================="),
//           records_list(""),
//           status_label(""),
//           back_btn("Back", 100, 40)
//     {
//         safe_copy(patient_id, pid, sizeof(patient_id));

//         heading.set_position(50, 20);
//         divider.set_position(50, 48);
//         records_list.set_position(50, 80);
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
//         records_list.render(window);
//         status_label.render(window);
//         back_btn.render(window);
//     }
// };


#pragma once
#include "screen.hpp"
#include "patientmenuscreen.hpp"
#include "loginscreen.hpp"
#include "../components/label.hpp"
#include "../components/color_label.hpp"
#include "../components/button.hpp"
#include "../components/ui_manager.hpp"
#include "../../src/hospital_system.hpp"
#include "../../src/patient.hpp"
 
class ViewRecordsScreen : public Screen {
private:
    char patient_id[64];
 
    Label      heading;
    Label      divider;
    Label      records_list;
    ColorLabel status_label;
    Button     back_btn;
 
    static void safe_copy(char* dst, const char* src, std::size_t max) {
        std::size_t i = 0;
        while (i < max - 1 && src[i]) { dst[i] = src[i]; ++i; }
        dst[i] = '\0';
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
 
        Prescription* ptr_rx = HospitalSystem::instance().get_prescriptions().get_data();
        int total = HospitalSystem::instance().get_prescriptions().size();
 
        int indices[100]; int count = 0;
        for (int i = 0; i < total && count < 100; i++)
            if ((ptr_rx + i)->get_patient_id() == pid_int)
                indices[count++] = i;
 
        if (count == 0) { records_list.set_text("No medical records found."); return; }
 
        // Bubble sort descending by date
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
 
        static char buf[2048]; int pos = 0;
        pos = write_str(buf, pos, "Date       | Doctor          | Medicines         | Notes\n");
        pos = write_str(buf, pos, "---------------------------------------------------------\n");
 
        for (int i = 0; i < count; i++) {
            Prescription* rx = ptr_rx + indices[i];
            Doctor* ptr_d = HospitalSystem::instance().get_doctors().find(rx->get_doctor_id());
            pos = write_str(buf, pos, rx->get_date());
            pos = write_str(buf, pos, " | ");
            pos = write_str(buf, pos, ptr_d ? ptr_d->get_name() : "Unknown");
            pos = write_str(buf, pos, " | ");
            pos = write_str(buf, pos, rx->get_medicine());
            pos = write_str(buf, pos, " | ");
            pos = write_str(buf, pos, rx->get_doctor_note());
            buf[pos++] = '\n';
        }
        buf[pos] = '\0';
        records_list.set_text(buf);
    }
 
public:
    ViewRecordsScreen(const char* pid)
        : heading("My Medical Records"),
          divider("===================="),
          records_list(""),
          status_label(""),
          back_btn("Back", 100, 40)
    {
        safe_copy(patient_id, pid, sizeof(patient_id));
 
        heading.set_position(50, 20);
        divider.set_position(50, 48);
        records_list.set_position(50, 80);
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
        records_list.render(window);
        status_label.render(window);
        back_btn.render(window);
    }
};