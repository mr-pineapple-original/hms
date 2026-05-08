// #pragma once
// #include "screen.hpp"
// #include "../components/label.hpp"
// #include "../components/color_label.hpp"
// #include "../components/button.hpp"
// #include "../components/ui_manager.hpp"

// // ── UnpaidBillsScreen ─────────────────────────────────────────────────────
// // Shows all bills with status == "unpaid" and the running total.
// // ─────────────────────────────────────────────────────────────────────────
// class UnpaidBillsScreen : public Screen
// {
// private:
//     Label heading;
//     Label divider;
//     Label col_header;
//     Label bills_list;
//     Label total_label;
//     ColorLabel status_label;
//     Button back_btn;

//     void load()
//     {
//         // TODO: FileHandler::get_all_bills("bills.txt", arr, count)
//         // Filter: status == "unpaid"
//         // Sum amounts → update total_label
//         // Build display: BillID | PatientName | DoctorName | Amount (PKR) | Date
//         col_header.set_text("BillID | Patient         | Doctor          | Amount (PKR) | Date");
//         bills_list.set_text("----------------------------------------------------------------------\n"
//                             "(unpaid bills will load from backend)");
//         total_label.set_text("Total Unpaid: PKR ---- (stub)");
//     }

// public:
//     UnpaidBillsScreen()
//         : heading("Unpaid Bills"),
//           divider("===================="),
//           col_header(""),
//           bills_list(""),
//           total_label(""),
//           status_label(""),
//           back_btn("Back", 100, 40)
//     {
//         heading.set_position(50, 20);
//         divider.set_position(50, 48);
//         col_header.set_position(50, 80);
//         bills_list.set_position(50, 108);
//         total_label.set_position(50, 460);
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
//         bills_list.render(window);
//         total_label.render(window);
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

class UnpaidBillsScreen : public Screen {
private:
    Label heading, divider, col_header, bills_list, total_label;
    ColorLabel status_label;
    Button back_btn;

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

    void load() {
        Bill*    ptr_b     = HospitalSystem::instance().get_bills().get_data();
        int      bill_count = HospitalSystem::instance().get_bills().size();

        static char buf[4096]; int pos = 0;
        double total = 0.0;
        bool any = false;

        for (int i = 0; i < bill_count; i++) {
            if (!str_eq((const char*)(ptr_b + i)->get_status(), "unpaid")) continue;
            any = true;
            total += (ptr_b + i)->get_amount();
            Patient* ptr_p = HospitalSystem::instance().get_patients().find((ptr_b + i)->get_patient_id());
            char amt_buf[32]; double_to_char((ptr_b + i)->get_amount(), amt_buf);
            pos = write_int(buf, pos, (ptr_b + i)->get_id());
            pos = write_str(buf, pos, " | ");
            pos = write_str(buf, pos, ptr_p ? ptr_p->get_name() : "Unknown");
            pos = write_str(buf, pos, " | PKR ");
            pos = write_str(buf, pos, amt_buf);
            pos = write_str(buf, pos, " | ");
            pos = write_str(buf, pos, (ptr_b + i)->get_date());
            buf[pos++] = '\n';
        }
        buf[pos] = '\0';
        bills_list.set_text(any ? buf : "No unpaid bills.");

        static char tot_buf[64]; int tp = 0;
        tp = write_str(tot_buf, tp, "Total Unpaid: PKR ");
        char amt_buf[32]; double_to_char(total, amt_buf);
        tp = write_str(tot_buf, tp, amt_buf);
        tot_buf[tp] = '\0';
        total_label.set_text(tot_buf);
    }

public:
    UnpaidBillsScreen()
        : heading("Unpaid Bills"), divider("===================="),
          col_header("BillID | Patient         | Amount (PKR) | Date"),
          bills_list(""), total_label(""), status_label(""),
          back_btn("Back", 100, 40)
    {
        heading.set_position(50, 20);
        divider.set_position(50, 48);
        col_header.set_position(50, 80);
        bills_list.set_position(50, 108);
        total_label.set_position(50, 460);
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
        col_header.render(window); bills_list.render(window);
        total_label.render(window); status_label.render(window);
        back_btn.render(window);
    }
    void go_back();
};