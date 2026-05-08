// #pragma once
// #include "screen.hpp"
// #include "../components/label.hpp"
// #include "../components/color_label.hpp"
// #include "../components/button.hpp"
// #include "../components/ui_manager.hpp"

// // ── DailyReportScreen ─────────────────────────────────────────────────────
// // Generates a summary report for today:
// //   - Total appointments (pending / completed / no-show / cancelled)
// //   - Total revenue collected today (completed appointments)
// //   - Total unpaid bills outstanding
// //   - New patients registered today
// // ─────────────────────────────────────────────────────────────────────────
// class DailyReportScreen : public Screen
// {
// private:
//     Label heading;
//     Label divider;
//     Label date_label;
//     Label appt_heading;
//     Label appt_stats;
//     Label revenue_heading;
//     Label revenue_stats;
//     Label bills_heading;
//     Label bills_stats;
//     Label patients_heading;
//     Label patients_stats;
//     ColorLabel status_label;
//     Button back_btn;

//     void load()
//     {
//         // TODO: get today's date via time()/strftime() → char date_buf[16]
//         // TODO: scan appointments.txt and count by status for today's date
//         // TODO: sum fees of completed appointments today → revenue
//         // TODO: count unpaid bills in bills.txt
//         // TODO: count patients registered today in patients.txt
//         date_label.set_text("Report Date: DD-MM-YYYY  (stub)");

//         appt_stats.set_text("  Pending   : --\n"
//                             "  Completed : --\n"
//                             "  No-Show   : --\n"
//                             "  Cancelled : --\n"
//                             "  Total     : --");

//         revenue_stats.set_text("  PKR ----  (stub)");
//         bills_stats.set_text("  Count: --   Total: PKR ----  (stub)");
//         patients_stats.set_text("  New registrations today: --  (stub)");
//     }

// public:
//     DailyReportScreen()
//         : heading("Daily Report"),
//           divider("===================="),
//           date_label(""),
//           appt_heading("-- Appointments Today --"),
//           appt_stats(""),
//           revenue_heading("-- Revenue Collected Today --"),
//           revenue_stats(""),
//           bills_heading("-- Outstanding Unpaid Bills --"),
//           bills_stats(""),
//           patients_heading("-- New Patients Today --"),
//           patients_stats(""),
//           status_label(""),
//           back_btn("Back", 100, 40)
//     {
//         heading.set_position(50, 20);
//         divider.set_position(50, 48);
//         date_label.set_position(50, 78);

//         appt_heading.set_position(50, 115);
//         appt_stats.set_position(50, 140);

//         revenue_heading.set_position(50, 285);
//         revenue_stats.set_position(50, 310);

//         bills_heading.set_position(50, 350);
//         bills_stats.set_position(50, 375);

//         patients_heading.set_position(50, 415);
//         patients_stats.set_position(50, 440);

//         status_label.set_position(50, 490);
//         back_btn.set_position(50, 530);

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
//         date_label.render(window);
//         appt_heading.render(window);
//         appt_stats.render(window);
//         revenue_heading.render(window);
//         revenue_stats.render(window);
//         bills_heading.render(window);
//         bills_stats.render(window);
//         patients_heading.render(window);
//         patients_stats.render(window);
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

class DailyReportScreen : public Screen {
private:
    Label heading, divider, date_label;
    Label appt_heading, appt_stats;
    Label revenue_heading, revenue_stats;
    Label bills_heading, bills_stats;
    Label patients_heading, patients_stats;
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
        char today[11];
        HospitalSystem::instance().get_today_date(today);

        static char date_buf[32]; int dp = 0;
        dp = write_str(date_buf, dp, "Report Date: ");
        dp = write_str(date_buf, dp, today);
        date_buf[dp] = '\0';
        date_label.set_text(date_buf);

        // Appointment counts for today
        int pending=0, completed=0, noshow=0, cancelled=0;
        Appointment* ptr_a = HospitalSystem::instance().get_appointments().get_data();
        int appt_total = HospitalSystem::instance().get_appointments().size();
        for (int i = 0; i < appt_total; i++) {
            if (!str_eq((ptr_a + i)->get_date(), today)) continue;
            const char* st = (const char*)(ptr_a + i)->get_status();
            if      (str_eq(st, "pending"))   pending++;
            else if (str_eq(st, "completed")) completed++;
            else if (str_eq(st, "no-show"))   noshow++;
            else if (str_eq(st, "cancelled")) cancelled++;
        }

        static char appt_buf[256]; int ap = 0;
        ap = write_str(appt_buf, ap, "  Pending   : "); ap = write_int(appt_buf, ap, pending);
        ap = write_str(appt_buf, ap, "\n  Completed : "); ap = write_int(appt_buf, ap, completed);
        ap = write_str(appt_buf, ap, "\n  No-Show   : "); ap = write_int(appt_buf, ap, noshow);
        ap = write_str(appt_buf, ap, "\n  Cancelled : "); ap = write_int(appt_buf, ap, cancelled);
        ap = write_str(appt_buf, ap, "\n  Total     : ");
        ap = write_int(appt_buf, ap, pending + completed + noshow + cancelled);
        appt_buf[ap] = '\0';
        appt_stats.set_text(appt_buf);

        // Revenue: paid bills today
        double revenue = 0.0;
        Bill* ptr_b = HospitalSystem::instance().get_bills().get_data();
        int bill_total = HospitalSystem::instance().get_bills().size();
        for (int i = 0; i < bill_total; i++) {
            if (str_eq((ptr_b + i)->get_date(), today) &&
                str_eq((const char*)(ptr_b + i)->get_status(), "paid"))
                revenue += (ptr_b + i)->get_amount();
        }
        static char rev_buf[64]; int rp = 0;
        char rev_amt[32]; double_to_char(revenue, rev_amt);
        rp = write_str(rev_buf, rp, "  PKR "); rp = write_str(rev_buf, rp, rev_amt);
        rev_buf[rp] = '\0';
        revenue_stats.set_text(rev_buf);

        // Unpaid bills (all time)
        int unpaid_count = 0; double unpaid_total = 0.0;
        for (int i = 0; i < bill_total; i++) {
            if (str_eq((const char*)(ptr_b + i)->get_status(), "unpaid")) {
                unpaid_count++;
                unpaid_total += (ptr_b + i)->get_amount();
            }
        }
        static char bill_buf[64]; int bp = 0;
        char unpaid_amt[32]; double_to_char(unpaid_total, unpaid_amt);
        bp = write_str(bill_buf, bp, "  Count: "); bp = write_int(bill_buf, bp, unpaid_count);
        bp = write_str(bill_buf, bp, "   Total: PKR "); bp = write_str(bill_buf, bp, unpaid_amt);
        bill_buf[bp] = '\0';
        bills_stats.set_text(bill_buf);

        // Total registered patients (no registration date in model)
        static char pat_buf[64]; int pp = 0;
        pp = write_str(pat_buf, pp, "  Total registered: ");
        pp = write_int(pat_buf, pp, HospitalSystem::instance().get_patients().size());
        pat_buf[pp] = '\0';
        patients_stats.set_text(pat_buf);
    }

public:
    DailyReportScreen()
        : heading("Daily Report"), divider("===================="),
          date_label(""), appt_heading("-- Appointments Today --"), appt_stats(""),
          revenue_heading("-- Revenue Collected Today --"), revenue_stats(""),
          bills_heading("-- Outstanding Unpaid Bills --"), bills_stats(""),
          patients_heading("-- Registered Patients --"), patients_stats(""),
          status_label(""), back_btn("Back", 100, 40)
    {
        heading.set_position(50, 20);
        divider.set_position(50, 48);
        date_label.set_position(50, 78);
        appt_heading.set_position(50, 115);   appt_stats.set_position(50, 140);
        revenue_heading.set_position(50, 285); revenue_stats.set_position(50, 310);
        bills_heading.set_position(50, 350);   bills_stats.set_position(50, 375);
        patients_heading.set_position(50, 415); patients_stats.set_position(50, 440);
        status_label.set_position(50, 490);
        back_btn.set_position(50, 530);
        load();
        back_btn.set_on_click([this]() { go_back(); });
    }

    void handle_event(sf::RenderWindow& window, const sf::Event& event) override {
        back_btn.handle_event(event, window);
    }
    void update() override {}
    void render(sf::RenderWindow& window) override {
        heading.render(window); divider.render(window); date_label.render(window);
        appt_heading.render(window); appt_stats.render(window);
        revenue_heading.render(window); revenue_stats.render(window);
        bills_heading.render(window); bills_stats.render(window);
        patients_heading.render(window); patients_stats.render(window);
        status_label.render(window); back_btn.render(window);
    }
    void go_back();
};