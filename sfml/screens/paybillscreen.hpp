#pragma once
#include "screen.hpp"
#include "../components/label.hpp"
#include "../components/color_label.hpp"
#include "../components/button.hpp"
#include "../components/ui_manager.hpp"
 
// ── ViewBillsScreen ───────────────────────────────────────────────────────
// Shows all bills for this patient + total outstanding unpaid amount.
// TODO: connect to FileHandler::get_bills_by_patient(...)
// ─────────────────────────────────────────────────────────────────────────
 
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
        while (i < max - 1 && src[i] != '\0') { dst[i] = src[i]; ++i; }
        dst[i] = '\0';
    }
 
    void load() {
        // TODO: FileHandler::get_bills_by_patient(patient_id, "bills.txt", arr, count)
        // Build display: Bill ID | Appt ID | Amount | Status | Date
        // Sum unpaid amounts → update total_label
        bills_list.set_text("BillID | ApptID | Amount (PKR) | Status  | Date\n"
                            "------------------------------------------------\n"
                            "(bills will load from backend)");
        total_label.set_text("Total Outstanding: PKR ---- (stub)");
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
            // TODO: UIManager::instance().set_screen(new PatientMenuScreen(patient_id));
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