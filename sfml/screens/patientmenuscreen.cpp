// #include "patientmenuscreen.hpp"
// #include "loginscreen.hpp"
// #include "../components/sf_string_utils.hpp"

// // Sub-screens — uncomment includes as you build each one
// // #include "patient/bookappointmentscreen.hpp"
// // #include "patient/cancelappointmentscreen.hpp"
// // #include "patient/viewappointmentsscreen.hpp"
// // #include "patient/viewrecordsscreen.hpp"
// // #include "patient/viewbillsscreen.hpp"
// // #include "patient/paybillscreen.hpp"
// // #include "patient/topupscreen.hpp"

// #include <cstring>  // for strncpy (char arrays, no std::string)

// // ── Helper: copy a char[] safely ─────────────────────────────────────────
// static void safe_copy(char* dst, const char* src, std::size_t max) {
//     std::size_t i = 0;
//     while (i < max - 1 && src[i] != '\0') { dst[i] = src[i]; ++i; }
//     dst[i] = '\0';
// }

// // PatientMenuScreen::PatientMenuScreen(const char* id)
// //     : welcome_label("Welcome, Patient"),   // TODO: replace with real name from file
// //       balance_label("Balance: PKR ----"),  // TODO: load from FileHandler
// //       divider_label("========================"),
// //       book_btn    ("1. Book Appointment",    360, 40),
// //       cancel_btn  ("2. Cancel Appointment",  360, 40),
// //       view_appt_btn("3. My Appointments",    360, 40),
// //       records_btn ("4. Medical Records",     360, 40),
// //       bills_btn   ("5. My Bills",            360, 40),
// //       pay_btn     ("6. Pay Bill",            360, 40),
// //       topup_btn   ("7. Top Up Balance",      360, 40),
// //       logout_btn  ("8. Logout",              360, 40),
// //       status_label("")
// // {
// //     safe_copy(patient_id, id, sizeof(patient_id));

// //     // ── Layout (800×600 window) ───────────────────────────────────────────
// //     welcome_label.set_position(50, 30);
// //     balance_label.set_position(50, 60);
// //     divider_label.set_position(50, 90);

// //     float btn_x    = 220.f;
// //     float btn_y    = 130.f;
// //     float btn_step = 52.f;

// //     book_btn.set_position     (btn_x, btn_y + btn_step * 0);
// //     cancel_btn.set_position   (btn_x, btn_y + btn_step * 1);
// //     view_appt_btn.set_position(btn_x, btn_y + btn_step * 2);
// //     records_btn.set_position  (btn_x, btn_y + btn_step * 3);
// //     bills_btn.set_position    (btn_x, btn_y + btn_step * 4);
// //     pay_btn.set_position      (btn_x, btn_y + btn_step * 5);
// //     topup_btn.set_position    (btn_x, btn_y + btn_step * 6);
// //     logout_btn.set_position   (btn_x, btn_y + btn_step * 7);

// //     status_label.set_position(50, 570);

// //     // ── Button handlers ───────────────────────────────────────────────────

// //     book_btn.set_on_click([this]() {
// //         status_label.set_text("Opening: Book Appointment...");
// //         // TODO: UIManager::instance().set_screen(new BookAppointmentScreen(patient_id));
// //     });

// //     cancel_btn.set_on_click([this]() {
// //         status_label.set_text("Opening: Cancel Appointment...");
// //         // TODO: UIManager::instance().set_screen(new CancelAppointmentScreen(patient_id));
// //     });

// //     view_appt_btn.set_on_click([this]() {
// //         status_label.set_text("Opening: My Appointments...");
// //         // TODO: UIManager::instance().set_screen(new ViewAppointmentsScreen(patient_id));
// //     });

// //     records_btn.set_on_click([this]() {
// //         status_label.set_text("Opening: Medical Records...");
// //         // TODO: UIManager::instance().set_screen(new ViewRecordsScreen(patient_id));
// //     });

// //     bills_btn.set_on_click([this]() {
// //         status_label.set_text("Opening: My Bills...");
// //         // TODO: UIManager::instance().set_screen(new ViewBillsScreen(patient_id));
// //     });

// //     pay_btn.set_on_click([this]() {
// //         status_label.set_text("Opening: Pay Bill...");
// //         // TODO: UIManager::instance().set_screen(new PayBillScreen(patient_id));
// //     });

// //     topup_btn.set_on_click([this]() {
// //         status_label.set_text("Opening: Top Up Balance...");
// //         // TODO: UIManager::instance().set_screen(new TopUpScreen(patient_id));
// //     });

// //     logout_btn.set_on_click([this]() {
// //         UIManager::instance().set_screen(new LoginScreen());
// //     });

// //     // TODO: load real patient name and balance via FileHandler
// //     // e.g.  Patient* p = FileHandler::load_patient(patient_id, "patients.txt");
// //     //       welcome_label.set_text("Welcome, " + p->get_name());
// //     //       refresh_balance_label();
// // }




//       PatientMenuScreen::PatientMenuScreen(const char* id, const char* name, double balance)
//     : welcome_label(""),
//       balance_label(""),
//       divider_label("========================"),
//       book_btn    ("1. Book Appointment",    360, 40),
//       cancel_btn  ("2. Cancel Appointment",  360, 40),
//       view_appt_btn("3. My Appointments",    360, 40),
//       records_btn ("4. Medical Records",     360, 40),
//       bills_btn   ("5. My Bills",            360, 40),
//       pay_btn     ("6. Pay Bill",            360, 40),
//       topup_btn   ("7. Top Up Balance",      360, 40),
//       logout_btn  ("8. Logout",              360, 40),
//       status_label("")
// {
//     safe_copy(patient_id, id, sizeof(patient_id));

//     // Build welcome string manually
//     char welcome_buf[80];
//     const char* prefix = "Welcome, ";
//     int pos = 0;
//     for (int i = 0; prefix[i] != '\0'; i++)    welcome_buf[pos++] = prefix[i];
//     for (int i = 0; name[i]   != '\0'; i++)    welcome_buf[pos++] = name[i];
//     welcome_buf[pos] = '\0';
//     welcome_label.set_text(welcome_buf);

//     // Build balance string manually
//     char bal_buf[64];
//     const char* bal_prefix = "Balance: PKR ";
//     pos = 0;
//     for (int i = 0; bal_prefix[i] != '\0'; i++) bal_buf[pos++] = bal_prefix[i];
//     char num_buf[32];
//     double_to_char(balance, num_buf);
//     for (int i = 0; num_buf[i] != '\0'; i++)    bal_buf[pos++] = num_buf[i];
//     bal_buf[pos] = '\0';
//     balance_label.set_text(bal_buf);

//     // rest of your layout and button handlers stay exactly the same
// }

// void PatientMenuScreen::refresh_balance_label()
// {
//     int pid = 0;
//     for (int i = 0; patient_id[i] != '\0'; i++)
//         pid = pid * 10 + (patient_id[i] - '0');

//     Patient* ptr_p = HospitalSystem::instance().get_patients().find(pid);
//     if (ptr_p == nullptr) return;

//     char bal_buf[64];
//     const char* prefix = "Balance: PKR ";
//     int pos = 0;
//     for (int i = 0; prefix[i] != '\0'; i++)      bal_buf[pos++] = prefix[i];
//     char num_buf[32];
//     double_to_char(ptr_p->get_balance(), num_buf);
//     for (int i = 0; num_buf[i] != '\0'; i++)      bal_buf[pos++] = num_buf[i];
//     bal_buf[pos] = '\0';
//     balance_label.set_text(bal_buf);
// }

// void PatientMenuScreen::handle_event(sf::RenderWindow& window, const sf::Event& event) {
//     book_btn.handle_event     (event, window);
//     cancel_btn.handle_event   (event, window);
//     view_appt_btn.handle_event(event, window);
//     records_btn.handle_event  (event, window);
//     bills_btn.handle_event    (event, window);
//     pay_btn.handle_event      (event, window);
//     topup_btn.handle_event    (event, window);
//     logout_btn.handle_event   (event, window);
// }

// void PatientMenuScreen::update() {}

// void PatientMenuScreen::render(sf::RenderWindow& window) {
//     welcome_label.render(window);
//     balance_label.render(window);
//     divider_label.render(window);

//     book_btn.render     (window);
//     cancel_btn.render   (window);
//     view_appt_btn.render(window);
//     records_btn.render  (window);
//     bills_btn.render    (window);
//     pay_btn.render      (window);
//     topup_btn.render    (window);
//     logout_btn.render   (window);

//     status_label.render(window);
// }


#include "patientmenuscreen.hpp"
#include "loginscreen.hpp"
#include "bookappointmentscreen.hpp"
#include "cancelappointmentscreen.hpp"
#include "viewappointmentsscreen.hpp"
#include "viewpatientappointmentscreen.hpp"
#include "viewmedicalrecordsscreen.hpp"
#include "viewbillscreen.hpp"
#include "paybillscreen.hpp"
#include "topupbalancescreen.hpp"
#include "../components/sf_string_utils.hpp"
#include "../../src/hospital_system.hpp"
#include "../../src/patient.hpp"

static void safe_copy(char* dst, const char* src, std::size_t max)
{
    std::size_t i = 0;
    while (i < max - 1 && src[i] != '\0') { dst[i] = src[i]; ++i; }
    dst[i] = '\0';
}

PatientMenuScreen::PatientMenuScreen(const char* id, const char* name, double balance)
    : welcome_label(""),
      balance_label(""),
      divider_label("========================"),
      book_btn     ("1. Book Appointment",   360, 40),
      cancel_btn   ("2. Cancel Appointment", 360, 40),
      view_appt_btn("3. My Appointments",    360, 40),
      records_btn  ("4. Medical Records",    360, 40),
      bills_btn    ("5. My Bills",           360, 40),
      pay_btn      ("6. Pay Bill",           360, 40),
      topup_btn    ("7. Top Up Balance",     360, 40),
      logout_btn   ("8. Logout",             360, 40),
      status_label ("")
{
    safe_copy(patient_id, id, sizeof(patient_id));

    // ── Build welcome string ──────────────────────────────────────────────
    char welcome_buf[80];
    const char* prefix = "Welcome, ";
    int pos = 0;
    for (int i = 0; prefix[i] != '\0'; i++) welcome_buf[pos++] = prefix[i];
    for (int i = 0; name[i]   != '\0'; i++) welcome_buf[pos++] = name[i];
    welcome_buf[pos] = '\0';
    welcome_label.set_text(welcome_buf);

    // ── Build balance string ──────────────────────────────────────────────
    char bal_buf[64];
    const char* bal_prefix = "Balance: PKR ";
    pos = 0;
    for (int i = 0; bal_prefix[i] != '\0'; i++) bal_buf[pos++] = bal_prefix[i];
    char num_buf[32];
    double_to_char(balance, num_buf);
    for (int i = 0; num_buf[i] != '\0'; i++) bal_buf[pos++] = num_buf[i];
    bal_buf[pos] = '\0';
    balance_label.set_text(bal_buf);

    // ── Layout ────────────────────────────────────────────────────────────
    welcome_label.set_position(50, 20);
    balance_label.set_position(50, 50);
    divider_label.set_position(50, 80);

    float btn_x    = 220.f;
    float btn_y    = 110.f;
    float btn_step = 52.f;

    book_btn.set_position     (btn_x, btn_y + btn_step * 0);
    cancel_btn.set_position   (btn_x, btn_y + btn_step * 1);
    view_appt_btn.set_position(btn_x, btn_y + btn_step * 2);
    records_btn.set_position  (btn_x, btn_y + btn_step * 3);
    bills_btn.set_position    (btn_x, btn_y + btn_step * 4);
    pay_btn.set_position      (btn_x, btn_y + btn_step * 5);
    topup_btn.set_position    (btn_x, btn_y + btn_step * 6);
    logout_btn.set_position   (btn_x, btn_y + btn_step * 7);

    status_label.set_position(50, 550);

    // ── Button handlers ───────────────────────────────────────────────────

    book_btn.set_on_click([this]() {
        UIManager::instance().set_screen(new BookAppointmentScreen(patient_id));
    });

    cancel_btn.set_on_click([this]() {
        UIManager::instance().set_screen(new CancelAppointmentScreen(patient_id));
    });

    view_appt_btn.set_on_click([this]() {
        UIManager::instance().set_screen(new PatientAppointmentScreen(patient_id));
    });

    records_btn.set_on_click([this]() {
        UIManager::instance().set_screen(new ViewRecordsScreen(patient_id));
    });

    bills_btn.set_on_click([this]() {
        UIManager::instance().set_screen(new ViewBillsScreen(patient_id));
    });

    pay_btn.set_on_click([this]() {
        UIManager::instance().set_screen(new PayBillsScreen(patient_id));
    });

    topup_btn.set_on_click([this]() {
        UIManager::instance().set_screen(new TopUpScreen(patient_id));
    });

    logout_btn.set_on_click([this]() {
        UIManager::instance().set_screen(new LoginScreen());
    });
}

void PatientMenuScreen::refresh_balance_label()
{
    int pid = 0;
    for (int i = 0; patient_id[i] != '\0'; i++)
        pid = pid * 10 + (patient_id[i] - '0');

    Patient* ptr_p = HospitalSystem::instance().get_patients().find(pid);
    if (ptr_p == nullptr) return;

    char bal_buf[64];
    const char* prefix = "Balance: PKR ";
    int pos = 0;
    for (int i = 0; prefix[i] != '\0'; i++)      bal_buf[pos++] = prefix[i];
    char num_buf[32];
    double_to_char(ptr_p->get_balance(), num_buf);
    for (int i = 0; num_buf[i] != '\0'; i++)      bal_buf[pos++] = num_buf[i];
    bal_buf[pos] = '\0';
    balance_label.set_text(bal_buf);
}

void PatientMenuScreen::handle_event(sf::RenderWindow& window, const sf::Event& event)
{
    book_btn.handle_event     (event, window);
    cancel_btn.handle_event   (event, window);
    view_appt_btn.handle_event(event, window);
    records_btn.handle_event  (event, window);
    bills_btn.handle_event    (event, window);
    pay_btn.handle_event      (event, window);
    topup_btn.handle_event    (event, window);
    logout_btn.handle_event   (event, window);
}

void PatientMenuScreen::update() {}

void PatientMenuScreen::render(sf::RenderWindow& window)
{
    welcome_label.render(window);
    balance_label.render(window);
    divider_label.render(window);

    book_btn.render     (window);
    cancel_btn.render   (window);
    view_appt_btn.render(window);
    records_btn.render  (window);
    bills_btn.render    (window);
    pay_btn.render      (window);
    topup_btn.render    (window);
    logout_btn.render   (window);

    status_label.render(window);
}