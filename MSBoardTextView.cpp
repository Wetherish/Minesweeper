////
//// Created by Bartek on 31.03.2022.
////
//
#include "MSBoardTextView.h"


using namespace std;
MSBoardTextView::MSBoardTextView(MinesweeperBoard &boardView) :Logic(boardView)
{
}
void MSBoardTextView::view()
{
    int height = Logic.get_height();
    int width = Logic.get_width();
    for (int wiersz = 0; wiersz < height; wiersz++)
    {
        for (int kolumna = 0; kolumna < width; kolumna++)
        {
            cout << "[" << Logic.getFieldInfo(wiersz, kolumna) << "]";
        }
        cout << endl;
    }
}




