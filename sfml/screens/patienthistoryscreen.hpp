#pragma once
#include "screen.hpp"
#include "../components/label.hpp"
#include "../components/color_label.hpp"
#include "../components/button.hpp"
#include "../components/text_field.hpp"
#include "../components/ui_manager.hpp"
 
class PatientHistoryScreen : public Screen {
private:
    char doctor_id[64];
 
    Label      heading;
    Label      patient_id_label;
    TextField  patient_id_field;
    Button     search_btn;
    Label      records_list;
    Button     back_btn;
    ColorLabel status_label;
 
    static void safe_copy(char* dst, const char* src, std::size_t max) {
        std::size_t i = 0;
        while (i < max - 1 && src[i] != '\0') { dst[i] = src[i]; ++i; }
        dst[i] = '\0';
    }
 
public:
    PatientHistoryScreen(const char* did)
        : heading("View Patient Medical History"),
          patient_id_label("Patient ID:"),
          search_btn("Search", 100, 40),
          records_list(""),
          back_btn("Back", 100, 40),
          status_label("")
    {
        safe_copy(doctor_id, did, sizeof(doctor_id));
 
        heading.set_position(50, 20);
        patient_id_label.set_position(50, 90);
        patient_id_field.set_position(180, 80);
        search_btn.set_position(450, 80);
        records_list.set_position(50, 140);
        status_label.set_position(50, 500);
        back_btn.set_position(50, 540);
 
        search_btn.set_on_click([this]() {
            if (patient_id_field.get_text().isEmpty()) {
                status_label.set_color(sf::Color::Red);
                status_label.set_text("Please enter a Patient ID.");
                return;
            }
            // TODO: validate patient exists AND has at least one completed appt with this doctor
            //       if not → "Access denied. You can only view records of your own patients."
            // TODO: FileHandler::get_prescriptions_by_patient_and_doctor(patient_id, doctor_id, arr, count)
            // Sort by date descending
            // Build display string
            records_list.set_text("Date        | Medicines              | Notes\n"
                                  "---------------------------------------------\n"
                                  "(records load from backend)");
            status_label.set_color(sf::Color::White);
            status_label.set_text("");
        });
 
        back_btn.set_on_click([this]() {
            // TODO: UIManager::instance().set_screen(new DoctorMenuScreen(doctor_id));
        });
    }
 
    void handle_event(sf::RenderWindow& window, const sf::Event& event) override {
        patient_id_field.handle_event(event, window);
        search_btn.handle_event(event, window);
        back_btn.handle_event(event, window);
    }
 
    void update() override {}
 
    void render(sf::RenderWindow& window) override {
        heading.render(window);
        patient_id_label.render(window);
        patient_id_field.render(window);
        search_btn.render(window);
        records_list.render(window);
        status_label.render(window);
        back_btn.render(window);
    }
};