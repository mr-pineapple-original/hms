#include"insufficient_funds_exception.hpp"

InsufficientFundsException::InsufficientFundsException() : HospitalException(" Unfortunately you do not have enough funds to pay for this transaction :( ")
{
    
}