#pragma once
#include "screen.hpp"
#include "adminmenuscreen.hpp"
#include "../components/label.hpp"
#include "../components/color_label.hpp"
#include "../components/button.hpp"
#include "../components/ui_manager.hpp"

// ── ViewAppointmentsScreen (Admin) ────────────────────────────────────────
// Loads ALL appointments from appointments.txt, sorted by date ascending.
// ─────────────────────────────────────────────────────────────────────────
class ViewAppointmentsScreen : public Screen
{
private:
    Label heading;
    Label divider;
    Label col_header;
    Label appt_list;
    ColorLabel status_label;
    Button back_btn;

    void load()
    {
        // TODO: FileHandler::get_all_appointments("appointments.txt", arr, count)
        // Sort by date ascending (implement manually, no std::sort)
        // Build display: ApptID | PatientName | DoctorName | Date | Slot | Status
        col_header.set_text("ID  | Patient         | Doctor          | Date       | Slot  | Status");
        appt_list.set_text("------------------------------------------------------------------------\n"
                           "(all appointments will load from backend)");
    }

public:
    ViewAppointmentsScreen()
        : heading("All Appointments"),
          divider("===================="),
          col_header(""),
          appt_list(""),
          status_label(""),
          back_btn("Back", 100, 40)
    {
        heading.set_position(50, 20);
        divider.set_position(50, 48);
        col_header.set_position(50, 80);
        appt_list.set_position(50, 108);
        status_label.set_position(50, 500);
        back_btn.set_position(50, 540);

        load();

        back_btn.set_on_click([this]()
                              { UIManager::instance().set_screen(new AdminMenuScreen()); });
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
        col_header.render(window);
        appt_list.render(window);
        status_label.render(window);
        back_btn.render(window);
    }
};
