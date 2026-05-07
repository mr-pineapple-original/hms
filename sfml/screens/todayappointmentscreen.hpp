#pragma once
#include "screen.hpp"
#include "../components/label.hpp"
#include "../components/color_label.hpp"
#include "../components/button.hpp"
#include "../components/ui_manager.hpp"
 
class TodayAppointmentsScreen : public Screen {
private:
    char doctor_id[64];
 
    Label      heading;
    Label      appt_list;
    ColorLabel status_label;
    Button     back_btn;
 
    static void safe_copy(char* dst, const char* src, std::size_t max) {
        std::size_t i = 0;
        while (i < max - 1 && src[i] != '\0') { dst[i] = src[i]; ++i; }
        dst[i] = '\0';
    }
 
    void load() {
        // TODO: get today's date via time()/strftime()
        // TODO: FileHandler::get_appointments_by_doctor_today(doctor_id, date, arr, count)
        // Sort by time slot ascending
        // Build string: Appt ID | Patient Name | Slot | Status
        appt_list.set_text("ID  | Patient Name         | Slot  | Status\n"
                           "--------------------------------------------\n"
                           "(today's appointments load from backend)");
    }
 
public:
    TodayAppointmentsScreen(const char* did)
        : heading("Today's Appointments"),
          appt_list(""),
          status_label(""),
          back_btn("Back", 100, 40)
    {
        safe_copy(doctor_id, did, sizeof(doctor_id));
 
        heading.set_position(50, 20);
        appt_list.set_position(50, 70);
        status_label.set_position(50, 500);
        back_btn.set_position(50, 540);
 
        load();
 
        back_btn.set_on_click([this]() {
            // TODO: UIManager::instance().set_screen(new DoctorMenuScreen(doctor_id));
        });
    }
 
    void handle_event(sf::RenderWindow& window, const sf::Event& event) override {
        back_btn.handle_event(event, window);
    }
 
    void update() override {}
 
    void render(sf::RenderWindow& window) override {
        heading.render(window);
        appt_list.render(window);
        status_label.render(window);
        back_btn.render(window);
    }
};