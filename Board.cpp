#pragma once
#include "Board.h"
#include "Move.h"
#include "Stack.h"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_ahoshalate     "\x1b[202m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_BRIGHTRED "\x1b[91m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"

Board::Board()
/**אתחל את לוח . מספר המקומות ללא לוח הוא 0.**/
{
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            square[i][j] = 0;
    moves_done = 0;
}


void Board::print()const
/**הדפסת לוח**/
{
    cout << endl <<   "    0   1   2"  << endl;
    cout << ANSI_COLOR_BRIGHTRED "   ___________" ANSI_COLOR_RESET << endl;
    for (int i = 0; i < 3; i++)
    {
        cout << endl << i;
        for (int j = 0; j < 3; j++)
        {
            if (square[i][j] == 1)
                cout << ANSI_COLOR_CYAN "   O" ANSI_COLOR_RESET;
            else if (square[i][j] == 2)
                cout << ANSI_COLOR_YELLOW"   X" ANSI_COLOR_RESET;
            else cout << "   -";
            if (j == 2) cout << endl;
        }
    }
    cout << ANSI_COLOR_BRIGHTRED "   ___________" ANSI_COLOR_RESET << endl;
    cout << endl;
}

void Board::play(Move try_it)
/**תתחיל צעד עם הלוח**/
{
    Move r, c;
    square[try_it.getrow()][try_it.getcol()] = moves_done % 2 + 1;
    moves_done++;
}

int Board::the_winner()const
/**מחזירה את המספר (1 או 2) המייצג את המנצח ומחזירה 0 אם המנצח או המפסיד אינם בטוחים.**/
{
    int i;
    for (i = 0; i < 3; i++)
        if (square[i][0] && square[i][0] == square[i][1]
            && square[i][0] == square[i][2])
            return square[i][0];

    for (i = 0; i < 3; i++)
        if (square[0][i] && square[0][i] == square[1][i]
            && square[0][i] == square[2][i])
            return square[0][i];

    if (square[0][0] && square[0][0] == square[1][1]
        && square[0][0] == square[2][2])
        return square[0][0];

    if (square[0][2] && square[0][2] == square[1][1]
        && square[0][2] == square[2][0])
        return square[0][2];
    return 0;
}

bool Board::done()const
/**לשפוט אם המשחק נגמר**/
{
    return (moves_done == 9 || the_winner() > 0);
}

int Board::legal_moves(Stack& moves)const
/**אחסן את כל השלבים האפשריים במחסנית**/
{
    int count = 0;
    while (!moves.empty())
        moves.pop();
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (square[i][j] == 0)
            {
                Move can_play(i, j);
                moves.push(can_play);
                count++;
            }
    return count;
}

bool Board::is_ok(Move try_it)
/**לשפוט האם הצעד הזה אפשרי או חוקי**/
{
    if (try_it.getrow() >= 0 && try_it.getrow() < 3 && try_it.getcol() >= 0 && try_it.getcol() < 3
        && square[try_it.getrow()][try_it.getcol()] == 0)
        return true;
    else return false;
}

int Board::evaluate()const
/**חזור למספר, המשקף את הניצחון או ההפסד וכמה צעדים נעשו.
    לחישוב התוצאה הסופית של כל שלב אפשרי בפונקציה הרקורסיבית הבאה**/
{
    int winner = the_winner();
    if (winner == 1)
        return 10 - moves_done;//אם המנצח הוא 1, ערך ההחזר חיובי. ככל שהמספר גדול יותר, כך טוב יותר עבור שחקן 1.

    else if (winner == 2)
        return moves_done - 10;//המנצח הוא 2, ואז ערך ההחזר שלילי. ככל שהמספר קטן יותר, כך ייטב לשחקן 2.
    else
        return 0;//זה נגמר בתיקו
}

int Board::worst_case()const
/**חזור למקרה הגרוע ביותר להשוואה קלה ברקורסיה**/
{
    if (moves_done % 2)	//For Player 2
        return 10;
    else return -10;	//For Player 1
}

bool Board::better(int value, int old_value)const
/**השווה בין שני הערכים שהוא הטוב ביותר**/
{
    if (moves_done % 2)	//For Player 2
        return value < old_value;
    else				//For Player 1
        return value > old_value;
}