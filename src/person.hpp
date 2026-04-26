#pragma once
// Abstract Base Class to avoid repetition

static const char* male = "Male";
static const char* female = "Female";

class Person
{
    protected:
        int m_age;    
        const char* m_gender;
        
        char* m_ptr_name;
        
        // Credientials
        int m_id;
        char* m_ptr_password;
    public:
        Person();
        Person(int id, char* ptr_password, char* ptr_name, const char* gender, int m_age);
        Person(const Person& obj);
        Person& operator=(const Person& obj);

        virtual void display() = 0; // So child classes override it
        virtual void menu() = 0;    // So child classes override it
        
        int get_id() const;
        char* get_name() const;
        char* get_password() const;
        int get_age() const;
        const char* get_gender() const;
        
        virtual ~Person();
};