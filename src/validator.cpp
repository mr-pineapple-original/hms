#include"validator.hpp"
#include"invalid_input_exception.hpp"

// I could have used an online clock
// But probably that would make our application entirely dependent online 
int Validator::current_year = 2026;
// None of these will return false
// Either they will return true or error exceptions :/
bool Validator::validate_id(int id)
{
    if(id <= 0)
    {

        throw InvalidInputException();
    }
    return true;
}

bool Validator::validate_menu_choice(int choice, int min, int max)
{
    if(choice > max || choice < min)
    {
        throw InvalidInputException();
    }
    return true;
}

bool Validator::validate_positive_int(int value)
{
    if(value < 0)
    {
        throw InvalidInputException();
    }
    return true;
}

bool Validator::validate_positive_float(float value)
{
    if(value < 0)
    {
        throw InvalidInputException();
    }
    return true;
}

bool Validator::validate_positive_double(double value)
{
    if(value < 0)
    {
        throw InvalidInputException();
    }
    return true;
}

bool Validator::validate_contact(const char* ptr_contact)
{
    // FIst 2 digits for a PK number start from 03XX-XXXXXXX
    if(*(ptr_contact + 0) != '0' || *(ptr_contact + 1) != '3')
    {
        throw InvalidInputException();
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
            throw InvalidInputException();
        }
    }
    if(length == 11)
    {
        return true;
    }

    throw InvalidInputException();
}

bool Validator::validate_date(const char* ptr_date)
{
    if (ptr_date == nullptr)
        throw InvalidInputException();

    if (*(ptr_date + 2) != '-' || *(ptr_date + 5) != '-')
        throw InvalidInputException();

    for (int i = 0; i < 10; i++)
    {
        if (i == 2 || i == 5)
            continue;

        if (*(ptr_date + i) < '0' || *(ptr_date + i) > '9')
            throw InvalidInputException();
    }

    if (*(ptr_date + 10) != '\0')
        throw InvalidInputException();

    // Extracting digits
    int day =
        (*(ptr_date + 0) - '0') * 10 +
        (*(ptr_date + 1) - '0');

    int month =
        (*(ptr_date + 3) - '0') * 10 +
        (*(ptr_date + 4) - '0');

    int year =
        (*(ptr_date + 6) - '0') * 1000 +
        (*(ptr_date + 7) - '0') * 100 +
        (*(ptr_date + 8) - '0') * 10 +
        (*(ptr_date + 9) - '0');

    if (month < 1 || month > 12)
        throw InvalidInputException();

    if (year < current_year)
        throw InvalidInputException();

   
    int max_days;

    if (month == 4 || month == 6 || month == 9 || month == 11)
        max_days = 30;
    else if (month == 2)
        max_days = is_leap_year(year) ? 29 : 28;
    else
        max_days = 31;

    if (day < 1 || day > max_days)
        throw InvalidInputException();

    return true;
}

bool Validator::is_leap_year(int year)
{
    if(year % 400 == 0)
    {
        return true;
    }

    if(year % 100 == 0)
    {
        return false;
    }
    if(year % 4 == 0)
    {
        return true;
    }

    return false;
}

bool Validator::validate_time_slot(const char* ptr_time)
{
    if (!validate_time_format(ptr_time))
        return false;

    if(!is_within_operating_hours(ptr_time))
        return false;

    return true;
}

bool Validator::validate_time_format(const char* ptr_time)
{
    if (ptr_time == nullptr)
        return false;

    // Checking for HH:MM format
    if (*(ptr_time + 2) != ':')
        return false;

    // Check digits only
    for (int i = 0; i < 5; i++)
    {
        if (i == 2) 
            continue;

        if (*(ptr_time + i) < '0' || *(ptr_time + i) > '9')
            return false;
    }

    // Must end exactly here
    if (*(ptr_time + 5) != '\0')
        return false;

    return true;
}

bool Validator::is_within_operating_hours(const char* ptr_time)
{
    if (ptr_time == nullptr)
        return false;

    // I never knew we could have done that :(
    const char* valid_slots[] =
    {
        "09:00", "10:00", "11:00", "12:00",
        "13:00", "14:00", "15:00", "16:00"
    };

    for (int i = 0; i < 8; i++)
    {
        bool match = true;

        for (int j = 0; valid_slots[i][j] != '\0'; j++)
        {
            if (ptr_time[j] != valid_slots[i][j])
            {
                match = false;
                break;
            }
        }

        if (match && ptr_time[5] == '\0')
            return true;
    }

    return false;
}


bool Validator::validate_age(int age)
{
    if(age <= 0)
    {
        throw InvalidInputException();
    }
    
    return true;
}