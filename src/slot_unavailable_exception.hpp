#include<iostream>

#include"hospital_exception.hpp"

#pragma once

class SlotUnavailableException : public HospitalException
{
    public:
        SlotUnavailableException();
};