#pragma once
#include "screen.hpp"
#include "../components/label.hpp"
#include "../components/color_label.hpp"
#include "../components/button.hpp"
#include "../components/text_field.hpp"
#include "../components/ui_manager.hpp"
 
// ── TopUpScreen ───────────────────────────────────────────────────────────
// Patient enters amount to add to balance.
// Uses overloaded += on Patient. Up to 3 invalid attempts before back.
// TODO: connect to FileHandler
// ─────────────────────────────────────────────────────────────────────────
 
class TopUpScreen : public Screen {
private:
    char patient_id[64];
    int  bad_attempts = 0;
 
    Label      heading;
    Label      divider;
    Label      balance_label;
    Label      amount_label;
    TextField  amount_field;
    Button     topup_btn;
    Button     back_btn;
    ColorLabel status_label;
 
    static void safe_copy(char* dst, const char* src, std::size_t max) {
        std::size_t i = 0;
        while (i < max - 1 && src[i] != '\0') { dst[i] = src[i]; ++i; }
        dst[i] = '\0';
    }
 
public:
    TopUpScreen(const char* pid)
        : heading("Top Up Balance"),
          divider("===================="),
          balance_label("Current Balance: PKR ---- (stub)"),
          amount_label("Amount to add (PKR):"),
          topup_btn("Top Up", 120, 40),
          back_btn("Back", 100, 40),
          status_label("")
    {
        safe_copy(patient_id, pid, sizeof(patient_id));
 
        heading.set_position(50, 20);
        divider.set_position(50, 48);
        balance_label.set_position(50, 90);
 
        amount_label.set_position(50, 180);
        amount_field.set_position(280, 170);
 
        topup_btn.set_position(180, 240);
        back_btn.set_position(320, 240);
        status_label.set_position(50, 305);
 
        // TODO: load real balance
        // Patient* p = FileHandler::load_patient(patient_id, "patients.txt");
        // balance_label.set_text("Current Balance: PKR " + float_to_str(p->balance));
 
        topup_btn.set_on_click([this]() {
            if (amount_field.get_text().isEmpty()) {
                status_label.set_color(sf::Color::Red);
                status_label.set_text("Please enter an amount.");
                bad_attempts++;
                if (bad_attempts >= 3) {
                    // TODO: UIManager::instance().set_screen(new PatientMenuScreen(patient_id));
                }
                return;
            }
            // TODO: parse amount as float
            // if amount <= 0 → throw InvalidInputException, bad_attempts++, if >= 3 go back
            // patient += amount  (overloaded +=)
            // FileHandler::update_patient_balance(patient_id, new_balance, "patients.txt")
            // refresh balance_label
            bad_attempts = 0;
            status_label.set_color(sf::Color::Green);
            status_label.set_text("Balance updated. New balance: PKR ---- (stub)");
            amount_field.clear();
        });
 
        back_btn.set_on_click([this]() {
            // TODO: UIManager::instance().set_screen(new PatientMenuScreen(patient_id));
        });
    }
 
    void handle_event(sf::RenderWindow& window, const sf::Event& event) override {
        amount_field.handle_event(event, window);
        topup_btn.handle_event(event, window);
        back_btn.handle_event(event, window);
    }
 
    void update() override {}
 
    void render(sf::RenderWindow& window) override {
        heading.render(window);
        divider.render(window);
        balance_label.render(window);
        amount_label.render(window);
        amount_field.render(window);
        topup_btn.render(window);
        back_btn.render(window);
        status_label.render(window);
    }
};