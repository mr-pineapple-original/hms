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

// // ── PayBillsScreen ───────────────────────────────────────────────────────
// // Shows all bills for this patient + total outstanding unpaid amount.
// // TODO: connect to FileHandler::get_bills_by_patient(...)
// // ─────────────────────────────────────────────────────────────────────────
 
// class PayBillsScreen : public Screen {
// private:
//     char patient_id[64];
 
//     Label      heading;
//     Label      divider;
//     Label      bills_list;
//     Label      total_label;
//     ColorLabel status_label;
//     Button     back_btn;
 
//     static void safe_copy(char* dst, const char* src, std::size_t max) {
//         std::size_t i = 0;
//         while (i < max - 1 && src[i] != '\0') { dst[i] = src[i]; ++i; }
//         dst[i] = '\0';
//     }
 
//     void load() {
//         // TODO: FileHandler::get_bills_by_patient(patient_id, "bills.txt", arr, count)
//         // Build display: Bill ID | Appt ID | Amount | Status | Date
//         // Sum unpaid amounts → update total_label
//         bills_list.set_text("BillID | ApptID | Amount (PKR) | Status  | Date\n"
//                             "------------------------------------------------\n"
//                             "(bills will load from backend)");
//         total_label.set_text("Total Outstanding: PKR ---- (stub)");
//     }
 
// public:
//     PayBillsScreen(const char* pid)
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
 
//         back_btn.set_on_click([this]() {
//             // We need to reload patient data to get updated balance
//         int pid = 0;
//         for (int i = 0; patient_id[i] != '\0'; i++)
//         pid = pid * 10 + (patient_id[i] - '0');

//     Patient* ptr_p = HospitalSystem::instance().get_patients().find(pid);
//     if (ptr_p != nullptr)
//         UIManager::instance().set_screen(
//             new PatientMenuScreen(patient_id,
//                                   ptr_p->get_name(),
//                                   ptr_p->get_balance()));
//     else
//         UIManager::instance().set_screen(new LoginScreen());
//         });
//     }
 
//     void handle_event(sf::RenderWindow& window, const sf::Event& event) override {
//         back_btn.handle_event(event, window);
//     }
 
//     void update() override {}
 
//     void render(sf::RenderWindow& window) override {
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
#include "../components/text_field.hpp"
#include "../components/ui_manager.hpp"
#include "patientmenuscreen.hpp"
#include "loginscreen.hpp"
#include "../../src/hospital_system.hpp"
#include "../../src/patient.hpp"
#include "../../src/file_handler.hpp"
 
class PayBillsScreen : public Screen {
private:
    char patient_id[64];
 
    Label      heading;
    Label      divider;
    Label      bills_list;       // shows unpaid bills
    Label      bill_id_label;
    TextField  bill_id_field;
    Button     pay_btn;
    Button     back_btn;
    ColorLabel status_label;
 
    static void safe_copy(char* dst, const char* src, std::size_t max) {
        std::size_t i = 0;
        while (i < max - 1 && src[i] != '\0') { dst[i] = src[i]; ++i; }
        dst[i] = '\0';
    }
 
    static bool char_eq(const char* a, const char* b) {
        int i = 0;
        while (a[i] != '\0' && b[i] != '\0') { if (a[i] != b[i]) return false; i++; }
        return a[i] == '\0' && b[i] == '\0';
    }
 
    void load_unpaid_bills() {
        int pid_int = 0;
        for (int i = 0; patient_id[i] != '\0'; i++)
            pid_int = pid_int * 10 + (patient_id[i] - '0');
 
        Bill* ptr_bills = HospitalSystem::instance().get_bills().get_data();
        int count = HospitalSystem::instance().get_bills().size();
 
        static char buf[1024];
        int pos = 0;
        const char* header = "BillID | ApptID | Amount (PKR) | Date\n--------------------------------------\n";
        for (int i = 0; header[i] != '\0'; i++) buf[pos++] = header[i];
 
        bool any = false;
        for (int i = 0; i < count; i++) {
            if ((ptr_bills + i)->get_patient_id() != pid_int) continue;
            if (!char_eq((const char*)(ptr_bills + i)->get_status(), "unpaid")) continue;
            any = true;
 
            // Write bill ID
            int id = (ptr_bills + i)->get_id();
            char tmp[16]; int ti = 0;
            if (id == 0) tmp[ti++] = '0';
            else { int n = id; char r[16]; int ri = 0; while(n>0){r[ri++]='0'+n%10;n/=10;} while(ri>0)tmp[ti++]=r[--ri]; }
            tmp[ti] = '\0';
            for (int j = 0; tmp[j] && pos < 1020; j++) buf[pos++] = tmp[j];
            buf[pos++] = ' '; buf[pos++] = '|'; buf[pos++] = ' ';
 
            // Write appt ID
            int aid = (ptr_bills + i)->get_appointment_id();
            ti = 0;
            if (aid == 0) tmp[ti++] = '0';
            else { int n = aid; char r[16]; int ri = 0; while(n>0){r[ri++]='0'+n%10;n/=10;} while(ri>0)tmp[ti++]=r[--ri]; }
            tmp[ti] = '\0';
            for (int j = 0; tmp[j] && pos < 1020; j++) buf[pos++] = tmp[j];
            buf[pos++] = ' '; buf[pos++] = '|'; buf[pos++] = ' ';
 
            // Write amount (integer part)
            int amt = (int)(ptr_bills + i)->get_amount();
            ti = 0;
            if (amt == 0) tmp[ti++] = '0';
            else { int n = amt; char r[16]; int ri = 0; while(n>0){r[ri++]='0'+n%10;n/=10;} while(ri>0)tmp[ti++]=r[--ri]; }
            tmp[ti] = '\0';
            for (int j = 0; tmp[j] && pos < 1020; j++) buf[pos++] = tmp[j];
            buf[pos++] = ' '; buf[pos++] = '|'; buf[pos++] = ' ';
 
            // Write date
            char* dt = (ptr_bills + i)->get_date();
            for (int j = 0; dt[j] && pos < 1020; j++) buf[pos++] = dt[j];
            buf[pos++] = '\n';
        }
        buf[pos] = '\0';
 
        if (!any)
            bills_list.set_text("No unpaid bills.");
        else
            bills_list.set_text(buf);
    }
 
public:
    PayBillsScreen(const char* pid)
        : heading("Pay Bill"),
          divider("===================="),
          bills_list(""),
          bill_id_label("Bill ID to pay:"),
          pay_btn("Pay Bill", 120, 40),
          back_btn("Back", 100, 40),
          status_label("")
    {
        safe_copy(patient_id, pid, sizeof(patient_id));
 
        heading.set_position(50, 20);
        divider.set_position(50, 48);
        bills_list.set_position(50, 80);
        bill_id_label.set_position(50, 340);
        bill_id_field.set_position(210, 330);
        pay_btn.set_position(180, 400);
        back_btn.set_position(320, 400);
        status_label.set_position(50, 460);
 
        load_unpaid_bills();
 
        pay_btn.set_on_click([this]() {
            if (bill_id_field.get_text().isEmpty()) {
                status_label.set_color(sf::Color::Red);
                status_label.set_text("Please enter a Bill ID.");
                return;
            }
 
            // Parse bill ID
            char bill_buf[32];
            sf::String s = bill_id_field.get_text();
            std::size_t len = s.getSize() < 31 ? s.getSize() : 31;
            for (std::size_t i = 0; i < len; ++i) bill_buf[i] = (char)s[i];
            bill_buf[len] = '\0';
 
            int bill_id = 0;
            for (int i = 0; bill_buf[i] != '\0'; i++)
                bill_id = bill_id * 10 + (bill_buf[i] - '0');
 
            // Parse patient ID
            int pid_int = 0;
            for (int i = 0; patient_id[i] != '\0'; i++)
                pid_int = pid_int * 10 + (patient_id[i] - '0');
 
            Bill* ptr_bill = HospitalSystem::instance().get_bills().find(bill_id);
 
            if (ptr_bill == nullptr ||
                ptr_bill->get_patient_id() != pid_int ||
                !char_eq((const char*)ptr_bill->get_status(), "unpaid")) {
                status_label.set_color(sf::Color::Red);
                status_label.set_text("Invalid Bill ID.");
                return;
            }
 
            Patient* ptr_p = HospitalSystem::instance().get_patients().find(pid_int);
            if (ptr_p == nullptr) {
                status_label.set_color(sf::Color::Red);
                status_label.set_text("Patient not found.");
                return;
            }
 
            if (ptr_p->get_balance() < ptr_bill->get_amount()) {
                status_label.set_color(sf::Color::Red);
                status_label.set_text("Insufficient balance.");
                return;
            }
 
            // Deduct using -= operator
            *ptr_p -= ptr_bill->get_amount();
 
            // Mark bill as paid
            char paid[] = "paid";
            ptr_bill->set_bill(ptr_bill->get_id(), ptr_bill->get_patient_id(),
                               ptr_bill->get_appointment_id(), ptr_bill->get_amount(),
                               paid, ptr_bill->get_date());
 
            FileHandler::update_bills(HospitalSystem::instance().get_bills(), "bills.txt");
            FileHandler::update_patients(HospitalSystem::instance().get_patients(), "patients.txt");
 
            status_label.set_color(sf::Color::Green);
            status_label.set_text("Bill paid successfully!");
            bill_id_field.clear();
            load_unpaid_bills();
        });
 
        back_btn.set_on_click([this]() {
            int pid_int = 0;
            for (int i = 0; patient_id[i] != '\0'; i++)
                pid_int = pid_int * 10 + (patient_id[i] - '0');
            Patient* ptr_p = HospitalSystem::instance().get_patients().find(pid_int);
            if (ptr_p != nullptr)
                UIManager::instance().set_screen(
                    new PatientMenuScreen(patient_id, ptr_p->get_name(), ptr_p->get_balance()));
            else
                UIManager::instance().set_screen(new LoginScreen());
        });
    }
 
    void handle_event(sf::RenderWindow& window, const sf::Event& event) override {
        bill_id_field.handle_event(event, window);
        pay_btn.handle_event(event, window);
        back_btn.handle_event(event, window);
    }
 
    void update() override {}
 
    void render(sf::RenderWindow& window) override {
        heading.render(window);
        divider.render(window);
        bills_list.render(window);
        bill_id_label.render(window);
        bill_id_field.render(window);
        pay_btn.render(window);
        back_btn.render(window);
        status_label.render(window);
    }
};