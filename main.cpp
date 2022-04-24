
#include "MinesweeperBoard.h"
#include "MSBoardTextView.h"
#include "MSTextController.h"
#include "MSSFMLCONTROL.h"
#include "MSSFMLView.h"
#include "SFML/Window.hpp"
#include "MSSFMLView.h"
using namespace std;
void intro()
{

    cout<<"Bartosz Kozlowski 96\n";
}

int main() {


    intro();
    srand(time(nullptr));
    MinesweeperBoard board(10,10, EASY);
    MSSFMLView view (board);
    sf::RenderWindow window(sf::VideoMode(1920, 850), "Grafika w C++/SFML");
    MSSFMLCONTROL control (board, view);
    window.setVerticalSyncEnabled(false);
    window.setFramerateLimit(30);
    // symulujemy rozgrywkę

//    board.revealField(3, 3);
//    board.revealField(0, 0);
//    board.revealField(1, 1);
//   board.revealField(3, 0);
//    board.toggleFlag(5,5);
//    board.debug_display();
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            switch (event.type)
            {
                case sf::Event::Closed:
                    window.close();
                    break;

                case sf::Event::MouseButtonPressed:
                    switch (event.key.code)
                    {
                        case sf::Mouse::Left:
                            control.gameplay(event,window);
                            break;
                        case sf::Mouse::Right:
                            control.gameplay(event,window);
                            break;
                    }
                    break;
            }

        }

        window.clear();
        view.draw(window);
        window.display();
    }

// play.akcja();
    return 0;
    }
