#pragma once
#include "screen.hpp"
#include "../components/label.hpp"
#include "../components/color_label.hpp"
#include "../components/button.hpp"
#include "../components/text_field.hpp"
#include "../components/ui_manager.hpp"
#include "patientmenuscreen.hpp"
#include "loginscreen.hpp"
#include "../components/sf_string_utils.hpp"
#include "../../src/hospital_system.hpp"
#include "../../src/patient.hpp"
#include "../../src/file_handler.hpp"
#include "../../src/invalid_input_exception.hpp"

// ── TopUpScreen ───────────────────────────────────────────────────────────
// Patient enters amount to add to balance.
// Uses overloaded += on Patient. Up to 3 invalid attempts before back.
// TODO: connect to FileHandler
// ─────────────────────────────────────────────────────────────────────────

class TopUpScreen : public Screen
{
private:
    char patient_id[64];
    int bad_attempts = 0;

    Label heading;
    Label divider;
    Label balance_label;
    Label amount_label;
    TextField amount_field;
    Button topup_btn;
    Button back_btn;
    ColorLabel status_label;

    static void safe_copy(char *dst, const char *src, std::size_t max)
    {
        std::size_t i = 0;
        while (i < max - 1 && src[i] != '\0')
        {
            dst[i] = src[i];
            ++i;
        }
        dst[i] = '\0';
    }

public:
    TopUpScreen(const char *pid)
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

        int pid2 = 0;
        for (int i = 0; patient_id[i] != '\0'; i++)
            pid2 = pid2 * 10 + (patient_id[i] - '0');
        Patient *ptr_init = HospitalSystem::instance().get_patients().find(pid2);
        if (ptr_init != nullptr)
        {
            char bal_buf[64];
            const char *bp = "Current Balance: PKR ";
            int pos = 0;
            for (int i = 0; bp[i] != '\0'; i++)
                bal_buf[pos++] = bp[i];
            char nb[32];
            double_to_char(ptr_init->get_balance(), nb);
            for (int i = 0; nb[i] != '\0'; i++)
                bal_buf[pos++] = nb[i];
            bal_buf[pos] = '\0';
            balance_label.set_text(bal_buf);
        }

        topup_btn.set_on_click([this]()
                               {
    if (amount_field.get_text().isEmpty()) {
        status_label.set_color(sf::Color::Red);
        status_label.set_text("Please enter an amount.");
        bad_attempts++;
        if (bad_attempts >= 3) {
            int pid = 0;
            for (int i = 0; patient_id[i] != '\0'; i++)
                pid = pid * 10 + (patient_id[i] - '0');
            Patient* ptr_p = HospitalSystem::instance().get_patients().find(pid);
            if (ptr_p != nullptr)
                UIManager::instance().set_screen(new PatientMenuScreen(patient_id, ptr_p->get_name(), ptr_p->get_balance()));
            else
                UIManager::instance().set_screen(new LoginScreen());
        }
        return;
    }

    // Parse amount from field
    char amount_buf[32];
    sf_string_to_char(amount_field.get_text(), amount_buf, sizeof(amount_buf));

    // Parse to double manually
    double amount = 0.0;
    double factor = 1.0;
    bool decimal = false;
    bool valid = true;

    for (int i = 0; amount_buf[i] != '\0'; i++)
    {
        if (amount_buf[i] == '.')
        {
            decimal = true;
            factor = 0.1;
            continue;
        }
        if (amount_buf[i] < '0' || amount_buf[i] > '9')
        {
            valid = false;
            break;
        }
        if (!decimal)
            amount = amount * 10 + (amount_buf[i] - '0');
        else
        {
            amount += (amount_buf[i] - '0') * factor;
            factor *= 0.1;
        }
    }

    if (!valid || amount <= 0)
    {
        status_label.set_color(sf::Color::Red);
        status_label.set_text("Please enter a valid positive amount.");
        bad_attempts++;
        if (bad_attempts >= 3)
        {
            int pid = 0;
            for (int i = 0; patient_id[i] != '\0'; i++)
                pid = pid * 10 + (patient_id[i] - '0');
            Patient* ptr_p = HospitalSystem::instance().get_patients().find(pid);
            if (ptr_p != nullptr)
                UIManager::instance().set_screen(new PatientMenuScreen(patient_id, ptr_p->get_name(), ptr_p->get_balance()));
            else
                UIManager::instance().set_screen(new LoginScreen());
        }
        return;
    }

    // Find patient and top up using += operator
    int pid = 0;
    for (int i = 0; patient_id[i] != '\0'; i++)
        pid = pid * 10 + (patient_id[i] - '0');

    Patient* ptr_p = HospitalSystem::instance().get_patients().find(pid);
    if (ptr_p == nullptr)
    {
        status_label.set_color(sf::Color::Red);
        status_label.set_text("Patient not found.");
        return;
    }

    *ptr_p += amount;
    FileHandler::update_patients(HospitalSystem::instance().get_patients(), "patients.txt");

    // Update balance label
    char bal_buf[64];
    const char* prefix = "Current Balance: PKR ";
    int pos = 0;
    for (int i = 0; prefix[i] != '\0'; i++) bal_buf[pos++] = prefix[i];
    char num_buf[32];
    double_to_char(ptr_p->get_balance(), num_buf);
    for (int i = 0; num_buf[i] != '\0'; i++) bal_buf[pos++] = num_buf[i];
    bal_buf[pos] = '\0';
    balance_label.set_text(bal_buf);

    // Show success
    char success_buf[64];
    const char* s_prefix = "Balance updated. New balance: PKR ";
    pos = 0;
    for (int i = 0; s_prefix[i] != '\0'; i++) success_buf[pos++] = s_prefix[i];
    for (int i = 0; num_buf[i] != '\0'; i++) success_buf[pos++] = num_buf[i];
    success_buf[pos] = '\0';

    bad_attempts = 0;
    status_label.set_color(sf::Color::Green);
    status_label.set_text(success_buf);
    amount_field.clear(); });

        back_btn.set_on_click([this]()
                              {
    int pid = 0;
    for (int i = 0; patient_id[i] != '\0'; i++)
        pid = pid * 10 + (patient_id[i] - '0');
    Patient* ptr_p = HospitalSystem::instance().get_patients().find(pid);
    if (ptr_p != nullptr)
        UIManager::instance().set_screen(new PatientMenuScreen(patient_id, ptr_p->get_name(), ptr_p->get_balance()));
    else
        UIManager::instance().set_screen(new LoginScreen()); });
    }

    void handle_event(sf::RenderWindow &window, const sf::Event &event) override
    {
        amount_field.handle_event(event, window);
        topup_btn.handle_event(event, window);
        back_btn.handle_event(event, window);
    }

    void update() override {}

    void render(sf::RenderWindow &window) override
    {
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