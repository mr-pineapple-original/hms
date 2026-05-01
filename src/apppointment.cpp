#include"appointment.hpp"
#include"char_array_functions.hpp"
#include"invalid_input_exception.hpp"
#include"slot_unavailable_exception.hpp"
#include"hospital_hours_violation_exception.hpp"
#include"validator.hpp"

Appointment::Appointment()
{
    m_appointment_id = 0;
    m_patient_id = 0;
    m_doctor_id = 0;

    m_ptr_date = nullptr;
    m_ptr_time_slot = nullptr;
    m_ptr_status = nullptr;
}

Appointment::Appointment(int appointment_id, int patient_id, int doctor_id, char* ptr_date, char* ptr_time, char* ptr_status)
{
    m_appointment_id = appointment_id;
    m_patient_id = patient_id;
    m_doctor_id = doctor_id;

    m_ptr_date = nullptr;
    m_ptr_time_slot = nullptr;
    m_ptr_status = nullptr;
    
    copy_array(m_ptr_date, ptr_date, get_char_arr_size(ptr_date) + 1);
    copy_array(m_ptr_time_slot, ptr_time, get_char_arr_size(ptr_time) + 1);
    copy_array(m_ptr_status, ptr_status, get_char_arr_size(ptr_status) + 1);
}

Appointment::Appointment(const Appointment& obj)
{
    m_appointment_id = obj.m_appointment_id;
    m_patient_id = obj.m_patient_id;
    m_doctor_id = obj.m_doctor_id;
    
    m_ptr_date = nullptr;
    m_ptr_time_slot = nullptr;
    m_ptr_status = nullptr;

    copy_array(m_ptr_date, obj.m_ptr_date, get_char_arr_size(obj.m_ptr_date) + 1);
    copy_array(m_ptr_time_slot, obj.m_ptr_time_slot, get_char_arr_size(obj.m_ptr_time_slot) + 1);
    copy_array(m_ptr_status, obj.m_ptr_status, get_char_arr_size(obj.m_ptr_status) + 1);
}

Appointment& Appointment::operator=(const Appointment& obj)
{
    if (this != &obj)
    {
        m_appointment_id = obj.m_appointment_id;
        m_patient_id = obj.m_patient_id;
        m_doctor_id = obj.m_doctor_id;
        
        m_ptr_date = nullptr;
        m_ptr_time_slot = nullptr;
        m_ptr_status = nullptr;

        copy_array(m_ptr_date, obj.m_ptr_date, get_char_arr_size(obj.m_ptr_date) + 1);
        copy_array(m_ptr_time_slot, obj.m_ptr_time_slot, get_char_arr_size(obj.m_ptr_time_slot) + 1);
        copy_array(m_ptr_status, obj.m_ptr_status, get_char_arr_size(obj.m_ptr_status) + 1);
    }
    return *this;
}

bool Appointment::operator==(const Appointment& obj) const
{
    if (m_doctor_id != obj.m_doctor_id)
        return false;

    int size1 = get_char_arr_size(m_ptr_date);
    int size2 = get_char_arr_size(obj.m_ptr_date);

    if (size1 != size2)
        return false;

    for (int i = 0; i < size1; i++)
    {
        if (*(m_ptr_date + i) != *(obj.m_ptr_date + i))
            return false;
    }

    int t1 = get_char_arr_size(m_ptr_time_slot);
    int t2 = get_char_arr_size(obj.m_ptr_time_slot);

    if (t1 != t2)
        return false;

    for (int i = 0; i < t1; i++)
    {
        if (*(m_ptr_time_slot + i) != *(obj.m_ptr_time_slot + i))
            return false;
    }


    if(is_cancelled(m_ptr_status) || is_cancelled(obj.m_ptr_status))
    {
        return false;
    }

    return true;
}

std::ostream& operator<<(std::ostream& output, const Appointment& obj)
{
    output << obj.m_appointment_id << ",";
    output << obj.m_patient_id << ",";
    output << obj.m_doctor_id << ",";
    output << obj.m_ptr_date << ",";
    output << obj.m_ptr_time_slot << ",";
    output << obj.m_ptr_status;

    return output;
}

int Appointment::get_id() const
{
    return m_appointment_id;
}

int Appointment::get_doctor_id() const
{
    return m_doctor_id;
}

int Appointment::get_patient_id() const
{
    return m_patient_id;
}

char* Appointment::get_date() const
{
    return m_ptr_date;
}

char* Appointment::get_time() const
{
    return m_ptr_time_slot;
}

char* Appointment::get_status() const
{
    return m_ptr_status;
}

void Appointment::set_date(char* ptr_date)
{
    if(m_ptr_date != nullptr)
        delete[] m_ptr_date;

    m_ptr_date = nullptr;
    int size = get_char_arr_size(ptr_date);
    copy_array(m_ptr_date, ptr_date, size + 1);
}

void Appointment::set_time_slot(char* ptr_time_slot)
{
    if(ptr_time_slot == nullptr)
        throw InvalidInputException();

    if(!Validator::validate_time_format(ptr_time_slot))
    {
        throw InvalidInputException();
    }

    if(!Validator::is_within_operating_hours(ptr_time_slot))
    {
        throw HospitalHoursViolationException();
    }

    if(m_ptr_time_slot != nullptr)
        delete[] m_ptr_time_slot;

    m_ptr_time_slot = nullptr;
    copy_array(m_ptr_time_slot, ptr_time_slot, get_char_arr_size(ptr_time_slot) + 1);
}

void Appointment::set_status(char* ptr_status)
{
    if(m_ptr_status != nullptr)
        delete[] m_ptr_status;

    m_ptr_status = nullptr;
    copy_array(m_ptr_status, ptr_status, get_char_arr_size(ptr_status) + 1);
}

void Appointment::set_appointment(int appointment_id, int patient_id, int doctor_id, char* ptr_date, char* ptr_time_slot, char* ptr_status)
{
    m_appointment_id = appointment_id;
    m_patient_id = patient_id;
    m_doctor_id = doctor_id;

    set_date(ptr_date);
    set_time_slot(ptr_time_slot);
    set_status(ptr_status);

}

Appointment::~Appointment()
{
    delete[] m_ptr_date;
    delete[] m_ptr_status;
    delete[] m_ptr_time_slot;

    m_ptr_date = nullptr;
    m_ptr_status = nullptr;
    m_ptr_time_slot = nullptr;
}