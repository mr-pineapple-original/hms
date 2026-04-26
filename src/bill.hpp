#include <iostream>
#pragma once

class Bill
{
    private:
        int m_bill_id;
        int m_patient_id;
        int m_appointment_id;
    
        double m_amount;

        char* m_ptr_status;   // paid / unpaid / cancelled
        char* m_ptr_date;

        void set_status(char* ptr_status);
        void set_date(char* ptr_date);

    public:
        Bill();
        Bill(int bill_id, int patient_id, int appointment_id, double amount, char* ptr_status, char* ptr_date);
        Bill(const Bill& obj);
        
        Bill& operator=(const Bill& obj);

        bool operator==(const Bill& obj) const;
        friend std::ostream& operator<<(std::ostream& output, const Bill& obj);

        int get_id() const; // We cant name it get_bill_id() cause of the template class Storage so we will make it get_id() to have a common interface
        int get_patient_id() const;
        int get_appointment_id() const;
        double get_amount() const;
        char* get_status() const;
        char* get_date() const;


        void set_bill(int bill_id, int patient_id, int appointment_id, double amount, char* ptr_status, char* ptr_date);

        ~Bill();
};
