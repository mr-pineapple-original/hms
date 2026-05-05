// #include<iostream>

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

class HospitalSystem {
private:
    Storage<Patient> patients;
    Storage<Doctor> doctors;
    Storage<Admin> admins;
    Storage<Appointment> appointments;
    Storage<Bill> bills;
    Storage<Prescription> prescriptions;

    void patient_session(Patient& patient);
    void doctor_session(Doctor& doctor);
    void admin_session(Admin& admin);
    
    void login_menu();
    void load_data();
    void save_data();

    void patient_login();
    void doctor_login();
    void admin_login();

    void patient_signup();
    void doctor_signup();
    void admin_signup();


public:
    HospitalSystem();
    void run(); // entry point
};
