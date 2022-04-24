//
// Created by Bartek on 07.04.2022.
//
#include "MinesweeperBoard.h"
#include "MSBoardTextView.h"
#include "MSTextController.h"
using namespace std;
MSTextController::MSTextController(MinesweeperBoard &board, MSBoardTextView &view) :Logic(board), Output(view)
{
}
void MSTextController::play()
{
    Output.view();
    cout << endl;
    while(Logic.getGameState() == RUNNING)
    {
        int row;
        int col;
        int wybor;
        cout << "Wybierz 1 jesli chcesz odkryc pole. Wybierz 2 jesli chcesz postawic flage. Wybierz 3 jesli chcesz wyczyscic pole" << endl;
        cin >> wybor;
        if (wybor == 1)
        {
            cout << "aby odkryc pole podaj numer kolumny w przedziale  od 0 do " << Logic.get_width() - 1 << "oraz podaj numer rzedu w przedziale od 0 do " << Logic.get_height() - 1 << endl;
            cin >> row;
            cin >> col;
            Logic.revealField(row, col);

        }
        if (wybor == 2)
        {
            cout << "aby umiescic flage podaj numer kolumny w przedziale  od 0 do " << Logic.get_width() - 1 << "oraz podaj numer rzedu w przedziale od 0 do " << Logic.get_height() - 1 << endl;
            cin >> row;
            cin >> col;
            Logic.toggleFlag(row, col);
        }
       Output.view();
        cout << endl;
       Logic.debug_display();
    }

   if(Logic.getGameState() == FINISHED_LOSS)
       cout << "Loss :(";
   if(Logic.getGameState() == FINISHED_WIN)
       cout << "Win :)";

}

