#include<iostream>
#include"person.hpp"
#pragma once

class Admin : public Person
{
    public:
        Admin();
        Admin(int id, char* ptr_password);
        Admin(const Admin& obj);

        Admin& operator=(const Admin& obj);
        
        void display() override;
        void menu() override;
        bool authenticate(int id, char* ptr_password) const;
        
        friend std::ostream& operator<<(std::ostream& output, const Admin& obj);

        ~Admin();
};  
