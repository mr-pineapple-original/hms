#include"file_not_found_exception.hpp"
// I can create a static or an extern here but ugh
FileNotFoundException::FileNotFoundException() : HospitalException("File not found :( ")
{
    
}