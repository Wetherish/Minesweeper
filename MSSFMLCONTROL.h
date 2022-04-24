//
// Created by Bartek on 24.04.2022.
//

#ifndef UNTITLED_MSSFMLCONTROL_H
#define UNTITLED_MSSFMLCONTROL_H
#include "SFML/Graphics.hpp"
#include "MinesweeperBoard.h"
#include "MSSFMLView.h"

using namespace std;
class MSSFMLCONTROL {
    MinesweeperBoard & board;
    MSSFMLView & view;
    float scalowanie();
public:
    explicit MSSFMLCONTROL(MinesweeperBoard & board, MSSFMLView & view);
    void gameplay (sf::Event &event, sf::RenderWindow &win);


};


#endif //UNTITLED_MSSFMLCONTROL_H
