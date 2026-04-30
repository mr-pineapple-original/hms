#include<iostream>

#include"hospital_exception.hpp"

#pragma once

class SlotUnavaialableException : public HospitalException
{
    public:
        SlotUnavaialableException();
};