// Since everyone in FAST hates us we are not allowed to use strings
// This sucks
// What is wrong with them

#include<iostream>
#pragma once
static const long CLEAR_BUFFER = 10000000;
static const int DEFAULT_SIZE_CHAR_ARRAY = 100;
template <typename T>
void resize_array(T* &ptr_arr, int size, int new_size)
{
    T* ptr_temp = new T[new_size];

    if(new_size <= size)
    {
        for(int i = 0; i < new_size; i++)
        {
            *(ptr_temp + i) = *(ptr_arr + i);
        }
    }
    else
    {
        for(int i = 0; i < size; i++)
        {
            *(ptr_temp + i) = *(ptr_arr + i);
        }
    }
    delete[] ptr_arr;
    ptr_arr = ptr_temp;
    ptr_temp = nullptr;
}

void safe_get_line(char* &ptr_arr)
{
    int size = DEFAULT_SIZE_CHAR_ARRAY;
    if(ptr_arr != nullptr)
    delete[] ptr_arr;

    ptr_arr = new char[size];

    std::cin.clear();
    std::cin.getline(ptr_arr, size);

    while(std::cin.fail())
    {
        std::cin.clear();
        std::cin.ignore(CLEAR_BUFFER, '\n');

        int new_size = size * 2;
        resize_array(ptr_arr, size, new_size);
        size = new_size;

        std::cout << "\n Please let us use strings :(";
        std::cout << "\n Sorry the input is too long, please enter again:\n";

        std::cin.getline(ptr_arr, size);
    }

    // Check if the character array is empty or not
    if(*(ptr_arr + 0) == '\0')
    {
        std::cout << "\n Name cannot be empty, try again \n";    
        safe_get_line(ptr_arr);
    }

}

// void Beyblade::set_name()
// {
//     int default_size = 100;
//     int size = default_size;
//     cout << "\n Enter the name of the healthbot:\n";

//     if(m_ptr_name != nullptr)
//     {
//         delete[] m_ptr_name;
//     }

//     m_ptr_name = new char[default_size];
//     while(true)
//     {
//     cin.clear();    
//     cin.getline(m_ptr_name, default_size);
//     if(*m_ptr_name == '\0')
//     {
//         cout << "\n Name cannot be empty, please enter again:\n";
//         continue;
//     }

//     else
//     {
//         break;
//     }

//     }

//     while(true)
//     {

//     if(cin.fail())
// 	{
//         cin.clear();
//         cin.ignore(CLEAR_BUFFER,'\n');
//         resize_array(m_ptr_name, size*2, size);
//         size = size*2;
//         cout << "\n Please let us use strings :(";
//         cout << "\n Sorry the name is too long, please enter again:\n";
//         cin.getline(m_ptr_name,size);
//         continue;
// 	}

//     else
//     {
//         break;
//     }
//     }

// }