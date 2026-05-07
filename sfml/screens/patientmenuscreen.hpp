#pragma once
#include "screen.hpp"
#include "../components/label.hpp"
#include "../components/button.hpp"
#include "../components/ui_manager.hpp"
#include "../src/hospital_system.hpp"

// ── PatientMenuScreen ─────────────────────────────────────────────────────
// Main hub shown after a patient logs in successfully.
// Displays name + balance, and routes to each sub-screen.
// patient_id is stored as a char array (no std::string per project rules).
// ─────────────────────────────────────────────────────────────────────────

class PatientMenuScreen : public Screen {
private:
    char patient_id[64];

    // Header labels
    Label welcome_label;
    Label balance_label;
    Label divider_label;

    // 8 menu buttons
    Button book_btn;
    Button cancel_btn;
    Button view_appt_btn;
    Button records_btn;
    Button bills_btn;
    Button pay_btn;
    Button topup_btn;
    Button logout_btn;

    // Status / feedback label at the bottom
    Label status_label;

    void refresh_balance_label();   // re-reads balance from file and updates label

public:
    // Pass the patient's ID string; screen loads name + balance from file
    PatientMenuScreen(const char* id, const char* name, double balance);

    void handle_event(sf::RenderWindow& window, const sf::Event& event) override;
    void update() override;
    void render(sf::RenderWindow& window) override;
};
