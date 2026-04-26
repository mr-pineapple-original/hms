#include<iostream>
#pragma once

class Appointment
{
    private:
        int m_appointment_id;  
        int m_patient_id;
        int m_doctor_id;
    
        char* m_ptr_date;
        char* m_ptr_time_slot;
        char* m_ptr_status;

        void set_date(char* ptr_date);
        void set_time_slot(char* ptr_time_slot);
        void set_status(char* ptr_status);

    public:
        Appointment();
        Appointment(int appointment_id, int patient_id, int doctor_id, char* ptr_date, char* ptr_time_slot, char* ptr_status);
        Appointment(const Appointment& obj);
        
        Appointment& operator=(const Appointment& obj);

        bool operator==(const Appointment& obj) const;
        friend std::ostream& operator<<(std::ostream& output, const Appointment& obj);

        int get_id() const; // We cant name it get_appointment_id() cause of the template class Storage so we will make it get_id() to have a common interface
        int get_doctor_id() const;
        int get_patient_id() const;
        char* get_date() const;
        char* get_time() const;
        char* get_status() const;


        void Appointment::set_appointment(int appointment_id, int patient_id, int doctor_id, char* ptr_date, char* ptr_time_slot, char* ptr_status);

        ~Appointment();
};