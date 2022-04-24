//
// Created by Bartek on 18.03.2022.
//
#include <iostream>
#include "MinesweeperBoard.h"
#include <cstdlib>
#include <cmath>

using namespace std;
void MinesweeperBoard::clear_board()
//czyscimy
{
    Field czyszczenie;
    czyszczenie.hasMine = 0;
    czyszczenie.hasFlag = 0;
    czyszczenie.isRevealed = 0;
    for(int wiersz = 0; wiersz <= height; wiersz++)
    {
        for(int kolumna = 0; kolumna <= width; kolumna++)
            board[kolumna][wiersz] = czyszczenie;
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

    // ustawic szerokosc


    int PolePokryte = 0;
    clear_board();
    if(mode == DEBUG)
    {

        Field OpcjaA;   //zawiera minę, nie ma flagi i nie zostało odkryte
        Field OpcjaB;   //jest odkryte, nie ma miny i nie ma flagi
        Field OpcjaC;   //zawiera minę i flagę, nie jest odkryte

        OpcjaA.hasMine = true;
        OpcjaA.hasFlag = false;
        OpcjaA.isRevealed = false;

        OpcjaB.hasMine = false;
        OpcjaB.hasFlag = false;
        OpcjaB.isRevealed = false;

        OpcjaC.hasMine = true;
        OpcjaC.hasFlag = true;
        OpcjaC.isRevealed = false;
        board[0][0] = OpcjaA;
        board[1][1] = OpcjaB;
        board[0][2] = OpcjaC;

    }
    if(mode == EASY)
    {
        double temp1 = double(height) * double(width) * 0.1;
        temp1 = ceil(temp1);
        PolePokryte = int(temp1);
    }
    if(mode == NORMAL)
    {

        double temp2 = double(height)  * double(width) * 0.2;
        temp2 = ceil(temp2);
        PolePokryte = int(temp2);
    }
    if(mode == HARD)
    {
        double temp3 = double(height) * double(width) * 0.3;
        temp3 = ceil(temp3);
        PolePokryte = temp3;
    }
    //cout << PolePokryte << endl;
    for (int IloscBomb = 0; IloscBomb < PolePokryte; IloscBomb++)
    {
        int RandomHeight = rand() % height;
        int RandomWidth = rand() % width;
        if(board[RandomHeight][RandomWidth].hasMine == true)
        {
            IloscBomb -= 1;
        }
        board[RandomHeight][RandomWidth].hasMine = true;
    }
        //debug_display();
       //cout<<getMineCount()<<endl;
        }


bool MinesweeperBoard::hasFlag(int row, int col) const
{
    // return true if the field at (row,col) position was marked with flag
    // return false if any of the following is true:
    // - row or col is outside board

    if(onBoard(row, col) == false)
    {
        return false;
    }

    if (board[row][col].isRevealed == true)
    {
        return false;
    }
    return board[row][col].hasFlag;

//    if (board[row][col].hasFlag == true)
//        {
//            return true;
//    }
//    if (board[row][col].hasFlag == false)
//    {
//        return false;
//    }
//    if (board[row][col].isRevealed == true)
//    {
//        return false;
//    }
// napisac jesli jest poza plansza!!!!!!!!!!!!!!!!!!!!!!!!!!
}

int MinesweeperBoard::countMines(int row, int col) const {
    int licznik=0;
    for(int kolumna = col -1; kolumna <= col + 1; kolumna++)
        for(int rzad = row - 1; rzad <= row + 1; rzad++)
        {
            if(onBoard(rzad, kolumna) and board[rzad][kolumna].hasMine)
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
    // try to reveal the field at (row,col)
    // Do nothing if any of the following is true
    // - field was already revealed
    // - either row or col is outside board
    // - game is already finished
    // - there is a flag on the field
    //
    // If the field was not revealed and there is no mine on it - reveal it
    // If the field was not revealed and there is a mine on it:
    // - if its the first player action - move mine to another location, reveal field (not in DEBUG mode!)
    // - reveal it and finish game
   if((isRevealed(row, col) == true) or !onBoard(row,col) or (getGameState() != RUNNING) or (hasFlag(row, col) == true))
   {
       return;
   }

   if( board[row][col].hasMine == true)
   {

       //cout<<licznikRevealed;
       if (liczRevealed() == 0)
       {

           int IloscBomb = 0;
           for (IloscBomb = 0; IloscBomb < 1; IloscBomb++)
           {
               int RandomHeight = rand() % height;
               int RandomWidth = rand() % width;
               if ((board[RandomHeight][RandomWidth].hasMine == true) or (row == RandomWidth   and col == RandomHeight))
               {
                   IloscBomb -= 1;
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
     //if the field is revealed and has 0 mines around        - return ' ' (space) character
     //if the field is revealed and has some mines around     - return '1' ... '8' (number of mines as a digit)
}
void MinesweeperBoard::debug_display() const
{
    for (int wiersz = 0; wiersz < height; wiersz++) {
        for (int kolumna = 0; kolumna < width; kolumna++) {
            cout << "[";
            if (board[wiersz][kolumna].hasMine)
                cout << "M";
            else
                cout << ".";
            if (board[wiersz][kolumna].isRevealed)
                cout << "O";
            else
                cout << ".";
            if (board[wiersz][kolumna].hasFlag)
                cout << "f";
            else
                cout << ".";
            cout << "]";
        }
        cout << endl;
    }

    cout << endl;

    for (int wiersz = 0; wiersz < height; wiersz++)
    {
        for (int kolumna = 0; kolumna < width; kolumna++)
        {
            cout << "[" << getFieldInfo(wiersz, kolumna) << "]";
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




