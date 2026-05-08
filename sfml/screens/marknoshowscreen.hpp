#pragma once
#include "screen.hpp"
#include "../components/label.hpp"
#include "../components/color_label.hpp"
#include "../components/button.hpp"
#include "../components/text_field.hpp"
#include "../components/ui_manager.hpp"
#include "doctormenuscreen.hpp"
#include "../../src/hospital_system.hpp"

class MarkNoShowScreen : public Screen
{
private:
    char doctor_id[64];

    Label heading;
    Label appt_list;
    Label appt_id_label;
    TextField appt_id_field;
    Button confirm_btn;
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

    void load()
    {
        // TODO: FileHandler::get_pending_appointments_today(doctor_id, arr, count)
        appt_list.set_text("ID  | Patient Name         | Slot\n"
                           "----------------------------------\n"
                           "(today's pending appointments load from backend)");
    }

public:
    MarkNoShowScreen(const char *did)
        : heading("Mark Appointment No-Show"),
          appt_list(""),
          appt_id_label("Appointment ID:"),
          confirm_btn("Mark No-Show", 160, 40),
          back_btn("Back", 100, 40),
          status_label("")
    {
        safe_copy(doctor_id, did, sizeof(doctor_id));

        heading.set_position(50, 20);
        appt_list.set_position(50, 70);
        appt_id_label.set_position(50, 300);
        appt_id_field.set_position(210, 290);
        confirm_btn.set_position(180, 360);
        back_btn.set_position(360, 360);
        status_label.set_position(50, 420);

        load();

        confirm_btn.set_on_click([this]()
                                 {
            if (appt_id_field.get_text().isEmpty()) {
                status_label.set_color(sf::Color::Red);
                status_label.set_text("Please enter an Appointment ID.");
                return;
            }
            // TODO: validate appt belongs to this doctor, status==pending, date==today
            // TODO: FileHandler::update_appointment_status(appt_id, "no_show", "appointments.txt")
            // TODO: FileHandler::update_bill_status(appt_id, "cancelled", "bills.txt")
            // No refund on no-show
            status_label.set_color(sf::Color::Green);
            status_label.set_text("Appointment marked as no-show. (stub)");
            appt_id_field.clear();
            load(); });

        back_btn.set_on_click([this]()
                              { UIManager::instance().set_screen(new DoctorMenuScreen(doctor_id)); });
    }

    void handle_event(sf::RenderWindow &window, const sf::Event &event) override
    {
        appt_id_field.handle_event(event, window);
        confirm_btn.handle_event(event, window);
        back_btn.handle_event(event, window);
    }

    void update() override {}

    void render(sf::RenderWindow &window) override
    {
        heading.render(window);
        appt_list.render(window);
        appt_id_label.render(window);
        appt_id_field.render(window);
        confirm_btn.render(window);
        back_btn.render(window);
        status_label.render(window);
    }
};