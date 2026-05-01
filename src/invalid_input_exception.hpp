#include"hospital_exception.hpp"

#pragma once

class InvalidInputException : public HospitalException
{
    public:
        InvalidInputException();
};
