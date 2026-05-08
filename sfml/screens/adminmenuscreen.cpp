#include "adminmenuscreen.hpp"
#include "loginscreen.hpp"
#include "loginscreen.hpp"
#include "adddoctorscreen.hpp"
#include "removedoctorscreen.hpp"
#include "viewpatientsscreen.hpp"
#include "viewdoctorsscreen.hpp"
#include "viewappointmentsscreen.hpp"
#include "unpaidbillsscreen.hpp"
#include "dischargepatientscreen.hpp"
#include "securitylogscreen.hpp"
#include "dailyreportscreen.hpp"

AdminMenuScreen::AdminMenuScreen()
    : heading_label("Admin Panel -- MediCore"),
      divider_label("======================"),
      add_doctor_btn    ("1. Add Doctor",          220, 40),
      remove_doctor_btn ("2. Remove Doctor",        220, 40),
      view_patients_btn ("3. View All Patients",    220, 40),
      view_doctors_btn  ("4. View All Doctors",     220, 40),
      view_appts_btn    ("5. View All Appointments",220, 40),
      unpaid_bills_btn  ("6. View Unpaid Bills",    220, 40),
      discharge_btn     ("7. Discharge Patient",    220, 40),
      security_log_btn  ("8. Security Log",         220, 40),
      daily_report_btn  ("9. Daily Report",         220, 40),
      logout_btn        ("10. Logout",              220, 40),
      status_label("")
{
    // ── Layout — two columns of 5 ─────────────────────────────────────────
    // Left column: options 1-5   Right column: options 6-10
    heading_label.set_position(50, 20);
    divider_label.set_position(50, 50);

    float left_x   = 80.f;
    float right_x  = 450.f;
    float start_y  = 100.f;
    float btn_step = 80.f;

    add_doctor_btn.set_position    (left_x,  start_y + btn_step * 0);
    remove_doctor_btn.set_position (left_x,  start_y + btn_step * 1);
    view_patients_btn.set_position (left_x,  start_y + btn_step * 2);
    view_doctors_btn.set_position  (left_x,  start_y + btn_step * 3);
    view_appts_btn.set_position    (left_x,  start_y + btn_step * 4);

    unpaid_bills_btn.set_position  (right_x, start_y + btn_step * 0);
    discharge_btn.set_position     (right_x, start_y + btn_step * 1);
    security_log_btn.set_position  (right_x, start_y + btn_step * 2);
    daily_report_btn.set_position  (right_x, start_y + btn_step * 3);
    logout_btn.set_position        (right_x, start_y + btn_step * 4);

    status_label.set_position(50, 570);

    // ── Button handlers ───────────────────────────────────────────────────

    add_doctor_btn.set_on_click([this]() {
       UIManager::instance().set_screen(new AddDoctorScreen());
    });

    remove_doctor_btn.set_on_click([this]() {
        UIManager::instance().set_screen(new RemoveDoctorScreen());
    });

    view_patients_btn.set_on_click([this]() {
        UIManager::instance().set_screen(new ViewPatientsScreen());
    });

    view_doctors_btn.set_on_click([this]() {
        UIManager::instance().set_screen(new ViewDoctorsScreen());
    });

    view_appts_btn.set_on_click([this]() {
        UIManager::instance().set_screen(new ViewAppointmentsScreen());
    });

    unpaid_bills_btn.set_on_click([this]() {
        UIManager::instance().set_screen(new UnpaidBillsScreen());
    });

    discharge_btn.set_on_click([this]() {
        UIManager::instance().set_screen(new DischargePatientScreen());
    });

    security_log_btn.set_on_click([this]() {
        UIManager::instance().set_screen(new SecurityLogScreen());
    });

    daily_report_btn.set_on_click([this]() {
        UIManager::instance().set_screen(new DailyReportScreen());
    });

    logout_btn.set_on_click([this]() {
        UIManager::instance().set_screen(new LoginScreen());
    });
}

void AdminMenuScreen::handle_event(sf::RenderWindow& window, const sf::Event& event) {
    add_doctor_btn.handle_event    (event, window);
    remove_doctor_btn.handle_event (event, window);
    view_patients_btn.handle_event (event, window);
    view_doctors_btn.handle_event  (event, window);
    view_appts_btn.handle_event    (event, window);
    unpaid_bills_btn.handle_event  (event, window);
    discharge_btn.handle_event     (event, window);
    security_log_btn.handle_event  (event, window);
    daily_report_btn.handle_event  (event, window);
    logout_btn.handle_event        (event, window);
}

void AdminMenuScreen::update() {}

void AdminMenuScreen::render(sf::RenderWindow& window) {
    heading_label.render(window);
    divider_label.render(window);

    add_doctor_btn.render    (window);
    remove_doctor_btn.render (window);
    view_patients_btn.render (window);
    view_doctors_btn.render  (window);
    view_appts_btn.render    (window);
    unpaid_bills_btn.render  (window);
    discharge_btn.render     (window);
    security_log_btn.render  (window);
    daily_report_btn.render  (window);
    logout_btn.render        (window);

    status_label.render(window);
}
