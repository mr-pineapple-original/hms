#include "patient.hpp"
#include "char_array_functions.cpp"

Patient::Patient() : Person()
{
    m_ptr_contact = nullptr;
    m_balance = 0.0;
}

Patient::Patient(int id, char* ptr_password, char* ptr_name, const char* gender, int age, char* ptr_contact, double balance) : Person(id, ptr_password, ptr_name, gender, age)
{
    m_ptr_contact = nullptr;

    int contact_size = get_char_arr_size(ptr_contact);
    copy_array(m_ptr_contact, ptr_contact, contact_size + 1);

    m_balance = balance;
}

Patient::Patient(const Patient& obj) : Person(obj)
{
    m_ptr_contact = nullptr;

    int contact_size = get_char_arr_size(obj.m_ptr_contact);
    copy_array(m_ptr_contact, obj.m_ptr_contact, contact_size + 1);

    m_balance = obj.m_balance;
}

Patient& Patient::operator=(const Patient& obj)
{
    if (this != &obj)
    {
        // Call base class assignment
        Person::operator=(obj);

        if(m_ptr_contact != nullptr)
        delete[] m_ptr_contact;
        m_ptr_contact = nullptr;

        int contact_size = get_char_arr_size(obj.m_ptr_contact);
        copy_array(m_ptr_contact, obj.m_ptr_contact, contact_size + 1);

        m_balance = obj.m_balance;
    }
    return *this;
}

Patient::~Patient()
{
    delete[] m_ptr_contact;
    m_ptr_contact = nullptr;
}

Patient& Patient::operator+=(double amount)
{
    m_balance += amount;
    return *this;
}
// -------------------------
Patient& Patient::operator-=(double amount)
{
    m_balance -= amount;
    return *this;
}

bool Patient::operator==(const Patient& obj) const
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

std::ostream& operator<<(std::ostream& output, const Patient& obj)
{
    output << obj.m_id << ",";
    output << obj.m_ptr_name << ",";
    output << obj.m_age << ",";
    output << obj.m_gender << ",";
    output << obj.m_ptr_contact << ",";
    output << obj.m_ptr_password << ",";
    output << obj.m_balance;

    return output;
}

std::istream& operator>>(std::istream& input, Patient& obj)
{
    std::cout << "Enter Name:\n";
    safe_get_line(obj.m_ptr_name);

    std::cout << "Enter Password:\n";
    safe_get_line(obj.m_ptr_password);

    std::cout << "Enter Contact:\n";
    safe_get_line(obj.m_ptr_contact);

    std::cout << "Enter Age:\n";
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

    std::cout << "Enter Balance:\n";
    input >> obj.m_balance;

    return input;
}

void Patient::display()
{
    std::cout << *this; // It will call << overload  I know very weird to have 2 ways to display it right
}

void Patient::menu()
{
    std::cout << "\nPatient Menu\n";
    std::cout << "1. Book Appointment\n";
    std::cout << "2. Cancel Appointment\n";
    std::cout << "3. View Appointments\n";
    std::cout << "4. View Medical Records\n";
    std::cout << "5. View Bills\n";
    std::cout << "6. Pay Bill\n";
    std::cout << "7. Top Up Balance\n";
    std::cout << "8. Logout\n";
}


char* Patient::get_contact() const
{
    return m_ptr_contact;
}

double Patient::get_balance() const
{
    return m_balance;
}