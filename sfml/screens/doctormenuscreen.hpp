#pragma once
#include "screen.hpp"
#include "../components/label.hpp"
#include "../components/button.hpp"
#include "../components/ui_manager.hpp"

// ── DoctorMenuScreen ──────────────────────────────────────────────────────
// Main hub shown after a doctor logs in successfully.
// Shows name + specialization in the header, routes to 6 sub-screens.
// ─────────────────────────────────────────────────────────────────────────

class DoctorMenuScreen : public Screen {
private:
    char doctor_id[64];

    // Header
    Label welcome_label;      // "Welcome, Dr. [Name] | Specialization: [spec]"
    Label divider_label;

    // 6 menu buttons
    Button today_appt_btn;
    Button complete_btn;
    Button noshow_btn;
    Button prescription_btn;
    Button history_btn;
    Button logout_btn;

    // Feedback label
    Label status_label;

public:
    DoctorMenuScreen(const char* id);

    void handle_event(sf::RenderWindow& window, const sf::Event& event) override;
    void update() override;
    void render(sf::RenderWindow& window) override;
};
