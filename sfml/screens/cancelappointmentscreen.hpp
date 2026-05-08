#pragma once
#include "screen.hpp"
#include "../components/label.hpp"
#include "../components/color_label.hpp"
#include "../components/button.hpp"
#include "../components/text_field.hpp"
#include "../components/ui_manager.hpp"
#include "patientmenuscreen.hpp"
#include "loginscreen.hpp"
#include "../../src/hospital_system.hpp"
#include "../../src/patient.hpp"

// ── CancelAppointmentScreen ───────────────────────────────────────────────
// Shows patient's pending appointments, prompts for appointment ID to cancel.
// Refund is issued via overloaded += on Patient.
// ─────────────────────────────────────────────────────────────────────────

class CancelAppointmentScreen : public Screen
{
private:
    char patient_id[64];

    Label heading;
    Label divider;
    Label list_heading;
    Label appt_list; // pending appointments displayed here

    Label appt_id_label;
    TextField appt_id_field;

    Button cancel_btn;
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

    void load_pending_appointments()
    {
        // TODO: FileHandler::get_pending_appointments(patient_id, "appointments.txt", ...)
        // Build display string: "ID | Doctor Name | Date | Time Slot"
        appt_list.set_text("ID   Doctor Name            Date         Slot\n"
                           "---------------------------------------------\n"
                           "(pending appointments will load from backend)");
    }

public:
    CancelAppointmentScreen(const char *pid)
        : heading("Cancel Appointment"),
          divider("=============================="),
          list_heading("Your Pending Appointments:"),
          appt_list(""),
          appt_id_label("Appointment ID to cancel:"),
          cancel_btn("Cancel Appointment", 200, 40),
          back_btn("Back", 100, 40),
          status_label("")
    {
        safe_copy(patient_id, pid, sizeof(patient_id));

        heading.set_position(50, 20);
        divider.set_position(50, 48);
        list_heading.set_position(50, 85);
        appt_list.set_position(50, 115);

        appt_id_label.set_position(50, 280);
        appt_id_field.set_position(310, 270);

        cancel_btn.set_position(180, 340);
        back_btn.set_position(410, 340);

        status_label.set_position(50, 410);

        load_pending_appointments();

        cancel_btn.set_on_click([this]()
                                {
            sf::String id_input = appt_id_field.get_text();
            if (id_input.isEmpty()) {
                status_label.set_color(sf::Color::Red);
                status_label.set_text("Please enter an Appointment ID.");
                return;
            }
 
            // TODO: char appt_buf[32]; convert id_input → appt_buf
            // 1. Validate appointment belongs to this patient and status == "pending"
            //    → if not: status red, "Invalid appointment ID."
            // 2. Update appointment status to "cancelled" in appointments.txt
            // 3. patient += doctor_fee  (overloaded +=)
            // 4. FileHandler::update_patient_balance(...)
            // 5. Update bill status to "cancelled" in bills.txt
 
            status_label.set_color(sf::Color::Green);
            status_label.set_text("Appointment cancelled. PKR [fee] refunded. (stub)");
            appt_id_field.clear();
            load_pending_appointments(); });

        back_btn.set_on_click([this]()
                              {
                // We need to reload patient data to get updated balance
    int pid = 0;
    for (int i = 0; patient_id[i] != '\0'; i++)
        pid = pid * 10 + (patient_id[i] - '0');

    Patient* ptr_p = HospitalSystem::instance().get_patients().find(pid);
    if (ptr_p != nullptr)
        UIManager::instance().set_screen(
            new PatientMenuScreen(patient_id,
                                  ptr_p->get_name(),
                                  ptr_p->get_balance()));
    else
        UIManager::instance().set_screen(new LoginScreen()); });
    }

    void handle_event(sf::RenderWindow &window, const sf::Event &event) override
    {
        appt_id_field.handle_event(event, window);
        cancel_btn.handle_event(event, window);
        back_btn.handle_event(event, window);
    }

    void update() override {}

    void render(sf::RenderWindow &window) override
    {
        heading.render(window);
        divider.render(window);
        list_heading.render(window);
        appt_list.render(window);
        appt_id_label.render(window);
        appt_id_field.render(window);
        cancel_btn.render(window);
        back_btn.render(window);
        status_label.render(window);
    }
};