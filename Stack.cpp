#pragma once
#include "Stack.h"
Stack::Stack()
{
    count = 0;
}
bool Stack::push(const Stack_entry& item) //מוסיף אלמנט בראש החסנית
{
    bool outcome = success;
    if (count >= maxstack)
        return overflow;
    else
        entry[count++] = item;
    return outcome;
}
bool Stack::pop() //מוחק את הרכיב העליון ביותר של החסנית 
{
    bool outcome = success;
    if (count == 0)
        outcome = underflow;
    else --count;
    return outcome;
}
bool Stack::top(Stack_entry& item) //מחזירה הפניה לרכיב העליון ביותר של החסנית 
{
    bool outcome = success;
    if (count == 0)
        return underflow;
    else
        item = entry[count - 1];
    return outcome;
}
bool Stack::empty()const //מחזירה אם החסנית ריקה
{
    bool outcome = true;
    if (count > 0)
        outcome = false;
    return outcome;
}