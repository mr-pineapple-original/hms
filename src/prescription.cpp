#include"prescription.hpp"
#include"char_array_functions.hpp"

Prescription::Prescription()
{
    m_prescription_id = 0;
    m_appointment_id = 0;
    m_patient_id = 0;
    m_doctor_id = 0;

    m_ptr_date = nullptr;
    m_ptr_medicine = nullptr;
    m_ptr_doc_note = nullptr;
}

Prescription::Prescription(int prescription_id, int appointment_id, int patient_id, int doctor_id, char* ptr_date, char* ptr_medicine, char* ptr_doc_note)
{
    m_prescription_id = prescription_id;
    m_appointment_id = appointment_id;
    m_patient_id = patient_id;
    m_doctor_id = doctor_id;

    m_ptr_date = nullptr;
    m_ptr_medicine = nullptr;
    m_ptr_doc_note = nullptr;

    set_date(ptr_date);
    set_medicine(ptr_medicine);
    set_doctor_note(ptr_doc_note);
}

Prescription::Prescription(const Prescription& obj)
{
    m_prescription_id = obj.m_prescription_id;
    m_appointment_id = obj.m_appointment_id;
    m_patient_id = obj.m_patient_id;
    m_doctor_id = obj.m_doctor_id;

    m_ptr_date = nullptr;
    m_ptr_medicine = nullptr;
    m_ptr_doc_note = nullptr;

    set_date(obj.m_ptr_date);
    set_medicine(obj.m_ptr_medicine);
    set_doctor_note(obj.m_ptr_doc_note);
}

Prescription& Prescription::operator=(const Prescription& obj)
{
    if (this != &obj)
    {
        m_prescription_id = obj.m_prescription_id;
        m_appointment_id = obj.m_appointment_id;
        m_patient_id = obj.m_patient_id;
        m_doctor_id = obj.m_doctor_id;

        if(m_ptr_date != nullptr)
            delete[] m_ptr_date;
        
        if(m_ptr_medicine != nullptr)
            delete[] m_ptr_medicine;
        
        if(m_ptr_doc_note != nullptr)
            delete[] m_ptr_doc_note;

        m_ptr_date = nullptr;
        m_ptr_medicine = nullptr;
        m_ptr_doc_note = nullptr;

        set_date(obj.m_ptr_date);
        set_medicine(obj.m_ptr_medicine);
        set_doctor_note(obj.m_ptr_doc_note);
    }
    return *this;
}

bool Prescription::operator==(const Prescription& obj) const
{
    if(m_prescription_id != obj.m_prescription_id)
    {
        return false;
    }

    return true;
}

std::ostream& operator<<(std::ostream& output, const Prescription& obj)
{
    output << obj.m_prescription_id << ",";
    output << obj.m_appointment_id << ",";
    output << obj.m_patient_id << ",";
    output << obj.m_doctor_id << ",";
    output << obj.m_ptr_date << ",";
    output << obj.m_ptr_medicine << ",";
    output << obj.m_ptr_doc_note;

    return output;
}

int Prescription::get_prescription_id() const
{
    return m_prescription_id;
}

int Prescription::get_appointment_id() const
{
    return m_appointment_id;
}

int Prescription::get_doctor_id() const
{
    return m_doctor_id;
}

char* Prescription::get_date() const
{
    return m_ptr_date;
}

char* Prescription::get_medicine() const
{
    return m_ptr_medicine;
}

char* Prescription::get_doctor_note() const
{
    return m_ptr_doc_note;
}

void Prescription::set_date(char* ptr_date)
{
    if (m_ptr_date != nullptr)
        delete[] m_ptr_date;

    m_ptr_date = nullptr;

    copy_array(m_ptr_date, ptr_date, get_char_arr_size(ptr_date) + 1);
}

void Prescription::set_medicine(char* ptr_medicine)
{
    if (m_ptr_medicine != nullptr)
        delete[] m_ptr_medicine;

    m_ptr_medicine = nullptr;

    copy_array(m_ptr_medicine, ptr_medicine, get_char_arr_size(ptr_medicine) + 1);
}

void Prescription::set_doctor_note(char* ptr_doc_note)
{
    if (m_ptr_doc_note != nullptr)
        delete[] m_ptr_doc_note;

    m_ptr_doc_note = nullptr;

    copy_array(m_ptr_doc_note, ptr_doc_note, get_char_arr_size(ptr_doc_note) + 1);
}

void Prescription::set_prescription(int prescription_id, int appointment_id, int patient_id, int doctor_id, char* ptr_date, char* ptr_medicine, char* ptr_doc_note)
{
    m_prescription_id = prescription_id;
    m_appointment_id = appointment_id;
    m_patient_id = patient_id;
    m_doctor_id = doctor_id;

    set_date(ptr_date);
    set_medicine(ptr_medicine);
    set_doctor_note(ptr_doc_note);
}

Prescription::~Prescription()
{
    delete[] m_ptr_date;
    delete[] m_ptr_medicine;
    delete[] m_ptr_doc_note;

    m_ptr_date = nullptr;
    m_ptr_medicine = nullptr;
    m_ptr_doc_note = nullptr;
}