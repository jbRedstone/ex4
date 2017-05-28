#pragma once

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <vector>
#include <ctime>
#include "Stick.hpp"
#include "types.hpp"

class Board
{
public:
    
    Board();
    void draw(sf::RenderWindow & window);
    void collisionCheck(sf::Vector2i MousePos);
    void deleteStick(subMap::const_iterator i);
    subMap makeSubset(sf::Vector2i MousePos);
    
private:
    
     // The ints here will hold an order of placement, so the lower the int the "higher" the stick
    stickVector m_sticks;
    
    //hold a data structure of pointers to the sorted based on x-ints of sticks' centres
    xCoordinateMap m_xSortedSticks;
};
