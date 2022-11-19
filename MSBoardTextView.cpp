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
    for (int row = 0; row < height; row++)
    {
        for (int col = 0; col < width; col++)
        {
            cout << "[" << Logic.getFieldInfo(row, col) << "]";
        }
        cout << endl;
    }
}




