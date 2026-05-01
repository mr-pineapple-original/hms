#include<iostream>

#include"hospital_exception.hpp"

#pragma once

// I was thinking about seeing here if the patien'ts funds are insufficent or not which would have been a horrible choice
class InsufficientFundsException : public HospitalException
{
    public:
        InsufficientFundsException();
};