#include <SFML/Graphics.hpp>
#include "Board.hpp"
#include "Stick.hpp"
#include "Exception.hpp"
#include "InvalidAngle.hpp"
#include "types.hpp"


int main()
{
    // Create the main window
    sf::RenderWindow window(sf::VideoMode(BOARD_X, BOARD_Y), "Pick-Up Sticks");
    
    Board board;

    // Start the game loop
    while (window.isOpen())
    {
        // Process events
        sf::Event event;
        while (window.pollEvent(event))
        {
            // Close window: exit
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }

            // Escape pressed: exit
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
            {
                window.close();
            }
            
            if (event.type == sf::Event::MouseButtonPressed)
            {
                board.collisionCheck(sf::Mouse::getPosition(window));
            }
        }

        // Clear screen
        window.clear();
        
        // Draw board of sticks
        board.draw(window);

        // Update the window
        window.display();
    }

    return EXIT_SUCCESS;
}
