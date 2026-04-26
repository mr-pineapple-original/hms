#include"validator.hpp"

int Validator::current_year = 2026;
bool Validator::validate_id(int id)
{
    if(id <= 0)
    {
        return false;
    }
    return true;
}

bool Validator::validate_menu_choice(int choice, int min, int max)
{
    if(choice > max || choice < min)
    {
        return false;
    }
    return true;
}

bool Validator::validate_positive_float(float value)
{
    if(value < 0)
    {
        return false;
    }
    return true;
}

bool Validator::validate_positive_double(double value)
{
    if(value < 0)
    {
        return false;
    }
    return true;
}

bool Validator::validate_contact(const char* ptr_contact)
{
    // FIst 2 digits for a PK number start from 03XX-XXXXXXX
    if(*(ptr_contact + 0) != '0' || *(ptr_contact + 1) != '3')
    {
        return false;
    }

    int length = 0;
    for(int i = 0; *(ptr_contact + i) != '\0'; i++)
    {
        if(*(ptr_contact + i) >= '0' && *(ptr_contact + i) <= '9')
        {
            length++;
        }
        else
        {
            return false;
        }
    }
    if(length == 11)
    {
        return true;
    }
    return false;
}

bool Validator::validate_date(const char* ptr_date)
{
    // Needs to be fixed 
    if (!ptr_date) return false;

    if (*(ptr_date + 2) != '-' || *(ptr_date + 5) != '-')
        return false;

    int day = (*(ptr_date + 0) - '0') * 10 + (*(ptr_date + 1) - '0');

    int month = (*(ptr_date + 3) - '0') * 10 + (*(ptr_date + 4) - '0');

    int year = (*(ptr_date + 6) - '0') * 1000 + (*(ptr_date + 7) - '0') * 100 + (*(ptr_date + 8) - '0') * 10 + (*(ptr_date + 9) - '0');

    if (day < 1 || day > 31) 
        return false;
    if (month < 1 || month > 12) 
        return false;
    if (year < current_year) 
        return false;

    return true;
}

