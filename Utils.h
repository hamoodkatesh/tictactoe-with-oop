#pragma once
#pragma warning(disable : 4996)
#include<iostream>
#include<stdio.h>
#include"windows.h"
#include "Move.h"
#include "Board.h"
#include "Stack.h"
#include<cstdlib>
#include<conio.h>
#include<string>
#include<iomanip>

#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_ahoshalate     "\x1b[202m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_BRIGHTRED "\x1b[91m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"
//Regular underline text
#define UBLK "\e[4;30m"
#define URED "\e[4;31m"
#define UGRN "\e[4;32m"
#define UYEL "\e[4;33m"
#define UBLU "\e[4;34m"
#define UMAG "\e[4;35m"
#define UCYN "\e[4;36m"
#define UWHT "\e[4;37m"
#define Stack_entry Move
#define maxstack 100
#define success true
#define underflow false
#define overflow false

using namespace std;

const int options_row = 4;
const int options_col = 16;


class Panel {
private:
    char options[options_row][options_col] =
    {
      {' ',' ',' ',' ','N','e','w',' ','G','a','m','e',' ',' ',' ',' '},
      {' ',' ','I','n','s','t','r','u','c','t','i','o','n','s',' ',' '},
      {' ',' ',' ',' ','C','r','e','d','i','t','s',' ',' ',' ',' ',' '},
      {' ',' ',' ',' ',' ',' ','E','x','i','t',' ',' ',' ',' ',' ',' '},
    };
    int arrow_row = 0, arrow_col = 0;
    char options_move;
    int computer_x = 0;
    char upordown;
    bool valid_computer_position;
    int computer_row, computer_col;
    string name;

public:

    void mygametitle()
    {
        cout << ANSI_COLOR_RED R"(       
|\  \  /  /|\   __  \   |\  \  /  /|\   __  \                          |\  \  /  /|\   __  \   |\  \  /  /|\   __  \    
\ \  \/  / | \  \|\  \  \ \  \/  / | \  \|\  \                         \ \  \/  / | \  \|\  \  \ \  \/  / | \  \|\  \   
 \ \    / / \ \  \\\  \  \ \    / / \ \  \\\  \                         \ \    / / \ \  \\\  \  \ \    / / \ \  \\\  \  
  /     \/   \ \  \\\  \  /     \/   \ \  \\\  \                         /     \/   \ \  \\\  \  /     \/   \ \  \\\  \ 
 /  /\   \    \ \_______\/  /\   \    \ \_______\                       /  /\   \    \ \_______\/  /\   \    \ \_______\
/__/ /\ __\    \|_______/__/ /\ __\    \|_______|                      /__/ /\ __\    \|_______/__/ /\ __\    \|_______|
|__|/ \|__|             |__|/ \|__|                                    |__|/ \|__|             |__|/ \|__|              
                                                                                                                        
                                                                                                                  
                                                                                                         
                                                 
                                                   
)" << endl<<endl;
    }

    int look_ahead(const Board& game, int depth, Move& recommended)
    {
        if (game.done() || depth == 0)
            return game.evaluate();
        else
        {
            Stack moves;
            game.legal_moves(moves);
            int value;
            int best_value = game.worst_case();
            while (!moves.empty())
            {
                Move try_it, reply;
                moves.top(try_it);
                Board new_game = game;
                new_game.play(try_it);
                value = look_ahead(new_game, depth - 1, reply);
                if (game.better(value, best_value))
                {
                    best_value = value;
                    recommended = try_it;
                }
                moves.pop();
            }
            return best_value;
        }
    }

    void instructions()
    {
        cout << ANSI_COLOR_BRIGHTRED "Welcome to the Hamood game!" ANSI_COLOR_RESET << endl
            << "You will begin to play Vs this computer." << endl
            << ANSI_COLOR_GREEN "The rules of the game are simple, just input the coordinates of the pieces." ANSI_COLOR_RESET << endl
            << "Reminder: O For you, X Represent your opponent." << endl << endl;
    }

    void print_the_result(int result)
    {
        if (result > 0)
            cout << ANSI_COLOR_CYAN "\n Congratulations on your victory!\n" ANSI_COLOR_RESET << endl;
        else if (result < 0)
            cout << ANSI_COLOR_RED "\noops!You lost!\n" ANSI_COLOR_RESET << endl;
        else cout << "\n Draw!\n" << endl;
    }

    int play_game(int intel)
    {
        Board game;
        Move player1_choice;
        Move player2_choice;

        cout << ANSI_COLOR_MAGENTA "Please enter the computer's IQ:" ANSI_COLOR_RESET << endl;
        while (intel < 1 || intel>9)
        {
            cout << "IQ should be greater than or equal to 1, less than or equal to 9." << endl;
            cin >> intel;
        }
        system("cls");
        game.print();
        while (!game.done())
        {
            int col1, row1;
            cout << "Please choose place Like 0 0,0 1,1 2 -->press number + space + number:(player 1):\n";
            cin >> row1 >> col1;
            player1_choice.setrow(row1);
            player1_choice.setcol(col1);
            while (!game.is_ok(player1_choice))
            {

                cout << "You can't play in this place or its taken." << endl;
                cin >> row1 >> col1;
                player1_choice.setrow(row1);
                player1_choice.setcol(col1);
            }
            game.play(player1_choice);
            if (game.done())
            {
                system("cls");
                game.print();
                break;
            }

            look_ahead(game, intel, player2_choice);  //Computer playing 
            game.play(player2_choice);

            system("cls");
            game.print();
        }
        print_the_result(game.evaluate());
        return game.evaluate();
    }

    void enter_player_name() {
        system("CLS");
        system("Color 02");

        for (int i = 0; i < 19; i++) {
            cout << endl;
        }
        cout << setw(72) << "Enter Your Name Please: ";
        getline(cin, name);
        cout << endl << endl << endl;
    }

    int Controlpanel()
    {
        int win0 = 0, win1 = 0, win2 = 0;
        int winner;
        char command;
        int intel = 0;

        enter_player_name();
        instructions();
        cout << "Do you start the game? Input Arbitrary None N Characters to start the game." << endl;
        cin >> command;
        if (command != 'N' && command != 'n')
        {
            cout << ANSI_COLOR_MAGENTA "Please enter the computer's IQ:" ANSI_COLOR_RESET << endl;
            while (intel < 1 || intel>9)
            {
                cout << "IQ should be greater than or equal to 1, less than or equal to 9." << endl;
                cin >> intel;
            }
            system("cls");
        }

        while (command != 'N' && command != 'n')
        {
            take_computer_input();
            winner = play_game(intel);
            if (winner == 0) win0++;
            else if (winner > 0) win1++;
            else win2++;
            cout << "Do you want to continue playing? Input Arbitrary None N Characters to continue." << endl;
            cin >> command;
            system("cls");
        }
        if ((win0 + win1 + win2) != 0)
            cout << "With IQ" << " " ANSI_COLOR_GREEN << intel << ANSI_COLOR_RESET" " << "In computer games:" << endl
            << ANSI_COLOR_RED " "<< name << " "  << win1 << " " ANSI_COLOR_RESET << " score" << endl
            << "The computer won. " << " " ANSI_COLOR_BLUE << win2 << " " ANSI_COLOR_RESET << " score" << endl
            << "Draw " << win0 << " score" << endl;
        cout << "press enter to continue..." << endl;
        getchar();
        return 0;
    }

    void print_options() {
        mygametitle();
        for (int i = 0; i < options_row; i++) {
            cout << setw(56);
            for (int j = 0; j < options_col; j++) {
                if (i == arrow_row && j == arrow_col) {
                    cout << (char)175;
                }
                cout << options[i][j];
            }cout << endl;
        }
    }

    void player_chooses_options() {
        while (1) {
            if (kbhit()) {
                options_move = getch();
                if (arrow_row == 0 && arrow_col == 0 && options_move == 13) {
                    system("CLS");
                    Controlpanel();
                }
                else if (arrow_row == 1 && arrow_col == 0 && options_move == 13) {
                    system("CLS");
                    instructions();
                    if (options_move == -32) {
                        system("CLS");
                        instructions();
                    }
                }
                else if (arrow_row == 2 && arrow_col == 0 && options_move == 13) {
                    system("CLS");
                    credits();
                }
                else if (arrow_row == 3 && arrow_col == 0 && options_move == 13) {
                    system("CLS");
                    system("Color 80");
                    for (int i = 0; i < 18; i++) {
                        cout << endl;
                    }cout << setw(58);
                    for (int i = 1; i <= 6; i++) {
                        cout << (char)i << " ";
                    }
                    for (int i = 0; i < 18; i++) {
                        cout << endl;
                    }
                    Sleep(5000);
                    exit(0);
                }
                else if (options_move == 27) {
                    system("CLS");
                    instructions();
                    print_options();
                }
                else if (options_move == -32) {
                    upordown = getch();
                    switch (upordown) {
                    case 72:
                        if (arrow_row > 0) {
                            arrow_row--;
                        }
                        break;
                    case 80:
                        if (arrow_row < options_row - 1) {
                            arrow_row++;
                        }
                        break;
                    }
                    system("CLS");
                    instructions();
                    print_options();
                }
            }
        }
    }

    void take_computer_input() {

        do {
            system("CLS");
            system("Color 8A");
            for (int i = 0; i < 19; i++) {
                cout << endl;
            }
            cout << setw(90) << "Waiting For Computer To Take look on the Board.......";
            valid_computer_position = true;
            srand(time(0));
            Sleep(5000);
            computer_row = rand() % 11;
            computer_col = rand() % 11;
            
            if (valid_computer_position == true) {
                computer_x++;
            }
        } while (computer_x < 4 || !valid_computer_position);

        system("CLS");
        for (int i = 0; i < 19; i++) {
            cout << endl;
        }
        cout << setw(90) << "The Computer is ready. Now It's Your Turn.";
        Sleep(3000);
        system("CLS");
    }

    void credits() {
        system("Color C");
        system("CLS");
        cout << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl;
        cout << setw(84) << "its 09/06/2022!!!" << endl;
        Sleep(4000);
        system("CLS");
        cout << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl;
        cout << setw(76) << "HAMOOD PROJECT IN C++" << endl;
        Sleep(4000);
        system("CLS");
        cout << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl;
        cout << setw(85) << "Working with visual studio 2019" << endl;
        Sleep(4000);
        system("CLS");
        cout << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl;
        cout << setw(68) << "XOXO GAME" << endl;
        Sleep(4000);
        system("CLS");
        cout << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl;
        cout << setw(69) << "GAME DIRECTOR:" << endl;
        cout << setw(71) << "------------------" << endl;
        cout << setw(69) << "Hamood Katesh" << endl;
        Sleep(4000);
        system("CLS");
        cout << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl;
        cout << setw(71) << "EXECUTIVE PRODUCERS:" << endl;
        cout << setw(75) << "----------------------------" << endl;
        cout << setw(72) << "Myself" << endl;
        cout << setw(67) << "And I" << endl << endl;
        Sleep(4000);
        system("CLS");
        cout << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl;
        cout << setw(71) << "LEAD PROGRAMMER:" << endl;
        cout << setw(76) << "--------------------------" << endl;
        cout << setw(69) << "Eilan" << endl;
        Sleep(4000);
        system("CLS");
        cout << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl;
        cout << setw(69) << "ART DIRECTOR:" << endl;
        cout << setw(76) << "----------------------------" << endl;
        cout << setw(69) << "Tal" << endl;
        Sleep(4000);
        system("CLS");
        cout << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl;
        cout << setw(70) << "LEAD DESIGNER:" << endl;
        cout << setw(78) << "------------------------------" << endl;
        cout << setw(69) << "Nasser" << endl;
        Sleep(4000);
        system("CLS");
        cout << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl;
        cout << setw(69) << "LEAD EDITOR:" << endl;
        cout << setw(75) << "------------------------" << endl;
        cout << setw(69) << "Hamood Katesh" << endl;
        Sleep(4000);
        system("CLS");
        cout << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl;
        cout << setw(70) << "UI DEVELOPMENT:" << endl;
        cout << setw(75) << "-------------------------" << endl;
        cout << setw(69) << "Hamood's" << endl;
        Sleep(4000);
        system("CLS");
        cout << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl;
        cout << setw(70) << "AI DEVELOPMENT:" << endl;
        cout << setw(77) << "-----------------------------" << endl;
        cout << setw(69) << "Hamood Katesh" << endl;
        Sleep(4000);
        system("CLS");
        cout << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl;
        cout << setw(71) << "SPECIAL THANKS TO:" << endl;
        cout << setw(75) << "--------------------------" << endl;
        cout << setw(67) << "Eilan Teacher" << endl;
        cout << setw(72) << "Tal Helper" << endl;
        cout << setw(72) << "Naser Helper" << endl;
        Sleep(4000);
        system("CLS");
        cout << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl;
        cout << setw(87) << "All rights its XoXo-game 2022 new version!" << endl;
        Sleep(4000);
        system("CLS");
        print_options();
        player_chooses_options();
    }
};
