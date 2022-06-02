#pragma once
#include "Move.h"
#include "Stack.h"
class Board {
public:
    Board();
    bool done()const;
    bool is_ok(Move try_it);
    void print()const;
    bool better(int value, int old_value)const;
    void play(Move try_it);
    int worst_case()const;
    int evaluate()const;
    int legal_moves(Stack& moves)const;
   //void show_the_board();
private:
    int square[3][3];
    int moves_done;
    int the_winner()const;
};
