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

// // ── ViewBillsScreen ───────────────────────────────────────────────────────
// // Shows all bills for this patient + total outstanding unpaid amount.
// // TODO: connect to FileHandler::get_bills_by_patient(...)
// // ─────────────────────────────────────────────────────────────────────────

// class ViewBillsScreen : public Screen
// {
// private:
//     char patient_id[64];

//     Label heading;
//     Label divider;
//     Label bills_list;
//     Label total_label;
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
//         // TODO: FileHandler::get_bills_by_patient(patient_id, "bills.txt", arr, count)
//         // Build display: Bill ID | Appt ID | Amount | Status | Date
//         // Sum unpaid amounts → update total_label
//         bills_list.set_text("BillID | ApptID | Amount (PKR) | Status  | Date\n"
//                             "------------------------------------------------\n"
//                             "(bills will load from backend)");
//         total_label.set_text("Total Outstanding: PKR ---- (stub)");
//     }

// public:
//     ViewBillsScreen(const char *pid)
//         : heading("My Bills"),
//           divider("===================="),
//           bills_list(""),
//           total_label(""),
//           status_label(""),
//           back_btn("Back", 100, 40)
//     {
//         safe_copy(patient_id, pid, sizeof(patient_id));

//         heading.set_position(50, 20);
//         divider.set_position(50, 48);
//         bills_list.set_position(50, 80);
//         total_label.set_position(50, 460);
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
//         bills_list.render(window);
//         total_label.render(window);
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
 
class ViewBillsScreen : public Screen {
private:
    char patient_id[64];
 
    Label      heading;
    Label      divider;
    Label      bills_list;
    Label      total_label;
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
 
        Bill* ptr_bills = HospitalSystem::instance().get_bills().get_data();
        int count = HospitalSystem::instance().get_bills().size();
 
        static char buf[2048]; int pos = 0;
        pos = write_str(buf, pos, "BillID | ApptID | Amount (PKR) | Status   | Date\n");
        pos = write_str(buf, pos, "-------------------------------------------------\n");
 
        bool any = false;
        double total_unpaid = 0.0;
 
        for (int i = 0; i < count; i++) {
            if ((ptr_bills + i)->get_patient_id() != pid_int) continue;
            any = true;
 
            pos = write_int(buf, pos, (ptr_bills + i)->get_id());
            pos = write_str(buf, pos, " | ");
            pos = write_int(buf, pos, (ptr_bills + i)->get_appointment_id());
            pos = write_str(buf, pos, " | ");
            pos = write_int(buf, pos, (int)(ptr_bills + i)->get_amount());
            pos = write_str(buf, pos, " | ");
            pos = write_str(buf, pos, (const char*)(ptr_bills + i)->get_status());
            pos = write_str(buf, pos, " | ");
            pos = write_str(buf, pos, (ptr_bills + i)->get_date());
            buf[pos++] = '\n';
 
            if (char_eq((const char*)(ptr_bills + i)->get_status(), "unpaid"))
                total_unpaid += (ptr_bills + i)->get_amount();
        }
        buf[pos] = '\0';
 
        if (!any) {
            bills_list.set_text("No bills found.");
            total_label.set_text("");
            return;
        }
 
        bills_list.set_text(buf);
 
        // Build total label
        static char total_buf[64];
        int tp = 0;
        const char* prefix = "Total Outstanding: PKR ";
        for (int i = 0; prefix[i]; i++) total_buf[tp++] = prefix[i];
        // Write integer part of total
        int ti_val = (int)total_unpaid;
        char tmp[16]; int ti = 0;
        if (ti_val == 0) { tmp[ti++] = '0'; }
        else { int n = ti_val; char r[16]; int ri = 0; while(n>0){r[ri++]='0'+n%10;n/=10;} while(ri>0)tmp[ti++]=r[--ri]; }
        for (int i = 0; i < ti; i++) total_buf[tp++] = tmp[i];
        total_buf[tp] = '\0';
        total_label.set_text(total_buf);
    }
 
public:
    ViewBillsScreen(const char* pid)
        : heading("My Bills"),
          divider("===================="),
          bills_list(""),
          total_label(""),
          status_label(""),
          back_btn("Back", 100, 40)
    {
        safe_copy(patient_id, pid, sizeof(patient_id));
 
        heading.set_position(50, 20);
        divider.set_position(50, 48);
        bills_list.set_position(50, 80);
        total_label.set_position(50, 460);
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
        bills_list.render(window);
        total_label.render(window);
        status_label.render(window);
        back_btn.render(window);
    }
};