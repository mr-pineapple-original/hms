#include "person.hpp"
#include "char_array_functions.cpp"

Person::Person()
{
    m_id = 0;
    m_age = 0;
    m_gender = nullptr; // Imagine having nullptr as gender. Crazy right
    m_ptr_name = nullptr; 
    m_ptr_password = nullptr;
}


Person::Person(int id, char* ptr_password, char* ptr_name, const char* gender, int age)
{
    m_id = id;
    m_age = age;
    m_gender = gender;

    int name_size = get_char_arr_size(ptr_name);
    m_ptr_name = nullptr;
    copy_array(m_ptr_name, ptr_name, name_size + 1);

    int password_size = get_char_arr_size(ptr_password);
    m_ptr_password = nullptr;
    copy_array(m_ptr_password, ptr_password, password_size + 1);

}

Person::Person(const Person& obj)
{
    m_id = obj.m_id;
    m_age = obj.m_age;
    m_gender = obj.m_gender;

    int name_size = get_char_arr_size(obj.m_ptr_name);
    m_ptr_name = nullptr;
    copy_array(m_ptr_name, obj.m_ptr_name, name_size + 1);

    int password_size = get_char_arr_size(obj.m_ptr_password);
    m_ptr_password = nullptr;
    copy_array(m_ptr_password, obj.m_ptr_password, password_size + 1);
}

Person& Person::operator=(const Person& obj)
{
    if(this != &obj)
    {
        m_id = obj.m_id;
        m_age = obj.m_age;
        m_gender = obj.m_gender;

        int name_size = get_char_arr_size(obj.m_ptr_name);
        if(m_ptr_name != nullptr)
            delete[] m_ptr_name;
        m_ptr_name = nullptr;
        copy_array(m_ptr_name, obj.m_ptr_name, name_size + 1);

        int password_size = get_char_arr_size(obj.m_ptr_password);
            if(m_ptr_password != nullptr)
                delete[] m_ptr_password;
        m_ptr_password = nullptr;
        copy_array(m_ptr_password, obj.m_ptr_password, password_size + 1);
    }
    return *this;
}

int Person::get_age() const
{
    return m_age;
}

int Person::get_id() const
{
    return m_id;
}

const char* Person::get_gender() const
{
    return m_gender;
}

char* Person::get_name() const
{
    return m_ptr_name;
}

char* Person::get_password() const
{
    return m_ptr_password;
}

Person::~Person()
{
    delete[] m_ptr_name;
    delete[] m_ptr_password;

    m_ptr_name = nullptr;
    m_ptr_password = nullptr;
}