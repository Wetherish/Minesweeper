//
// Created by Bartek on 08.04.2022.
//

#include "MSSFMLView.h"
MSSFMLView::MSSFMLView(MinesweeperBoard & b) : board(b) {
}

void MSSFMLView::draw (sf::RenderWindow & win ) {
    sf::Font font;
    if(!font.loadFromFile("../ALGER.ttf"))
    {
        return;
    }
    sf::Text text;
    text.setFont(font);
    sf::Text flag;
    flag.setFont(font);
    sf::RectangleShape plansza(sf::Vector2f(scale(win), scale(win)));
    plansza.setFillColor(sf::Color(142, 17, 195));

    int TmpCol;
    for (int row = 0; row < board.get_height(); row++) {
        for (TmpCol = row % 2; TmpCol < board.get_width(); TmpCol += 2)
        {
            plansza.setPosition(float(TmpCol) * scale(win), float(row) * scale(win));

            if (board.getFieldInfo(row, TmpCol) == '_') {
                plansza.setFillColor(sf::Color(216, 145, 246));
                win.draw(plansza);
            }
            if (board.getFieldInfo(row, TmpCol) == ' ') {
                plansza.setFillColor(sf::Color(189, 167,168));
                win.draw(plansza);
            }
            if (board.getFieldInfo(row, TmpCol) == 'F') {
                plansza.setFillColor(sf::Color(216, 145, 246));
                win.draw(plansza);
            }
            if (board.getFieldInfo(row, TmpCol) == (board.countMines(row, TmpCol)+'0')) {
                plansza.setFillColor(sf::Color(176,161,176));
                win.draw(plansza);

            }
            win.draw(plansza);
            if ( board.getFieldInfo(row, TmpCol) == 'x'){
                plansza.setFillColor(sf::Color::Black);
                win.draw(plansza);

            }


        }


    }

    for (int row = 0; row < board.get_height(); row++) {
        for (TmpCol = (row + 1) % 2; TmpCol < board.get_width(); TmpCol += 2)
        {
            plansza.setPosition(float(TmpCol) * scale(win), float(row) * scale(win));

            if (board.getFieldInfo(row, TmpCol) == '_') {
                plansza.setFillColor(sf::Color(142, 17, 195));
                win.draw(plansza);
            }
            if (board.getFieldInfo(row, TmpCol) == ' ') {
                plansza.setFillColor(sf::Color(176, 160,160));
                win.draw(plansza);
            }
            if (board.getFieldInfo(row, TmpCol) == 'F') {
                plansza.setFillColor(sf::Color(142, 17, 195));
                win.draw(plansza);
            }
            if (board.getFieldInfo(row, TmpCol) == (board.countMines(row, TmpCol)+'0')) {
                plansza.setFillColor(sf::Color(168,158,169));
                win.draw(plansza);
            }

            if ( board.getFieldInfo(row, TmpCol) == 'x') {
                plansza.setFillColor(sf::Color::Black);
                win.draw(plansza);
            }
        }
    }
    for (int row = 0; row < board.get_height() ; ++row)
    {
        for (int col = 0; col < board.get_width(); ++col)
        {
            if (board.getFieldInfo(row, col) == (board.countMines(row, col) + '0'))
            {
                std::string newString;
                newString = board.countMines(row, col) + '0';
                text.setPosition(col * scale(win), row * scale(win));
                text.setCharacterSize(scale(win));
                text.setString(newString);
            }

            if (board.getFieldInfo(row, col) == 'F')
            {
                std::string flagstring = "F";
                flag.setPosition(col * scale(win), row * scale(win));
                flag.setCharacterSize(scale(win));
                flag.setString(flagstring);
            }

                win.draw(text);
                win.draw(flag);

        }

    }
}
float MSSFMLView::scale(sf::RenderWindow &win) const {
    float scale;
    float pole = float(board.get_height()) * float(board.get_width()); //
    float SpaceOnScrean = win.getSize().x * win.getSize().y;
    scale = SpaceOnScrean / pole ;
   // std::cout << scale;
    scale = float(sqrt(double(scale))) ;
    float range_Height = float(board.get_height()) * scale ;
    float range_Width = float(board.get_width()) * scale ;
  while(win.getSize().y < range_Height)
  {
      scale -=1;
      range_Height = float(board.get_height()) * scale ;
  }
    while(win.getSize().x < range_Width)
    {
        scale -=1;
        range_Width = float(board.get_width()) * scale ;
    }

    return scale;

}





