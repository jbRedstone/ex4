#include "Stick.hpp"

Stick::Stick()
{
    int xPos = (std::rand() % (BOARD_X - 2*((int)STICK_SIZE.y))) + (int)STICK_SIZE.y;
    int yPos = (std::rand() % (BOARD_Y - 2*((int)STICK_SIZE.y))) + (int)STICK_SIZE.y;
    
    m_rectangle.setPosition(xPos, yPos);
    m_rectangle.setSize(STICK_SIZE);
    m_rectangle.setFillColor(sf::Color (std::rand() % 255, std::rand() % 255, std::rand() % 255));
    m_rectangle.setOutlineColor(sf::Color::White);
    m_rectangle.setOutlineThickness(STICK_OUTLINE_THICKNESS);
    m_rectangle.setRotation(std::rand() % 360);
    
    try
    {
        if (m_rectangle.getRotation() == 0)
            throw InvalidAngle();
    }
    catch (InvalidAngle)
    {
        m_rectangle.setRotation(STICK_ANGLE);
    }
    
}

sf::RectangleShape Stick::get()
{
    return m_rectangle;
}

float Stick::getX()
{
    return m_rectangle.getPosition().x;
}

float Stick::getY()
{
    return m_rectangle.getPosition().y;
}

void Stick::draw(sf::RenderWindow & window)
{
    window.draw(m_rectangle);
}

void Stick::flash()
{
    m_flash = true;
    std::cout<<"Flasing!!" << std::endl;
    //FIXME: turn off after one second
}

bool Stick::getFlash()
{
    return m_flash;
}
