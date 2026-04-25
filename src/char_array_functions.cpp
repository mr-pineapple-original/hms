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

template <typename T>
void copy_array(T* &ptr_arr, const T* ptr_arr_src, int size)
{
    if(ptr_arr != nullptr)
        delete[] ptr_arr;

    ptr_arr = new T[size];

    for(int i = 0; i < size; i++)
    {
        *(ptr_arr + i) = *(ptr_arr_src + i);
        
        if(*(ptr_arr_src + i) == '\0')
        {
            *(ptr_arr + i) = '\0';
            break;
        }    
    }
}

int get_char_arr_size(const char* ptr_arr)
{
    if(!ptr_arr) return 0;
    
    int length = 0;
    for(int i = 0; *(ptr_arr + i) != '\0'; i++)
    {
        length++;
    }
    return length;
}

void add_null_character_in_array(char* &ptr_arr)
{
    if(!ptr_arr) return;
    
    int size = get_char_arr_size(ptr_arr);
    bool flag = false;
    
    for(int i = 0; i < size; i++)
    {
        if(*(ptr_arr + i) == '\0')
        {
            flag = true;
            break;
        }
    }

    if(!flag)
    {
        resize_array(ptr_arr, size, size + 1);
        *(ptr_arr + size) = '\0';
    }
}