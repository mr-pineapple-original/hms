#include<iostream>
#pragma once
// It is also a static utility class
class Validator
{
    private:
        static int current_year;
        static bool is_leap_year(int year);
    public:
        static bool validate_id(int id);
        static bool validate_menu_choice(int choice, int min, int max);
        static bool validate_contact(const char* ptr_contact);
        static bool validate_positive_float(float value);
        static bool validate_positive_double(double value);
        static bool validate_time_slot(const char* ptr_time_slot); // IDK how to know at what time slots the doctor is free at
        static bool validate_date(const char* ptr_date);
};