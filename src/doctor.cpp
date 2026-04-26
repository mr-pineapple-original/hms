#include "doctor.hpp"
#include "char_array_functions.cpp"

Doctor::Doctor() : Person()
{
    m_ptr_specialization = nullptr;
    m_ptr_contact = nullptr;
    m_fee = 0.0;
}

Doctor::Doctor(int id, char* password, char* name, const char* gender, int age, char* specialization, char* contact, double fee) : Person(id, password, name, gender, age)
{
    m_ptr_specialization = nullptr;
    m_ptr_contact = nullptr;

    int spec_size = get_char_arr_size(specialization);
    copy_array(m_ptr_specialization, specialization, spec_size + 1);

    int contact_size = get_char_arr_size(contact);
    copy_array(m_ptr_contact, contact, contact_size + 1);

    m_fee = fee;
}

Doctor::Doctor(const Doctor& obj) : Person(obj)
{
    m_ptr_specialization = nullptr;
    m_ptr_contact = nullptr;

    int spec_size = get_char_arr_size(obj.m_ptr_specialization);
    copy_array(m_ptr_specialization, obj.m_ptr_specialization, spec_size + 1);

    int contact_size = get_char_arr_size(obj.m_ptr_contact);
    copy_array(m_ptr_contact, obj.m_ptr_contact, contact_size + 1);

    m_fee = obj.m_fee;
}

Doctor& Doctor::operator=(const Doctor& obj)
{
    if (this != &obj)
    {
        // Manually calling the base abstract class (Person) operator 
        Person::operator=(obj);

        if(m_ptr_specialization != nullptr)
        delete[] m_ptr_specialization;

        m_ptr_specialization = nullptr;

        int spec_size = get_char_arr_size(obj.m_ptr_specialization);
        copy_array(m_ptr_specialization, obj.m_ptr_specialization, spec_size + 1);

        if(m_ptr_contact != nullptr)
        delete[] m_ptr_contact;
        
        m_ptr_contact = nullptr;

        int contact_size = get_char_arr_size(obj.m_ptr_contact);
        copy_array(m_ptr_contact, obj.m_ptr_contact, contact_size + 1);

        m_fee = obj.m_fee;
    }
    return *this;
}

Doctor::~Doctor()
{
    delete[] m_ptr_specialization;
    delete[] m_ptr_contact;

    m_ptr_specialization = nullptr;
    m_ptr_contact = nullptr;
}

bool Doctor::operator==(const Doctor& obj) const
{
    if(m_id == obj.m_id)
    {
        return true;
    }

    else
    {
        return false;
    }

}

std::istream& operator>>(std::istream& input, Doctor& obj)
{
    std::cout << "Enter Name: \n";
    safe_get_line(obj.m_ptr_name);

    std::cout << "Enter Password: \n";
    safe_get_line(obj.m_ptr_password);

    std::cout << "Enter Specialization: \n";
    safe_get_line(obj.m_ptr_specialization);

    std::cout << "Enter Contact: \n";
    safe_get_line(obj.m_ptr_contact);

    std::cout << "Enter Age: \n";
    input >> obj.m_age;

    std::cout << "Enter Gender (M/F) either M or F:\n";
    char temp;
    input >> temp;

    if(temp == 'M' || temp == 'm')
    {
        obj.m_gender = male;
    }

    if(temp == 'F' || temp == 'f')
    {
        obj.m_gender = female;
    }

    std::cout << "Enter Fee:\n";
    input >> obj.m_fee;

    return input;
}

std::ostream& operator<<(std::ostream& output, const Doctor& obj)
{
    output << "ID: " << obj.m_id << "\n";
    output << "Name: " << obj.m_ptr_name << "\n";
    output << "Specialization: " << obj.m_ptr_specialization << "\n";
    output << "Contact: " << obj.m_ptr_contact << "\n";
    output << "Fee: PKR " << obj.m_fee << "\n";
    return output;
}

void Doctor::display() 
{
    std::cout << *this; // It will call << overload  I know very weird to have 2 ways to display it right
}

void Doctor::menu()
{
    std::cout << "\n Doctor Menu \n";
    std::cout << "1. View Today's Appointments \n";
    std::cout << "2. Mark Appointment Complete \n";
    std::cout << "3. Mark No-Show \n";
    std::cout << "4. Write Prescription \n";
    std::cout << "5. View Patient History \n";
    std::cout << "6. Logout \n";
}

char* Doctor::get_specialization() const
{
    return m_ptr_specialization;
}

char* Doctor::get_contact() const
{
    return m_ptr_contact;
}

double Doctor::get_fee() const
{
    return m_fee;
}