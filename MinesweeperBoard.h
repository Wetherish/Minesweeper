//
// Created by Bartek on 18.03.2022.
//

#ifndef UNTITLED_MINESWEEPERBOARD_H
#define UNTITLED_MINESWEEPERBOARD_H
#include <cstdlib>
#include <cmath>
#include <iostream>
#include <vector>
#include <string>
#include <ctime>

enum GameState { RUNNING, FINISHED_WIN, FINISHED_LOSS };
enum GameMode  { DEBUG, EASY, NORMAL, HARD };


struct Field
{
    bool hasMine;
    bool hasFlag;
    bool isRevealed;
};

class MinesweeperBoard

{

        Field board[100][100];
        int width;
        int height;
        GameState status;

        bool onBoard(int row,int col) const;


    public:
        MinesweeperBoard(int xwidth, int xheight, GameMode mode );
        void clear_board();
        int get_width() const;                                   // dziala
        int get_height() const;                                  // dziala
        int getMineCount() const;                                // dziala

        void debug_display() const;                             // dziala
        bool hasFlag(int row, int col) const;                   // dziala
        bool isRevealed(int row, int col) const;                // dziala

        int countMines(int row, int col) const;                 // dziala
        void revealField(int row, int col);                     // dziala
        void toggleFlag(int row, int col);                      // dziala
        int liczRevealed() const;


        GameState getGameState() const;                         // dziala
        char getFieldInfo(int row, int col) const;              // dziala

};





#endif //UNTITLED_MINESWEEPERBOARD_H
