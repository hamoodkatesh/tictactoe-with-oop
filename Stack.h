#pragma once
#include<iostream>
#include<stdio.h>
#include"windows.h"
#include "Move.h"

using namespace std;

class Stack {
public:
    Stack();
    bool empty()const;
    bool pop();
    bool top(Stack_entry& item);
    bool push(const Stack_entry& item);
private:
    int count;
    Stack_entry entry[maxstack];
};
