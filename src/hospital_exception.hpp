#include<iostream>
#pragma once

class HospitalException : public std::exception
{
    protected:
        char m_message[200]; // It's only static because in the project it says for that
    public:
        HospitalException(const char* ptr_message);
        virtual const char* what() const noexcept override; 
        virtual ~HospitalException();
};