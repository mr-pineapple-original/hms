#include"hospital_exception.hpp"

HospitalException::HospitalException(const char* ptr_message)
{
    // Used 200 because our project says we have to have a static character array to store 200 characters
    for(int i = 0; *(ptr_message + i) != '\0' && i < 200; i++)
    {
        m_message[i] = *(ptr_message + i);
        
        if(*(ptr_message + i + 1) == '\0')
        {
            m_message[i + 1] = '\0';
            break;
        }
    }
}

// what() is a special function to deal with exception handling that all the derived classes will use or override
const char* HospitalException::what() const
{
    return m_message;
}

HospitalException::~HospitalException()
{
    // Literally empty cause we have nothing on the heap :/
}
