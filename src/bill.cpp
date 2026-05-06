#include "bill.hpp"
#include"char_array_functions.hpp"

Bill::Bill()
{
    m_bill_id = 0;
    m_patient_id = 0;
    m_appointment_id = 0;
    m_amount = 0.0;

    m_ptr_status = nullptr;
    m_ptr_date = nullptr;
}

Bill::Bill(int bill_id, int patient_id, int appointment_id, double amount, char* ptr_status, char* ptr_date)
{
    m_bill_id = bill_id;
    m_patient_id = patient_id;
    m_appointment_id = appointment_id;
    m_amount = amount;

    m_ptr_status = nullptr;
    m_ptr_date = nullptr;

    copy_array(m_ptr_status, ptr_status, get_char_arr_size(ptr_status) + 1);
    copy_array(m_ptr_date, ptr_date, get_char_arr_size(ptr_date) + 1);
}

Bill::Bill(const Bill& obj)
{
    m_bill_id = obj.m_bill_id;
    m_patient_id = obj.m_patient_id;
    m_appointment_id = obj.m_appointment_id;
    m_amount = obj.m_amount;

    m_ptr_status = nullptr;
    m_ptr_date = nullptr;

    copy_array(m_ptr_status, obj.m_ptr_status, get_char_arr_size(obj.m_ptr_status) + 1);
    copy_array(m_ptr_date, obj.m_ptr_date, get_char_arr_size(obj.m_ptr_date) + 1);
}

Bill& Bill::operator=(const Bill& obj)
{
    if (this != &obj)
    {
        m_bill_id = obj.m_bill_id;
        m_patient_id = obj.m_patient_id;
        m_appointment_id = obj.m_appointment_id;
        m_amount = obj.m_amount;

        if (m_ptr_status != nullptr) 
            delete[] m_ptr_status;
        if (m_ptr_date != nullptr) 
            delete[] m_ptr_date;

        m_ptr_status = nullptr;
        m_ptr_date = nullptr;

        copy_array(m_ptr_status, obj.m_ptr_status, get_char_arr_size(obj.m_ptr_status) + 1);
        copy_array(m_ptr_date, obj.m_ptr_date, get_char_arr_size(obj.m_ptr_date) + 1);
    }
    return *this;
}

bool Bill::operator==(const Bill& obj) const
{
    if(m_bill_id != obj.m_bill_id)
    {
        return false;
    }
    return true;
}

std::ostream& operator<<(std::ostream& output, const Bill& obj)
{
    output << obj.m_bill_id << ",";
    output << obj.m_patient_id << ",";
    output << obj.m_appointment_id << ",";
    output << obj.m_amount << ",";
    output << obj.m_ptr_status << ",";
    output << obj.m_ptr_date;
    return output;
}

void Bill::set_status(char* ptr_status)
{
    // This should not happen
    // But we have to try to see if it debugs
    if (ptr_status == m_ptr_status)
        return;

    if (m_ptr_status != nullptr) 
        delete[] m_ptr_status;
    
    m_ptr_status = nullptr;
    copy_array(m_ptr_status, ptr_status, get_char_arr_size(ptr_status) + 1);
}

void Bill::set_date(char* ptr_date)
{
    // This should not happen
    // But we have to try to see if it debugs
    if (ptr_date == m_ptr_date)
        return;

    if (m_ptr_date != nullptr) 
        delete[] m_ptr_date;

    m_ptr_date = nullptr;
    copy_array(m_ptr_date, ptr_date, get_char_arr_size(ptr_date) + 1);
}

void Bill::set_bill(int bill_id, int patient_id, int appointment_id, double amount, char* ptr_status, char* ptr_date)
{
    m_bill_id = bill_id;
    m_patient_id = patient_id;
    m_appointment_id = appointment_id;
    m_amount = amount;

    set_status(ptr_status);
    set_date(ptr_date);
}


int Bill::get_id() const 
{ 
    return m_bill_id; 
}

int Bill::get_patient_id() const 
{ 
    return m_patient_id; 
}

int Bill::get_appointment_id() const 
{ 
    return m_appointment_id; 
}

double Bill::get_amount() const 
{ 
    return m_amount;
}

char* Bill::get_status() const 
{ 
    return m_ptr_status;
}

char* Bill::get_date() const 
{ 
    return m_ptr_date;
}

Bill::~Bill()
{
    delete[] m_ptr_status;
    delete[] m_ptr_date;

    m_ptr_status = nullptr;
    m_ptr_date = nullptr;
}
