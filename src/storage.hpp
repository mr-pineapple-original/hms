#include<iostream>
#pragma once

template <typename Entity>
class Storage
{
private:
    Entity data[100];
    int count;
    
public:
    Storage();

    void add(const Entity& obj);
    Entity* find(int id);
    bool remove(int id);
    int size() const;
    Entity* get_data(); // To send a modifyable pointer
    const Entity* get_data() const; // To send a non modifyable pointer
};
