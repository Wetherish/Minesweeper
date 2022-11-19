//
// Created by Bartek on 08.04.2022.
//

#ifndef UNTITLED_MSSFMLVIEW_H
#define UNTITLED_MSSFMLVIEW_H
#include "SFML/Graphics.hpp"
#include "MinesweeperBoard.h"

#include <cmath>


class MSSFMLView {
    MinesweeperBoard & board;
private:
    sf::Font font;
public:
    explicit MSSFMLView(MinesweeperBoard & board);
    float scale(sf::RenderWindow &window) const;
    void draw(sf::RenderWindow &win);
};

#endif //UNTITLED_MSSFMLVIEW_H
