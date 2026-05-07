// #include "doctormenuscreen.hpp"
// #include "loginscreen.hpp"

// // Sub-screens — uncomment as you build each one
// // #include "doctor/todayappointmentsscreen.hpp"
// // #include "doctor/markcompletedscreen.hpp"
// // #include "doctor/marknoshowscreen.hpp"
// // #include "doctor/writeprescriptionscreen.hpp"
// // #include "doctor/patienthistoryscreen.hpp"

// static void safe_copy(char* dst, const char* src, std::size_t max) {
//     std::size_t i = 0;
//     while (i < max - 1 && src[i] != '\0') { dst[i] = src[i]; ++i; }
//     dst[i] = '\0';
// }

// DoctorMenuScreen::DoctorMenuScreen(const char* id)
//     : welcome_label("Welcome, Dr. [Name] | Specialization: [spec]"),  // TODO: fill from file
//       divider_label("==============================================="),
//       today_appt_btn  ("1. Today's Appointments",    380, 40),
//       complete_btn    ("2. Mark Appointment Complete",380, 40),
//       noshow_btn      ("3. Mark Appointment No-Show", 380, 40),
//       prescription_btn("4. Write Prescription",       380, 40),
//       history_btn     ("5. View Patient History",     380, 40),
//       logout_btn      ("6. Logout",                   380, 40),
//       status_label("")
// {
//     safe_copy(doctor_id, id, sizeof(doctor_id));

//     // ── Layout ────────────────────────────────────────────────────────────
//     welcome_label.set_position(50, 30);
//     divider_label.set_position(50, 60);

//     float btn_x    = 210.f;
//     float btn_y    = 100.f;
//     float btn_step = 65.f;

//     today_appt_btn.set_position  (btn_x, btn_y + btn_step * 0);
//     complete_btn.set_position    (btn_x, btn_y + btn_step * 1);
//     noshow_btn.set_position      (btn_x, btn_y + btn_step * 2);
//     prescription_btn.set_position(btn_x, btn_y + btn_step * 3);
//     history_btn.set_position     (btn_x, btn_y + btn_step * 4);
//     logout_btn.set_position      (btn_x, btn_y + btn_step * 5);

//     status_label.set_position(50, 570);

//     // ── Button handlers ───────────────────────────────────────────────────

//     today_appt_btn.set_on_click([this]() {
//         status_label.set_text("Opening: Today's Appointments...");
//         // TODO: UIManager::instance().set_screen(new TodayAppointmentsScreen(doctor_id));
//     });

//     complete_btn.set_on_click([this]() {
//         status_label.set_text("Opening: Mark Appointment Complete...");
//         // TODO: UIManager::instance().set_screen(new MarkCompletedScreen(doctor_id));
//     });

//     noshow_btn.set_on_click([this]() {
//         status_label.set_text("Opening: Mark Appointment No-Show...");
//         // TODO: UIManager::instance().set_screen(new MarkNoShowScreen(doctor_id));
//     });

//     prescription_btn.set_on_click([this]() {
//         status_label.set_text("Opening: Write Prescription...");
//         // TODO: UIManager::instance().set_screen(new WritePrescriptionScreen(doctor_id));
//     });

//     history_btn.set_on_click([this]() {
//         status_label.set_text("Opening: View Patient History...");
//         // TODO: UIManager::instance().set_screen(new PatientHistoryScreen(doctor_id));
//     });

//     logout_btn.set_on_click([this]() {
//         UIManager::instance().set_screen(new LoginScreen());
//     });

//     // TODO: load real doctor name + specialization
//     // e.g. Doctor* d = FileHandler::load_doctor(doctor_id, "doctors.txt");
//     //      char buf[120];
//     //      ... build "Welcome, Dr. X | Specialization: Y" manually ...
//     //      welcome_label.set_text(buf);
// }

// void DoctorMenuScreen::handle_event(sf::RenderWindow& window, const sf::Event& event) {
//     today_appt_btn.handle_event  (event, window);
//     complete_btn.handle_event    (event, window);
//     noshow_btn.handle_event      (event, window);
//     prescription_btn.handle_event(event, window);
//     history_btn.handle_event     (event, window);
//     logout_btn.handle_event      (event, window);
// }

// void DoctorMenuScreen::update() {}

// void DoctorMenuScreen::render(sf::RenderWindow& window) {
//     welcome_label.render(window);
//     divider_label.render(window);

//     today_appt_btn.render  (window);
//     complete_btn.render    (window);
//     noshow_btn.render      (window);
//     prescription_btn.render(window);
//     history_btn.render     (window);
//     logout_btn.render      (window);

//     status_label.render(window);
// }

#include "doctormenuscreen.hpp"
#include "loginscreen.hpp"
#include "todayappointmentscreen.hpp"
#include "markcompletedscreen.hpp"
#include "marknoshowscreen.hpp"
#include "writeprescriptionscreen.hpp"
#include "patienthistoryscreen.hpp"
 
static void safe_copy(char* dst, const char* src, std::size_t max) {
    std::size_t i = 0;
    while (i < max - 1 && src[i] != '\0') { dst[i] = src[i]; ++i; }
    dst[i] = '\0';
}
 
DoctorMenuScreen::DoctorMenuScreen(const char* id)
    : welcome_label("Welcome, Dr. [Name] | Specialization: [spec]"),
      divider_label("==============================================="),
      today_appt_btn  ("1. Today's Appointments",     380, 40),
      complete_btn    ("2. Mark Appointment Complete", 380, 40),
      noshow_btn      ("3. Mark Appointment No-Show",  380, 40),
      prescription_btn("4. Write Prescription",        380, 40),
      history_btn     ("5. View Patient History",      380, 40),
      logout_btn      ("6. Logout",                    380, 40),
      status_label("")
{
    safe_copy(doctor_id, id, sizeof(doctor_id));
 
    welcome_label.set_position(50, 30);
    divider_label.set_position(50, 60);
 
    float btn_x = 210.f, btn_y = 100.f, step = 65.f;
    today_appt_btn.set_position  (btn_x, btn_y + step * 0);
    complete_btn.set_position    (btn_x, btn_y + step * 1);
    noshow_btn.set_position      (btn_x, btn_y + step * 2);
    prescription_btn.set_position(btn_x, btn_y + step * 3);
    history_btn.set_position     (btn_x, btn_y + step * 4);
    logout_btn.set_position      (btn_x, btn_y + step * 5);
    status_label.set_position(50, 570);
 
    today_appt_btn.set_on_click([this]() {
        UIManager::instance().set_screen(new TodayAppointmentsScreen(doctor_id));
    });
    complete_btn.set_on_click([this]() {
        UIManager::instance().set_screen(new MarkCompletedScreen(doctor_id));
    });
    noshow_btn.set_on_click([this]() {
        UIManager::instance().set_screen(new MarkNoShowScreen(doctor_id));
    });
    prescription_btn.set_on_click([this]() {
        UIManager::instance().set_screen(new WritePrescriptionScreen(doctor_id));
    });
    history_btn.set_on_click([this]() {
        UIManager::instance().set_screen(new PatientHistoryScreen(doctor_id));
    });
    logout_btn.set_on_click([this]() {
        UIManager::instance().set_screen(new LoginScreen());
    });
}
 
void DoctorMenuScreen::handle_event(sf::RenderWindow& window, const sf::Event& event) {
    today_appt_btn.handle_event  (event, window);
    complete_btn.handle_event    (event, window);
    noshow_btn.handle_event      (event, window);
    prescription_btn.handle_event(event, window);
    history_btn.handle_event     (event, window);
    logout_btn.handle_event      (event, window);
}
 
void DoctorMenuScreen::update() {}
 
void DoctorMenuScreen::render(sf::RenderWindow& window) {
    welcome_label.render(window);
    divider_label.render(window);
    today_appt_btn.render  (window);
    complete_btn.render    (window);
    noshow_btn.render      (window);
    prescription_btn.render(window);
    history_btn.render     (window);
    logout_btn.render      (window);
    status_label.render(window);
}