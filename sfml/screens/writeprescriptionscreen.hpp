#pragma once
#include "screen.hpp"
#include "../components/label.hpp"
#include "../components/color_label.hpp"
#include "../components/button.hpp"
#include "../components/text_field.hpp"
#include "../components/ui_manager.hpp"
 
class WritePrescriptionScreen : public Screen {
private:
    char doctor_id[64];
 
    Label      heading;
    Label      appt_id_label;
    TextField  appt_id_field;
    Label      medicines_label;
    TextField  medicines_field;   // e.g. Paracetamol 500mg;Amoxicillin 250mg
    Label      notes_label;
    TextField  notes_field;
    Button     save_btn;
    Button     back_btn;
    ColorLabel status_label;
 
    static void safe_copy(char* dst, const char* src, std::size_t max) {
        std::size_t i = 0;
        while (i < max - 1 && src[i] != '\0') { dst[i] = src[i]; ++i; }
        dst[i] = '\0';
    }
 
public:
    WritePrescriptionScreen(const char* did)
        : heading("Write Prescription"),
          appt_id_label("Appointment ID:"),
          medicines_label("Medicines (Name Dose;...):"),
          notes_label("Notes:"),
          save_btn("Save Prescription", 180, 40),
          back_btn("Back", 100, 40),
          status_label("")
    {
        safe_copy(doctor_id, did, sizeof(doctor_id));
 
        heading.set_position(50, 20);
 
        appt_id_label.set_position(50, 90);
        appt_id_field.set_position(220, 80);
 
        medicines_label.set_position(50, 160);
        medicines_field.set_position(50, 190);   // wider field below label
 
        notes_label.set_position(50, 260);
        notes_field.set_position(50, 290);
 
        save_btn.set_position(180, 370);
        back_btn.set_position(380, 370);
        status_label.set_position(50, 430);
 
        save_btn.set_on_click([this]() {
            if (appt_id_field.get_text().isEmpty() || medicines_field.get_text().isEmpty()) {
                status_label.set_color(sf::Color::Red);
                status_label.set_text("Appointment ID and medicines are required.");
                return;
            }
            // TODO: validate appt belongs to this doctor and status == "completed"
            // TODO: check prescriptions.txt — if already exists → error
            // TODO: FileHandler::append_prescription(appt_id, doctor_id, patient_id, date, medicines, notes)
            status_label.set_color(sf::Color::Green);
            status_label.set_text("Prescription saved. (stub)");
            appt_id_field.clear();
            medicines_field.clear();
            notes_field.clear();
        });
 
        back_btn.set_on_click([this]() {
            // TODO: UIManager::instance().set_screen(new DoctorMenuScreen(doctor_id));
        });
    }
 
    void handle_event(sf::RenderWindow& window, const sf::Event& event) override {
        appt_id_field.handle_event(event, window);
        medicines_field.handle_event(event, window);
        notes_field.handle_event(event, window);
        save_btn.handle_event(event, window);
        back_btn.handle_event(event, window);
    }
 
    void update() override {}
 
    void render(sf::RenderWindow& window) override {
        heading.render(window);
        appt_id_label.render(window);
        appt_id_field.render(window);
        medicines_label.render(window);
        medicines_field.render(window);
        notes_label.render(window);
        notes_field.render(window);
        save_btn.render(window);
        back_btn.render(window);
        status_label.render(window);
    }
};