//
// Created by Bartek on 18.03.2022.
//
#include <iostream>
#include "MinesweeperBoard.h"
#include <cstdlib>
#include <cmath>

using namespace std;
void MinesweeperBoard::clear_board()

{
    Field set_zero;
    set_zero.hasMine = 0;
    set_zero.hasFlag = 0;
    set_zero.isRevealed = 0;
    for(int row = 0; row <= height; row++)
    {
        for(int column = 0; column <= width; column++)
            board[column][row] = set_zero;
    }
}


int MinesweeperBoard::getMineCount() const {
    int licznik=0;
    for (int row = 0; row < width; row++) {
        for (int col = 0; col < height; col++) {
            if (board[row][col].hasMine == true)
            {licznik++;}
        }
    }
    return licznik;

}

int  MinesweeperBoard::liczRevealed() const
{
    int licznik = 0;
    for(int y =0; y < get_height() ; y++)
    {
        for(int x = 0; x < get_width(); x++) {
            if (board[x][y].isRevealed == true)
                licznik++;
        }
    }

    return licznik;
}

MinesweeperBoard::MinesweeperBoard(int xwidth, int xheight, GameMode  mode)
{
    width = xwidth;
    height = xheight;
    status = RUNNING;

    int field_covered = 0;
    clear_board();
    if(mode == DEBUG)
    {

    }
    if(mode == EASY)
    {
        double temp1 = double(height) * double(width) * 0.1;
        temp1 = ceil(temp1);
        field_covered = int(temp1);
    }
    if(mode == NORMAL)
    {

        double temp2 = double(height)  * double(width) * 0.2;
        temp2 = ceil(temp2);
        field_covered = int(temp2);
    }
    if(mode == HARD)
    {
        double temp3 = double(height) * double(width) * 0.3;
        temp3 = ceil(temp3);
        field_covered = temp3;
    }

    for (int IloscBomb = 0; IloscBomb < field_covered; IloscBomb++)
    {
        int RandomHeight = rand() % height;
        int RandomWidth = rand() % width;
        if(board[RandomHeight][RandomWidth].hasMine == true)
        {
            IloscBomb -= 1;
        }
        board[RandomHeight][RandomWidth].hasMine = true;
    }
}


bool MinesweeperBoard::hasFlag(int row, int col) const
{


    if(onBoard(row, col) == false)
    {
        return false;
    }

    if (board[row][col].isRevealed == true)
    {
        return false;
    }
    return board[row][col].hasFlag;

}

int MinesweeperBoard::countMines(int row, int col) const {
    int licznik=0;
    for(int column = col -1; column <= col + 1; column++)
        for(int rzad = row - 1; rzad <= row + 1; rzad++)
        {
            if(onBoard(rzad, column) and board[rzad][column].hasMine)
                licznik++;
        }
    return licznik-int(board[row][col].hasMine);
}

int MinesweeperBoard::get_width() const
{
    return width;
}
int MinesweeperBoard::get_height() const
{
    return height;
}

void MinesweeperBoard::toggleFlag(int row, int col)
{
    if ((board[row][col].isRevealed == true) or !onBoard(row, col) or (getGameState() != RUNNING))
    {
        return;
    }
    if(board[row][col].isRevealed == false)
    {
        if( board[row][col].hasFlag == false)
        board[row][col].hasFlag = true;
        else
            board[row][col].hasFlag = false;
    }


}
GameState MinesweeperBoard::getGameState() const {
    int licznikPol = 0;
    int licznikFlag = 0;
    for(int y = 0; y < get_height(); y++ )
    {
        for(int x = 0; x < get_width(); x++ ) {
            if (board[x][y].hasMine == true and isRevealed(x, y) == true) {
                return FINISHED_LOSS;
            }
            if (board[x][y].hasMine == false and isRevealed(x, y) == true)
                licznikPol++;

            if (board[x][y].hasMine == true and hasFlag(x, y) == true)
                licznikFlag++;
        }
    }
    if((licznikFlag == getMineCount()) and (licznikPol == get_width() * get_height() - getMineCount()))
        return  FINISHED_WIN;
    return RUNNING;
}

void MinesweeperBoard::revealField(int row, int col)
{

   if((isRevealed(row, col) == true) or !onBoard(row,col) or (getGameState() != RUNNING) or (hasFlag(row, col) == true))
   {
       return;
   }

   if( board[row][col].hasMine == true)
   {

       //cout<<licznikRevealed;
       if (liczRevealed() == 0)
       {

           int bombs_ctr = 0;
           for (bombs_ctr = 0; bombs_ctr < 1; bombs_ctr++)
           {
               int RandomHeight = rand() % height;
               int RandomWidth = rand() % width;
               if ((board[RandomHeight][RandomWidth].hasMine == true) or (row == RandomWidth   and col == RandomHeight))
               {
                   bombs_ctr -= 1;
               }
                else
                  board[RandomHeight][RandomWidth].hasMine = true;

           }

           board[row][col].hasMine = false;
       }

   }
  board[row][col].isRevealed = true;

    if (countMines(row, col) != 0) return;
    revealField(row + 1, col + 1);
    revealField(row + 1, col);
    revealField(row + 1, col - 1);
    revealField(row, col + 1);
    revealField(row, col - 1);
    revealField(row - 1, col + 1);
    revealField(row - 1, col);
    revealField(row - 1, col - 1);
}

bool MinesweeperBoard::isRevealed(int row, int col) const
{
    if (board[row][col].isRevealed == true)
        return true;

    return false;
}



char MinesweeperBoard::getFieldInfo(int row, int col) const
{
    if(row >= get_width() and col >= get_height())
    {
        return '#';
    }
    if(isRevealed(row,col) == false and hasFlag(row,col) == true)
    {
        return'F';
    }
    if(isRevealed(row,col) == false and hasFlag(row,col) == false)
    {
        return'_';
    }
    if(isRevealed(row,col) == true and board[row][col].hasMine == true)
    {
        return'x';
    }
    if(isRevealed(row,col) == true and countMines(row,col) == 0)
    {
        return' ';
    }
    if (isRevealed(row, col) and countMines(row, col) != 0) {
        return char(countMines(row, col)) + '0';
    }
    return '#';
}
void MinesweeperBoard::debug_display() const
{
    for (int row = 0; row < height; row++) {
        for (int column = 0; column < width; column++) {
            cout << "[";
            if (board[row][column].hasMine)
                cout << "M";
            else
                cout << ".";
            if (board[row][column].isRevealed)
                cout << "O";
            else
                cout << ".";
            if (board[row][column].hasFlag)
                cout << "f";
            else
                cout << ".";
            cout << "]";
        }
        cout << endl;
    }

    cout << endl;

    for (int row = 0; row < height; row++)
    {
        for (int column = 0; column < width; column++)
        {
            cout << "[" << getFieldInfo(row, column) << "]";
        }
        cout << endl;
    }
}



bool MinesweeperBoard::onBoard(int row, int col) const
{
    if (row >= 0 and row <= get_height() and col >= 0 and col <= get_width())
    { return true; }
    else
        return false;
}




