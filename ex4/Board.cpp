#include "Board.hpp"

Board::Board()
{
    std::srand(std::time(0));
    
    for (int i = 0; i < STICK_NUM; i ++)
    {
        Stick s;
        std::pair<int, Stick> sPair(i, s);
        m_sticks.push_back(sPair);
        m_xSortedSticks.insert(coordinateMap::value_type(s.getX(), & sPair));
//        m_ySortedSticks.insert(coordinateMap::value_type(s.getY(), & sPair));
    }
}

void Board::draw(sf::RenderWindow & window)
{
    for (stickVector::iterator i = m_sticks.begin(); i != m_sticks.end(); ++i)
    {
        i -> second.draw(window);
    }
}

void Board::collisionCheck(sf::Vector2i MousePos)
{
    //subset of all sticks in the range of the mouse position
    subMap subSet = makeSubset(MousePos);
    
    subMap::const_iterator low = subSet.begin();
    subMap::const_iterator up = subSet.end();
    subMap::const_iterator i = low;
    
    //iterate through the subset, and see if the mouse is touching any stick
    while (i != up && !(i->second->second.get().getGlobalBounds().contains(MousePos.x,MousePos.y)))
    {
        ++i;
    }
    
    //if the mouse isn't touching a stick, exit the function
    if (!(i->second->second.get().getGlobalBounds().contains(MousePos.x,MousePos.y)))
        return;
    
    bool covered = false;
    
    //if the mouse is touching a stick, see if this stick has any clashes with sticks close to it that are of a lower number. The lower the number the "higher" the stick, hence this checks all the sticks which may be above the clicked one.
    for (subMap::const_iterator j = i; j != low; --j)
    {
        //check to see if covered by other stick
        if (i->second->second.get().getGlobalBounds().intersects((j->second->second.get().getGlobalBounds())))
        {
            //if covered make the covering ones flash
            j->second->second.flash();
            covered = true;
        }
    }
    
    //if not covered, delete it from all arrays
    if (!covered)
    {
        deleteStick(i);
    }
    
}

subMap Board::makeSubset(sf::Vector2i MousePos)
{
    subMap subSet;
    
    //make iterators to iterate through all the sticks at the relavant x-variables
    coordinateMap::const_iterator lowX = m_xSortedSticks.lower_bound(MousePos.x - STICK_SIZE.y);
    coordinateMap::const_iterator upX = m_xSortedSticks.upper_bound(MousePos.x + STICK_SIZE.y);
    
    //from all sticks in the x-area, make subset of sticks also in the y-area
    for (coordinateMap::const_iterator i = lowX; i != upX; ++i)
    {
        float stickY = ((i -> second) -> second).getY();
        float mouseY = MousePos.y;
        
        //after adding these, the subset will contain pointers to all the sticks in the range of the mouse
        if ((stickY > (mouseY - STICK_SIZE.y)) && (stickY < (mouseY - STICK_SIZE.y)))
        {
            subSet.insert(std::pair<int, std::pair<int, Stick> *>(i->second->first, i->second));
        }
    }
    
    return subSet;
}

void Board::deleteStick(subMap::const_iterator i)
{
    std::cout << "Delete this stick" << std::endl; //FIXME
}
