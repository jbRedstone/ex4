#pragma once

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include "InvalidAngle.hpp"
#include "types.hpp"

class Stick
{
public:
    Stick();
    sf::RectangleShape get(); //returns rectangle of stick
    void flash(); //makes stick rectangle blink to show it's ontop of another
    float getX();
    float getY();
    void draw(sf::RenderWindow & window);
    bool getFlash();
private:
    sf::RectangleShape m_rectangle;
    bool m_flash = false;
};
