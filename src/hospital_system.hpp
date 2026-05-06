#include<iostream>
#include<ctime>

// #include "storage.hpp"
// #include "patient.hpp"
// #include "doctor.hpp"
// #include "admin.hpp"
// #include "appointment.hpp"
// #include "bill.hpp"
// #include "prescription.hpp"
// #include "storage.hpp"
// #include "file_handler.hpp"
// #include "hospital_exception.hpp"
// #include "hospital_exception.hpp"
// #include "hospital_hours_violation_exception.hpp"
// #include "file_not_found_exception.hpp"
// #include "insufficient_funds_exception.hpp"
// #include "invalid_input_exception.hpp"


// #pragma once

// class HospitalSystem
// {   
//     private:
//         Storage<Patient> patients;
//         Storage<Doctor> doctors; 
//         Storage<Admin> admins;
//         Storage<Appointment> appointments;
//         Storage<Bill> bills;
//         Storage<Prescription> prescriptions;

//         void display_main_menu();
//         void login_patient();
//         void login_doctor();
//         void login_admin();
//         void patient_menu(Patient* ptr_patient);
//         void doctor_menu(Doctor* ptr_doctor);
//         void admin_menu(Admin* ptr_doctor);

//     public:
//         void initialise();
//         void refreshh_data();
//         void run();
// };


#pragma once
#include "storage.hpp"
#include "patient.hpp"
#include "doctor.hpp"
#include "admin.hpp"
#include "appointment.hpp"
#include "bill.hpp"
#include "prescription.hpp"
#include "file_handler.hpp"
#include "validator.hpp"
#include "char_array_functions.hpp"
#include "hospital_exception.hpp"
#include "invalid_input_exception.hpp"
#include "slot_unavailable_exception.hpp"
#include "insufficient_funds_exception.hpp"
#include "file_not_found_exception.hpp"

class HospitalSystem 
{
    
private:
    Storage<Patient> patients;
    Storage<Doctor> doctors;
    Storage<Admin> admins;
    Storage<Appointment> appointments;
    Storage<Bill> bills;
    Storage<Prescription> prescriptions;

    // Respective menu functions
    void patient_session(Patient& patient);
    void doctor_session(Doctor& doctor);
    void admin_session(Admin& admin);
    

    // Main functions to be called
    void login_menu();
    void load_data();
    void save_data();

    // Helper functions
    void get_today_date(char* ptr_buffer);

    // Login functions
    void patient_login();
    void doctor_login();
    void admin_login();

    // Signup functions
    void patient_signup();
    void doctor_signup();
    void admin_signup();


    // Patient session handlers
    void book_appointment(Patient& patient);
    void cancel_appointment(Patient& patient);
    void view_appointments(Patient& patient);
    void view_medical_records(Patient& patient);
    void view_bills(Patient& patient);
    void pay_bill(Patient& patient);
    void top_up_balance(Patient& patient);


    // Doctor session handlers
    void view_today_appointments(Doctor& doctor);
    void mark_appointment_complete(Doctor& doctor);
    void mark_appointment_no_show(Doctor& doctor);
    void write_prescription(Doctor& doctor);
    void view_patient_history(Doctor& doctor);

    // Admin session handlers
    void add_doctor();
    void remove_doctor();
    void view_all_patients();
    void view_all_doctors();
    void view_all_dcotors();
    void view_all_appointments();
    void view_unpaid_bills();
    void discharge_patient();
    void view_security_log();
    void generate_daily_report();
public:
    HospitalSystem();
    void run(); // entry point
};
