#include"storage.hpp"

template <typename Entity>
Storage<Entity>::Storage()
{
    count = 0;
}

template <typename Entity>
void Storage<Entity>::add(const Entity& obj)
{
    if (count < 100)
    {
        data[count] = obj;
        count++;
    }
    else
    {
        std::cout << "\n Storage full";
    }
}

template <typename Entity>
Entity* Storage<Entity>::find(int id)
{
    for (int i = 0; i < count; i++)
    {
        if (data[i].get_id() == id)
        {
            return &data[i];
        }
    }
    return nullptr;
}

template <typename Entity>
bool Storage<Entity>::remove(int id)
{
    for (int i = 0; i < count; i++)
    {
        if (data[i].get_id() == id)
        {
            for (int j = i; j < count - 1; j++)
            {
                data[j] = data[j + 1];
            }
            count--;
            return true;
        }
    }
    return false;
}

template <typename Entity>
int Storage<Entity>::size() const
{
    return count;
}