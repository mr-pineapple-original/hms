#include<iostream>
#pragma once

class Prescription
{
    private:
        int m_prescription_id;
        int m_appointment_id;
        int m_patient_id;
        int m_doctor_id;

        char* m_ptr_date; 
        char* m_ptr_medicine;
        char* m_ptr_doc_note; //  Doc note is a crazy name 

        void set_date(char* ptr_date);
        void set_medicine(char* ptr_medicine);
        void set_doctor_note(char* ptr_doc_note);

    public:
        Prescription();
        Prescription(int prescription_id, int appointment_id, int patient_id, int doctor_id, char* ptr_date, char* ptr_medicine, char* ptr_doc_note);
        Prescription(const Prescription& obj);

        Prescription& operator=(const Prescription& obj);

        bool operator==(const Prescription& obj) const;
        friend std::ostream& operator<<(std::ostream& output, const Prescription& obj);

        int get_id() const;
        int get_appointment_id() const;
        int get_doctor_id() const;
        int get_patient_id() const;

        char* get_date() const;
        char* get_medicine() const;
        char* get_doctor_note() const;

        void set_prescription(int prescription_id, int appointment_id, int patient_id, int doctor_id, char* ptr_date, char* ptr_medicine, char* ptr_doc_note);

        ~Prescription();
};