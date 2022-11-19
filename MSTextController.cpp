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
        int choice;
        cout << "Select 1 if you want to reveal a field. 2 if you want to plant a flag.3 if you want to clear the field" << endl;
        cin >> choice;
        if (choice == 1)
        {
            cout << " If you want to reveal field, pick the number of a column between 0 and " << Logic.get_width() - 1 << "and the number of a row between 0 and " << Logic.get_height() - 1 << endl;
            cin >> row;
            cin >> col;
            Logic.revealField(row, col);

        }
        if (choice == 2)
        {
            cout << "If you want to toggle the flag pick the number of the column between 0 and " << Logic.get_width() - 1 << "and the number of a row between 0 and " << Logic.get_height() - 1 << endl;
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

