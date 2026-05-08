// #pragma once
// #include "screen.hpp"
// #include "../components/label.hpp"
// #include "../components/color_label.hpp"
// #include "../components/button.hpp"
// #include "../components/text_field.hpp"
// #include "../components/ui_manager.hpp"

// // ── BookAppointmentScreen ─────────────────────────────────────────────────
// // Step 1: enter specialization → show matching doctors
// // Step 2: enter doctor ID → enter date → pick time slot
// // All backend calls are stubbed with // TODO comments.
// // ─────────────────────────────────────────────────────────────────────────

// class BookAppointmentScreen : public Screen
// {
// private:
//     char patient_id[64];

//     // ── Header ────────────────────────────────────────────────────────────
//     Label heading;
//     Label divider;

//     // ── Step 1: specialization search ────────────────────────────────────
//     Label spec_label;
//     TextField spec_field;
//     Button search_btn;

//     // ── Step 2: doctor ID ─────────────────────────────────────────────────
//     Label doc_id_label;
//     TextField doc_id_field;

//     // ── Step 3: date ──────────────────────────────────────────────────────
//     Label date_label;
//     TextField date_field; // DD-MM-YYYY

//     // ── Step 4: time slot ─────────────────────────────────────────────────
//     Label slot_label;
//     TextField slot_field; // e.g. 09:00

//     // ── Actions ───────────────────────────────────────────────────────────
//     Button book_btn;
//     Button back_btn;

//     // ── Feedback ──────────────────────────────────────────────────────────
//     ColorLabel status_label; // red for errors, green for success
//     Label results_label;     // shows doctor list after search

//     static void safe_copy(char *dst, const char *src, std::size_t max)
//     {
//         std::size_t i = 0;
//         while (i < max - 1 && src[i] != '\0')
//         {
//             dst[i] = src[i];
//             ++i;
//         }
//         dst[i] = '\0';
//     }

// public:
//     BookAppointmentScreen(const char *pid)
//         : heading("Book Appointment"),
//           divider("=============================="),
//           spec_label("Specialization:"),
//           search_btn("Search Doctors", 160, 36),
//           doc_id_label("Doctor ID:"),
//           date_label("Date (DD-MM-YYYY):"),
//           slot_label("Time Slot (e.g. 09:00):"),
//           book_btn("Book Appointment", 200, 40),
//           back_btn("Back", 100, 40),
//           status_label(""),
//           results_label("")
//     {
//         safe_copy(patient_id, pid, sizeof(patient_id));

//         // ── Layout ────────────────────────────────────────────────────────
//         heading.set_position(50, 20);
//         divider.set_position(50, 48);

//         // Row 1 — specialization
//         spec_label.set_position(50, 90);
//         spec_field.set_position(220, 80);
//         search_btn.set_position(490, 80);

//         // Doctor list area (text only, updated after search)
//         results_label.set_position(50, 130);

//         // Row 2 — doctor ID
//         doc_id_label.set_position(50, 220);
//         doc_id_field.set_position(220, 210);

//         // Row 3 — date
//         date_label.set_position(50, 280);
//         date_field.set_position(220, 270);

//         // Row 4 — time slot
//         slot_label.set_position(50, 340);
//         slot_field.set_position(220, 330);

//         // Buttons
//         book_btn.set_position(200, 400);
//         back_btn.set_position(430, 400);

//         // Status
//         status_label.set_position(50, 460);

//         // ── Handlers ──────────────────────────────────────────────────────

//         search_btn.set_on_click([this]()
//                                 {
//             status_label.set_color(sf::Color::White);
//             status_label.set_text("Searching...");
//             results_label.set_text("");

//             sf::String spec_input = spec_field.get_text();
//             if (spec_input.isEmpty()) {
//                 status_label.set_color(sf::Color::Red);
//                 status_label.set_text("Please enter a specialization.");
//                 return;
//             }

//             // TODO: replace with FileHandler call
//             // char spec_buf[64];
//             // ... convert sf::String to char buf ...
//             // Doctor* matches = FileHandler::find_doctors_by_spec(spec_buf, "doctors.txt", count);
//             // if (count == 0) { status_label.set_text("No doctors available for that specialization."); return; }
//             // Build display string from matches array

//             // Stub: show placeholder result
//             results_label.set_text("ID  Name                  Fee\n"
//                                    "-----------------------------------\n"
//                                    "(results will appear here after backend integration)");
//             status_label.set_color(sf::Color::White);
//             status_label.set_text("Doctors loaded. Enter Doctor ID below."); });

//         book_btn.set_on_click([this]()
//                               {
//             sf::String doc_input  = doc_id_field.get_text();
//             sf::String date_input = date_field.get_text();
//             sf::String slot_input = slot_field.get_text();

//             if (doc_input.isEmpty() || date_input.isEmpty() || slot_input.isEmpty()) {
//                 status_label.set_color(sf::Color::Red);
//                 status_label.set_text("All fields are required.");
//                 return;
//             }

//             // TODO: convert inputs to char bufs then call:
//             // 1. Validator::validate_date(date_buf)         → throw InvalidInputException
//             // 2. FileHandler::find_doctor(doc_id_buf, ...)  → throw if not found
//             // 3. Check slot availability via appointments.txt → throw SlotUnavailableException
//             // 4. Check patient balance >= doctor fee         → throw InsufficientFundsException
//             // 5. patient -= fee  (overloaded -=)
//             // 6. FileHandler::append_appointment(...)
//             // 7. FileHandler::append_bill(...)
//             // 8. FileHandler::update_patient_balance(...)

//             // Stub success
//             status_label.set_color(sf::Color::Green);
//             status_label.set_text("Appointment booked successfully. (stub)"); });

//         back_btn.set_on_click([this]()
//                               {
//     // We need to reload patient data to get updated balance
//     int pid = 0;
//     for (int i = 0; patient_id[i] != '\0'; i++)
//         pid = pid * 10 + (patient_id[i] - '0');

//     Patient* ptr_p = HospitalSystem::instance().get_patients().find(pid);
//     if (ptr_p != nullptr)
//         UIManager::instance().set_screen(
//             new PatientMenuScreen(patient_id,
//                                   ptr_p->get_name(),
//                                   ptr_p->get_balance()));
//     else
//         UIManager::instance().set_screen(new LoginScreen()); });
//     }

//     void handle_event(sf::RenderWindow &window, const sf::Event &event) override
//     {
//         spec_field.handle_event(event, window);
//         doc_id_field.handle_event(event, window);
//         date_field.handle_event(event, window);
//         slot_field.handle_event(event, window);
//         search_btn.handle_event(event, window);
//         book_btn.handle_event(event, window);
//         back_btn.handle_event(event, window);
//     }

//     void update() override {}

//     void render(sf::RenderWindow &window) override
//     {
//         heading.render(window);
//         divider.render(window);
//         spec_label.render(window);
//         spec_field.render(window);
//         search_btn.render(window);
//         results_label.render(window);
//         doc_id_label.render(window);
//         doc_id_field.render(window);
//         date_label.render(window);
//         date_field.render(window);
//         slot_label.render(window);
//         slot_field.render(window);
//         book_btn.render(window);
//         back_btn.render(window);
//         status_label.render(window);
//     }
// };


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
#include "../../src/file_handler.hpp"



// Helper function 

static bool is_valid_slot(const char* slot) {
    const char* valid_slots[] = {"09:00","10:00","11:00","12:00","13:00","14:00","15:00","16:00"};
    for (int i = 0; i < 8; i++)
        if (is_char_arrays_equal(slot, valid_slots[i])) return true;
    return false;
}


class BookAppointmentScreen : public Screen {
private:
    char patient_id[64];
 
    Label      heading;
    Label      divider;
    Label      spec_label;
    TextField  spec_field;
    Button     search_btn;
    Label      doc_id_label;
    TextField  doc_id_field;
    Label      date_label;
    TextField  date_field;
    Label      slot_label;
    TextField  slot_field;
    Button     book_btn;
    Button     back_btn;
    ColorLabel status_label;
    Label      results_label;
 
    static void safe_copy(char* dst, const char* src, std::size_t max) {
        std::size_t i = 0;
        while (i < max - 1 && src[i] != '\0') { dst[i] = src[i]; ++i; }
        dst[i] = '\0';
    }
 
    static void sf_to_char(const sf::String& s, char* buf, std::size_t max) {
        std::size_t len = s.getSize() < max - 1 ? s.getSize() : max - 1;
        for (std::size_t i = 0; i < len; ++i) buf[i] = (char)s[i];
        buf[len] = '\0';
    }
 
    static bool char_eq(const char* a, const char* b) {
        int i = 0;
        while (a[i] && b[i]) { if (a[i] != b[i]) return false; i++; }
        return a[i] == '\0' && b[i] == '\0';
    }
 
    static int write_int(char* buf, int pos, int val) {
        char tmp[16]; int ti = 0;
        if (val == 0) { tmp[ti++] = '0'; }
        else { int n = val; char r[16]; int ri = 0; while(n>0){r[ri++]='0'+n%10;n/=10;} while(ri>0)tmp[ti++]=r[--ri]; }
        for (int i = 0; i < ti; i++) buf[pos++] = tmp[i];
        return pos;
    }
 
    static int write_str(char* buf, int pos, const char* s) {
        for (int i = 0; s[i]; i++) buf[pos++] = s[i];
        return pos;
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
 
        heading.set_position(50, 20);
        divider.set_position(50, 48);
        spec_label.set_position(50, 90);
        spec_field.set_position(220, 80);
        search_btn.set_position(490, 80);
        results_label.set_position(50, 130);
        doc_id_label.set_position(50, 220);
        doc_id_field.set_position(220, 210);
        date_label.set_position(50, 280);
        date_field.set_position(220, 270);
        slot_label.set_position(50, 340);
        slot_field.set_position(220, 330);
        book_btn.set_position(200, 400);
        back_btn.set_position(430, 400);
        status_label.set_position(50, 460);
 
        // ── Search button ─────────────────────────────────────────────────
        search_btn.set_on_click([this]() {
            if (spec_field.get_text().isEmpty()) {
                status_label.set_color(sf::Color::Red);
                status_label.set_text("Please enter a specialization.");
                return;
            }
 
            char spec_buf[64];
            sf_to_char(spec_field.get_text(), spec_buf, sizeof(spec_buf));
 
            // Lowercase manually
            for (int i = 0; spec_buf[i]; i++)
                if (spec_buf[i] >= 'A' && spec_buf[i] <= 'Z') spec_buf[i] += 32;
 
            Doctor* ptr_doctors = HospitalSystem::instance().get_doctors().get_data();
            int doc_count       = HospitalSystem::instance().get_doctors().size();
 
            static char buf[1024]; int pos = 0;
            pos = write_str(buf, pos, "ID  | Name                 | Fee\n");
            pos = write_str(buf, pos, "---------------------------------\n");
 
            bool found = false;
            for (int i = 0; i < doc_count; i++) {
                char* ptr_spec = (ptr_doctors + i)->get_specialization();
 
                // Lowercase copy of doctor specialization
                int slen = 0; while (ptr_spec[slen]) slen++;
                char* lower = new char[slen + 1];
                for (int j = 0; j <= slen; j++)
                    lower[j] = (ptr_spec[j] >= 'A' && ptr_spec[j] <= 'Z') ? ptr_spec[j] + 32 : ptr_spec[j];
 
                bool match = char_eq(lower, spec_buf);
                delete[] lower;
                if (!match) continue;
 
                found = true;
                pos = write_int(buf, pos, (ptr_doctors + i)->get_id());
                pos = write_str(buf, pos, " | ");
                pos = write_str(buf, pos, (ptr_doctors + i)->get_name());
                pos = write_str(buf, pos, " | ");
                pos = write_int(buf, pos, (int)(ptr_doctors + i)->get_fee());
                buf[pos++] = '\n';
            }
            buf[pos] = '\0';
 
            if (!found) {
                status_label.set_color(sf::Color::Red);
                status_label.set_text("No doctors available for that specialization.");
                results_label.set_text("");
                return;
            }
 
            results_label.set_text(buf);
            status_label.set_color(sf::Color::White);
            status_label.set_text("Enter Doctor ID, date and time slot below.");
        });
 
        // ── Book button ───────────────────────────────────────────────────
        book_btn.set_on_click([this]() {
            if (doc_id_field.get_text().isEmpty() ||
                date_field.get_text().isEmpty()   ||
                slot_field.get_text().isEmpty()) {
                status_label.set_color(sf::Color::Red);
                status_label.set_text("All fields are required.");
                return;
            }
 
            char doc_buf[32], date_buf[32], slot_buf[16];
            sf_to_char(doc_id_field.get_text(), doc_buf,  sizeof(doc_buf));
            sf_to_char(date_field.get_text(),   date_buf, sizeof(date_buf));
            sf_to_char(slot_field.get_text(),   slot_buf, sizeof(slot_buf));
 
            int pid_int = 0;
            for (int i = 0; patient_id[i]; i++) pid_int = pid_int * 10 + (patient_id[i] - '0');
            int doc_id = 0;
            for (int i = 0; doc_buf[i]; i++) doc_id = doc_id * 10 + (doc_buf[i] - '0');
 
            Doctor* ptr_d = HospitalSystem::instance().get_doctors().find(doc_id);
            if (ptr_d == nullptr) {
                status_label.set_color(sf::Color::Red);
                status_label.set_text("Doctor not found.");
                return;
            }
 
            Patient* ptr_p = HospitalSystem::instance().get_patients().find(pid_int);
            if (ptr_p == nullptr) {
                status_label.set_color(sf::Color::Red);
                status_label.set_text("Patient not found.");
                return;
            }
 
            // Check balance
            if (ptr_p->get_balance() < ptr_d->get_fee()) {
                status_label.set_color(sf::Color::Red);
                status_label.set_text("Insufficient balance.");
                return;
            }
 
            // Check slot availability
            Appointment* ptr_appts = HospitalSystem::instance().get_appointments().get_data();
            int appt_count = HospitalSystem::instance().get_appointments().size();
            for (int i = 0; i < appt_count; i++) {
                if ((ptr_appts + i)->get_doctor_id() == doc_id &&
                    char_eq((ptr_appts + i)->get_date(), date_buf) &&
                    char_eq((ptr_appts + i)->get_time(), slot_buf) &&
                    !char_eq((const char*)(ptr_appts + i)->get_status(), "cancelled")) {
                    status_label.set_color(sf::Color::Red);
                    status_label.set_text("That slot is already taken. Pick another.");
                    return;
                }
            }
            
            if (!is_valid_slot(slot_buf)) {
    status_label.set_color(sf::Color::Red);
    status_label.set_text("Invalid slot. Use 09:00, 10:00, 11:00, 12:00, 13:00, 14:00, 15:00, or 16:00.");
    return;
}

            // Deduct fee using -= operator
            *ptr_p -= ptr_d->get_fee();
 
            // Generate new IDs
            int new_appt_id = FileHandler::generate_new_id(HospitalSystem::instance().get_appointments());
            int new_bill_id = FileHandler::generate_new_id(HospitalSystem::instance().get_bills());
 
            char pending[] = "pending";
            char unpaid[]  = "unpaid";
 
            Appointment new_appt(new_appt_id, pid_int, doc_id, date_buf, slot_buf, pending);
            HospitalSystem::instance().get_appointments().add(new_appt);
            FileHandler::append_appointment(new_appt, "appointments.txt");
 
            Bill new_bill(new_bill_id, pid_int, new_appt_id, ptr_d->get_fee(), unpaid, date_buf);
            HospitalSystem::instance().get_bills().add(new_bill);
            FileHandler::append_bill(new_bill, "bills.txt");
 
            FileHandler::update_patients(HospitalSystem::instance().get_patients(), "patients.txt");
 
            status_label.set_color(sf::Color::Green);
            status_label.set_text("Appointment booked successfully!");
            doc_id_field.clear(); date_field.clear(); slot_field.clear();
        });
 
        // ── Back button (unchanged from your original) ────────────────────
        back_btn.set_on_click([this]() {
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
                UIManager::instance().set_screen(new LoginScreen());
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