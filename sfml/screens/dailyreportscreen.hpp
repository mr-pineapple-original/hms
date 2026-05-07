#pragma once
#include "screen.hpp"
#include "../components/label.hpp"
#include "../components/color_label.hpp"
#include "../components/button.hpp"
#include "../components/ui_manager.hpp"

// ── DailyReportScreen ─────────────────────────────────────────────────────
// Generates a summary report for today:
//   - Total appointments (pending / completed / no-show / cancelled)
//   - Total revenue collected today (completed appointments)
//   - Total unpaid bills outstanding
//   - New patients registered today
// ─────────────────────────────────────────────────────────────────────────
class DailyReportScreen : public Screen {
private:
    Label      heading;
    Label      divider;
    Label      date_label;
    Label      appt_heading;
    Label      appt_stats;
    Label      revenue_heading;
    Label      revenue_stats;
    Label      bills_heading;
    Label      bills_stats;
    Label      patients_heading;
    Label      patients_stats;
    ColorLabel status_label;
    Button     back_btn;

    void load() {
        // TODO: get today's date via time()/strftime() → char date_buf[16]
        // TODO: scan appointments.txt and count by status for today's date
        // TODO: sum fees of completed appointments today → revenue
        // TODO: count unpaid bills in bills.txt
        // TODO: count patients registered today in patients.txt
        date_label.set_text     ("Report Date: DD-MM-YYYY  (stub)");

        appt_stats.set_text     ("  Pending   : --\n"
                                 "  Completed : --\n"
                                 "  No-Show   : --\n"
                                 "  Cancelled : --\n"
                                 "  Total     : --");

        revenue_stats.set_text  ("  PKR ----  (stub)");
        bills_stats.set_text    ("  Count: --   Total: PKR ----  (stub)");
        patients_stats.set_text ("  New registrations today: --  (stub)");
    }

public:
    DailyReportScreen()
        : heading("Daily Report"),
          divider("===================="),
          date_label(""),
          appt_heading("-- Appointments Today --"),
          appt_stats(""),
          revenue_heading("-- Revenue Collected Today --"),
          revenue_stats(""),
          bills_heading("-- Outstanding Unpaid Bills --"),
          bills_stats(""),
          patients_heading("-- New Patients Today --"),
          patients_stats(""),
          status_label(""),
          back_btn("Back", 100, 40)
    {
        heading.set_position        (50,  20);
        divider.set_position        (50,  48);
        date_label.set_position     (50,  78);

        appt_heading.set_position   (50, 115);
        appt_stats.set_position     (50, 140);

        revenue_heading.set_position(50, 285);
        revenue_stats.set_position  (50, 310);

        bills_heading.set_position  (50, 350);
        bills_stats.set_position    (50, 375);

        patients_heading.set_position(50, 415);
        patients_stats.set_position  (50, 440);

        status_label.set_position   (50, 490);
        back_btn.set_position       (50, 530);

        load();

        back_btn.set_on_click([this]() {
            // TODO: UIManager::instance().set_screen(new AdminMenuScreen());
        });
    }

    void handle_event(sf::RenderWindow& window, const sf::Event& event) override {
        back_btn.handle_event(event, window);
    }

    void update() override {}

    void render(sf::RenderWindow& window) override {
        heading.render(window);
        divider.render(window);
        date_label.render(window);
        appt_heading.render(window);
        appt_stats.render(window);
        revenue_heading.render(window);
        revenue_stats.render(window);
        bills_heading.render(window);
        bills_stats.render(window);
        patients_heading.render(window);
        patients_stats.render(window);
        status_label.render(window);
        back_btn.render(window);
    }
};
