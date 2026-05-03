#include<iostream>
#include<fstream>
#include<cstdio>
#pragma once

#include"storage.hpp"
#include"patient.hpp"
#include"doctor.hpp"
#include"admin.hpp"
#include"appointment.hpp"
#include"bill.hpp"
#include"prescription.hpp"

// We are gonna make it a static utility class
class FileHandler
{
    private:
        // Completely rewrite data in a file by making a temp file and then renaming it and reading from the storage ( It is the helper function that will be used in all the update functions )
        template<typename Entity>
        static void rewrite_file(const Storage<Entity>& entity, const char* ptr_file_name);
    
    public:
        // Loading is to read data from the file and add them into the storage 
        static void load_patients(Storage<Patient>& patients, const char* ptr_file_name);
        static void load_admins(Storage<Admin>& admins, const char* ptr_file_name);
        static void load_appointments(Storage<Appointment>& appointments, const char* ptr_file_name);
        static void load_bills(Storage<Bill>& bills, const char* ptr_file_name);
        static void load_doctors(Storage<Doctor>& doctors, const char* ptr_file_name);
        static void load_prescriptions(Storage<Prescription>& prescriptions, const char* ptr_file_name);

        // Appending is to read data from the object and append them into the file
        static void append_patient(const Patient& patient, const char* ptr_file_name);
        static void append_admin(const Admin& admin, const char* ptr_file_name);
        static void append_appointment(const Appointment& appointment, const char* ptr_file_name);
        static void append_bill(const Bill& bill, const char* ptr_file_name);
        static void append_doctor(const Doctor& doctor, const char* ptr_file_name);
        static void append_prescription(const Prescription& prescription, const char* ptr_file_name);

        // Updating is to read from the storage and updating the records in the file
        static void update_patients(const Storage<Patient>& patients, const char* ptr_file_name);
        static void update_admins(const Storage<Admin>& admins, const char* ptr_file_name);
        static void update_appointments(const Storage<Appointment>& appointments, const char* ptr_file_name);
        static void update_bills(const Storage<Bill>& bills, const char* ptr_file_names);
        static void update_doctors(const Storage<Doctor>& doctors, const char* ptr_file_names);
        static void update_prescriptions(const Storage<Prescription>& prescriptions, const char* ptr_file_names);

        // Generating new id that can be used by reading from the storage and returning + 1 of the last id
        template<typename Entity>
        static int generate_new_id(const Storage<Entity>& entity);

        static bool validate_patient(const char* id, const char* password, const char* ptr_file_name);
        static bool validate_doctor(const char* id, const char* password, const char* ptr_file_name);
        static bool validate_admin(const char* id, const char* password, const char* ptr_file_name);
        static bool validate_admin(const char* id, const char* password, const char* ptr_file_name);

        static void log_security_attempt(const char* role, int entered_id, const char* result);
};  