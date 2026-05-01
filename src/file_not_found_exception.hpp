#include<iostream>

#include"hospital_exception.hpp"

#pragma once

class FileNotFoundException : public HospitalException
{
    public:
        FileNotFoundException();
};