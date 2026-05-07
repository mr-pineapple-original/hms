#pragma once
#include "screen.hpp"
#include "../components/label.hpp"
#include "../components/button.hpp"
#include "../components/ui_manager.hpp"
#include "adddoctorscreen.hpp"
#include "viewpatientsscreen.hpp"
#include "dailyreportscreen.hpp"

// ── AdminMenuScreen ───────────────────────────────────────────────────────
// Main hub shown after admin logs in successfully.
// Routes to all 10 admin sub-screens.
// ─────────────────────────────────────────────────────────────────────────

class AdminMenuScreen : public Screen {
private:
    // Header
    Label heading_label;
    Label divider_label;

    // 10 menu buttons — split into two columns of 5 for better layout
    Button add_doctor_btn;
    Button remove_doctor_btn;
    Button view_patients_btn;
    Button view_doctors_btn;
    Button view_appts_btn;
    Button unpaid_bills_btn;
    Button discharge_btn;
    Button security_log_btn;
    Button daily_report_btn;
    Button logout_btn;

    // Feedback label
    Label status_label;

public:
    AdminMenuScreen();

    void handle_event(sf::RenderWindow& window, const sf::Event& event) override;
    void update() override;
    void render(sf::RenderWindow& window) override;
};
