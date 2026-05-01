#include<iostream>

#include"hospital_exception.hpp"

class HospitalHoursViolationException : public HospitalException
{
    public:
        HospitalHoursViolationException();
};