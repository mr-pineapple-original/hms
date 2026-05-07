#pragma once
#include "screen.hpp"
#include "../components/label.hpp"
#include "../components/color_label.hpp"
#include "../components/button.hpp"
#include "../components/ui_manager.hpp"

// ── UnpaidBillsScreen ─────────────────────────────────────────────────────
// Shows all bills with status == "unpaid" and the running total.
// ─────────────────────────────────────────────────────────────────────────
class UnpaidBillsScreen : public Screen {
private:
    Label      heading;
    Label      divider;
    Label      col_header;
    Label      bills_list;
    Label      total_label;
    ColorLabel status_label;
    Button     back_btn;

    void load() {
        // TODO: FileHandler::get_all_bills("bills.txt", arr, count)
        // Filter: status == "unpaid"
        // Sum amounts → update total_label
        // Build display: BillID | PatientName | DoctorName | Amount (PKR) | Date
        col_header.set_text("BillID | Patient         | Doctor          | Amount (PKR) | Date");
        bills_list.set_text("----------------------------------------------------------------------\n"
                            "(unpaid bills will load from backend)");
        total_label.set_text("Total Unpaid: PKR ---- (stub)");
    }

public:
    UnpaidBillsScreen()
        : heading("Unpaid Bills"),
          divider("===================="),
          col_header(""),
          bills_list(""),
          total_label(""),
          status_label(""),
          back_btn("Back", 100, 40)
    {
        heading.set_position    (50,  20);
        divider.set_position    (50,  48);
        col_header.set_position (50,  80);
        bills_list.set_position (50, 108);
        total_label.set_position(50, 460);
        status_label.set_position(50, 500);
        back_btn.set_position   (50, 540);

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
        col_header.render(window);
        bills_list.render(window);
        total_label.render(window);
        status_label.render(window);
        back_btn.render(window);
    }
};
