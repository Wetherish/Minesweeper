//
// Created by Bartek on 07.04.2022.
//

#ifndef UNTITLED_MSTEXTCONTROLLER_H
#define UNTITLED_MSTEXTCONTROLLER_H
#include "MinesweeperBoard.h"
#include "MSBoardTextView.h"



class MSTextController {
    MinesweeperBoard &Logic;
    MSBoardTextView &Output;
public:
    MSTextController(MinesweeperBoard &board, MSBoardTextView &view);
    void play();

};


#endif //UNTITLED_MSTEXTCONTROLLER_H
