#pragma once
#include "screen.hpp"
#include "../components/label.hpp"
#include "../components/color_label.hpp"
#include "../components/button.hpp"
#include "../components/text_field.hpp"
#include "../components/ui_manager.hpp"

// ── BookAppointmentScreen ─────────────────────────────────────────────────
// Step 1: enter specialization → show matching doctors
// Step 2: enter doctor ID → enter date → pick time slot
// All backend calls are stubbed with // TODO comments.
// ─────────────────────────────────────────────────────────────────────────

class BookAppointmentScreen : public Screen {
private:
    char patient_id[64];

    // ── Header ────────────────────────────────────────────────────────────
    Label  heading;
    Label  divider;

    // ── Step 1: specialization search ────────────────────────────────────
    Label      spec_label;
    TextField  spec_field;
    Button     search_btn;

    // ── Step 2: doctor ID ─────────────────────────────────────────────────
    Label      doc_id_label;
    TextField  doc_id_field;

    // ── Step 3: date ──────────────────────────────────────────────────────
    Label      date_label;
    TextField  date_field;        // DD-MM-YYYY

    // ── Step 4: time slot ─────────────────────────────────────────────────
    Label      slot_label;
    TextField  slot_field;        // e.g. 09:00

    // ── Actions ───────────────────────────────────────────────────────────
    Button     book_btn;
    Button     back_btn;

    // ── Feedback ──────────────────────────────────────────────────────────
    ColorLabel status_label;      // red for errors, green for success
    Label      results_label;     // shows doctor list after search

    static void safe_copy(char* dst, const char* src, std::size_t max) {
        std::size_t i = 0;
        while (i < max - 1 && src[i] != '\0') { dst[i] = src[i]; ++i; }
        dst[i] = '\0';
    }

public:
    BookAppointmentScreen(const char* pid)
        : heading("Book Appointment"),
          divider("=============================="),
          spec_label("Specialization:"),
          search_btn("Search Doctors", 160, 36),
          doc_id_label("Doctor ID:"),
          date_label("Date (DD-MM-YYYY):"),
          slot_label("Time Slot (e.g. 09:00):"),
          book_btn("Book Appointment", 200, 40),
          back_btn("Back", 100, 40),
          status_label(""),
          results_label("")
    {
        safe_copy(patient_id, pid, sizeof(patient_id));

        // ── Layout ────────────────────────────────────────────────────────
        heading.set_position(50, 20);
        divider.set_position(50, 48);

        // Row 1 — specialization
        spec_label.set_position(50, 90);
        spec_field.set_position(220, 80);
        search_btn.set_position(490, 80);

        // Doctor list area (text only, updated after search)
        results_label.set_position(50, 130);

        // Row 2 — doctor ID
        doc_id_label.set_position(50, 220);
        doc_id_field.set_position(220, 210);

        // Row 3 — date
        date_label.set_position(50, 280);
        date_field.set_position(220, 270);

        // Row 4 — time slot
        slot_label.set_position(50, 340);
        slot_field.set_position(220, 330);

        // Buttons
        book_btn.set_position(200, 400);
        back_btn.set_position(430, 400);

        // Status
        status_label.set_position(50, 460);

        // ── Handlers ──────────────────────────────────────────────────────

        search_btn.set_on_click([this]() {
            status_label.set_color(sf::Color::White);
            status_label.set_text("Searching...");
            results_label.set_text("");

            sf::String spec_input = spec_field.get_text();
            if (spec_input.isEmpty()) {
                status_label.set_color(sf::Color::Red);
                status_label.set_text("Please enter a specialization.");
                return;
            }

            // TODO: replace with FileHandler call
            // char spec_buf[64];
            // ... convert sf::String to char buf ...
            // Doctor* matches = FileHandler::find_doctors_by_spec(spec_buf, "doctors.txt", count);
            // if (count == 0) { status_label.set_text("No doctors available for that specialization."); return; }
            // Build display string from matches array

            // Stub: show placeholder result
            results_label.set_text("ID  Name                  Fee\n"
                                   "-----------------------------------\n"
                                   "(results will appear here after backend integration)");
            status_label.set_color(sf::Color::White);
            status_label.set_text("Doctors loaded. Enter Doctor ID below.");
        });

        book_btn.set_on_click([this]() {
            sf::String doc_input  = doc_id_field.get_text();
            sf::String date_input = date_field.get_text();
            sf::String slot_input = slot_field.get_text();

            if (doc_input.isEmpty() || date_input.isEmpty() || slot_input.isEmpty()) {
                status_label.set_color(sf::Color::Red);
                status_label.set_text("All fields are required.");
                return;
            }

            // TODO: convert inputs to char bufs then call:
            // 1. Validator::validate_date(date_buf)         → throw InvalidInputException
            // 2. FileHandler::find_doctor(doc_id_buf, ...)  → throw if not found
            // 3. Check slot availability via appointments.txt → throw SlotUnavailableException
            // 4. Check patient balance >= doctor fee         → throw InsufficientFundsException
            // 5. patient -= fee  (overloaded -=)
            // 6. FileHandler::append_appointment(...)
            // 7. FileHandler::append_bill(...)
            // 8. FileHandler::update_patient_balance(...)

            // Stub success
            status_label.set_color(sf::Color::Green);
            status_label.set_text("Appointment booked successfully. (stub)");
        });

        back_btn.set_on_click([this]() {
            // TODO: UIManager::instance().set_screen(new PatientMenuScreen(patient_id));
            UIManager::instance().set_screen(nullptr); // replace with correct screen
        });
    }

    void handle_event(sf::RenderWindow& window, const sf::Event& event) override {
        spec_field.handle_event(event, window);
        doc_id_field.handle_event(event, window);
        date_field.handle_event(event, window);
        slot_field.handle_event(event, window);
        search_btn.handle_event(event, window);
        book_btn.handle_event(event, window);
        back_btn.handle_event(event, window);
    }

    void update() override {}

    void render(sf::RenderWindow& window) override {
        heading.render(window);
        divider.render(window);
        spec_label.render(window);
        spec_field.render(window);
        search_btn.render(window);
        results_label.render(window);
        doc_id_label.render(window);
        doc_id_field.render(window);
        date_label.render(window);
        date_field.render(window);
        slot_label.render(window);
        slot_field.render(window);
        book_btn.render(window);
        back_btn.render(window);
        status_label.render(window);
    }
};