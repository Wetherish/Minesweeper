//
// Created by Bartek on 31.03.2022.
//

#ifndef UNTITLED_MSBOARDTEXTVIEW_H
#define UNTITLED_MSBOARDTEXTVIEW_H
#include "MinesweeperBoard.h"

class MSBoardTextView {
    MinesweeperBoard &Logic;
    public:
        explicit MSBoardTextView(MinesweeperBoard &board);
        void view();
};

#endif //UNTITLED_MSBOARDTEXTVIEW_H
