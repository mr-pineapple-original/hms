#pragma once
// Abstract Base Class to avoid repetition
class Person
{
    protected:
        const char* m_gender;
        int m_age;
        char* m_ptr_name;
        
        // Credientials
        int m_id;
        char* ptr_password;
    public:
        Person();
        Person(int m_id, char* ptr_password, char* ptr_name, const char* gender, int m_age);
        virtual void display() = 0; // So child classes override it
        virtual void menu() = 0;    
};