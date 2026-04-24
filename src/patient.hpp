#include<iostream>
#include"person.hpp"
#pragma once

class Patient : public Person
{
    private:
        char* m_ptr_contact;
        double m_balance;
    public:
        Patient();
        Patient(int id, char* ptr_password, char* ptr_name, const char* gender, int m_age, char* ptr_contact, double balance);
        Patient(const Patient& obj);
        Patient& operator=(const Patient& obj);

        Patient& operator+=(double balance);
        Patient& operator-= (double balance);
        bool operator==(const Patient& obj) const;
        friend std::ostream& operator<<(std::ostream& output, const Patient& obj);
        friend std::istream& operator>>(std::istream& input, Patient& obj);

        void display() override;
        void menu() override;

        char* get_contact() const;
        double get_balance() const;

        ~Patient();
};

