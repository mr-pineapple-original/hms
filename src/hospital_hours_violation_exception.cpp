#include"hospital_hours_violation_exception.hpp"

HospitalHoursViolationException::HospitalHoursViolationException() : HospitalException(" Unfortunately the time slot that you chose is outside hospital operating hours :( ")
{
    
}