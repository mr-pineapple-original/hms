#pragma once
#include "screen.hpp"
#include "../components/label.hpp"
#include "../components/color_label.hpp"
#include "../components/button.hpp"
#include "../components/ui_manager.hpp"
#include "patientmenuscreen.hpp"
#include "loginscreen.hpp"
#include "../../src/hospital_system.hpp"
#include "../../src/patient.hpp"
// ── PatientAppointmentScreen ────────────────────────────────────────────────
// Shows all appointments for this patient sorted by date ascending.
// TODO: connect to FileHandler::get_appointments_by_patient(...)
// ─────────────────────────────────────────────────────────────────────────

class PatientAppointmentScreen : public Screen
{
private:
    char patient_id[64];

    Label heading;
    Label divider;
    Label col_header;
    Label appt_list;
    ColorLabel status_label;
    Button back_btn;

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

    void load()
    {
        // TODO: FileHandler::get_all_appointments(patient_id, "appointments.txt", arr, count)
        // Sort by date ascending (implement manually)
        // Build display string: ID | Doctor Name | Spec | Date | Slot | Status
        appt_list.set_text("ID  | Doctor            | Date        | Slot  | Status\n"
                           "--------------------------------------------------------\n"
                           "(appointments will load from backend)");
    }

public:
    PatientAppointmentScreen(const char *pid)
        : heading("My Appointments"),
          divider("===================="),
          col_header(""),
          appt_list(""),
          status_label(""),
          back_btn("Back", 100, 40)
    {
        safe_copy(patient_id, pid, sizeof(patient_id));

        heading.set_position(50, 20);
        divider.set_position(50, 48);
        appt_list.set_position(50, 80);
        status_label.set_position(50, 500);
        back_btn.set_position(50, 540);

        load();

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
        back_btn.handle_event(event, window);
    }

    void update() override {}

    void render(sf::RenderWindow &window) override
    {
        heading.render(window);
        divider.render(window);
        appt_list.render(window);
        status_label.render(window);
        back_btn.render(window);
    }
};