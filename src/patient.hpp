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
            
        }
    }
}

class Patient
{
    private:
                
};

