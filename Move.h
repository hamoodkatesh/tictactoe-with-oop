#pragma once
#include<iostream>
#include<stdio.h>
#include"windows.h"

#define Stack_entry Move
#define maxstack 100
#define success true
#define underflow false
#define overflow false

using namespace std;

class Move {
public:
    Move();
    Move(int r, int c);
    void setrow(int row)
    {
        this->row = row;
    }
    int getrow()
    {
        return row;
    }

    void setcol(int col)
    {
        this->col = col;
    }
    int getcol()
    {
        return col;
    }
private:
    int row;
    int col;
    
};
