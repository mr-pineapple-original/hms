#include<iostream>
#include"person.hpp"
#pragma once

class Doctor : public Person
{
private:
    double m_fee;
    
    char* m_ptr_specialization;
    char* m_ptr_contact;
    

public:
    Doctor();
    Doctor(int id, char* password, char* name, const char* gender, int age, char* specialization, char* contact, double fee);
    Doctor(const Doctor& obj);
    Doctor& operator=(const Doctor& obj);

    bool operator==(const Doctor& obj) const;

    friend std::istream& operator>>(std::istream& input, Doctor& obj);
    friend std::ostream& operator<<(std::ostream& output, const Doctor& obj);

    void display() override;
    void menu() override;

    char* get_specialization() const;
    char* get_contact() const;
    double get_fee() const;

    ~Doctor();
};