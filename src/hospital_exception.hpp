#include<iostream>
#pragma once

class HospitalException
{
    protected:
        char m_message[200]; // It's only static because in the project it says for that
    public:
        HospitalException(char* ptr_message);
        virtual const char* what() const; 
        virtual ~HospitalException();
};