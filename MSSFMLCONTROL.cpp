//
// Created by Bartek on 24.04.2022.
//

#include "MSSFMLCONTROL.h"

MSSFMLCONTROL::MSSFMLCONTROL(MinesweeperBoard & b, MSSFMLView & v) : board(b), view(v)
{

}

void MSSFMLCONTROL::gameplay(sf::Event &event, sf::RenderWindow &win)
{
    if (event.type == sf::Event::MouseButtonPressed){

        int col = ((event.mouseButton.x )/view.scale(win));
        int row = ((event.mouseButton.y)/view.scale(win));

        if(event.mouseButton.button == sf::Mouse::Left)
        {
            board.revealField(row, col);
            return;
        }
        if(event.mouseButton.button == sf::Mouse::Right)
        {
            if(board.getFieldInfo(row, col) == 'F')
            {
                board.toggleFlag(row, col);
            }
            else
            {
                board.toggleFlag(row, col);
            }
        }

    }
}







