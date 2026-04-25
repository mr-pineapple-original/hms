#include"admin.hpp"
#include<iostream>

Admin::Admin() : Person()
{
    
}

Admin::Admin(int id, char* ptr_password)  : Person(id, ptr_password, m_ptr_name, male, 18)
{

}

Admin::Admin(const Admin& obj)
{

}

Admin& Admin::operator=(const Admin& obj)
{
    if(this != &obj)
    {
        // Manually calling the base abstract class (Person) operator 
        Person::operator=(obj);
    }
    return *this;
}

void Admin::display() 
{
    std::cout << "Admin ID: " << m_id << "\n";
    std::cout << "Name: " << m_ptr_name << "\n";
}

void Admin::menu() 
{

    int choice;

    do
    {
        std::cout << "\n Admin Panel — MediCore \n";
        std::cout << "1. Add Doctor \n";
        std::cout << "2. Remove Doctor \n";
        std::cout << "3. View All Patients \n";
        std::cout << "4. View All Doctors \n";
        std::cout << "5. View All Appointments \n";
        std::cout << "6. View Unpaid Bills \n";
        std::cout << "7. Discharge Patient \n";
        std::cout << "8. View Security Log \n";
        std::cout << "9. Generate Daily Report \n";
        std::cout << "10. Logout \n";

        std::cin >> choice;

        // Still needs more work mate

    } while (choice != 10);
}

bool Admin::authenticate(int id, char* ptr_password) const
{
    if(m_id != id)
    {
        return false;
    }

    int size = get_char_arr_size(ptr_password);
    int m_size = get_char_arr_size(m_ptr_password);
    
    if(size != m_size)
    {
        return false;
    }

    for(int i = 0; i < size; i++)
    {
        if(*(m_ptr_password + i) != *(ptr_password + i))
        {
            return false;
        }
    }

    return true;
}

Admin::~Admin()
{

}