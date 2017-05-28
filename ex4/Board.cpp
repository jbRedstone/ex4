#include "Board.hpp"

Board::Board()
{
    std::srand(std::time(0));
    
    for (int i = 0; i < STICK_NUM; i ++)
    {
        Stick s;
        std::pair<int, Stick> sPair(i, s);
        m_sticks.push_back(sPair);
        m_xSortedSticks.insert(xCoordinateMap::value_type(s.getLocation(), & sPair));
    }
    
    for (xCoordinateMap::const_iterator i = m_xSortedSticks.lower_bound(location(0, 1));
         i !=  m_xSortedSticks.upper_bound(location(BOARD_X, 1)); ++i)
    {
        std::cout << "added stick to Xmap @" << (i->first).first << std::endl;
//        ySortedSticks.insert(*i);
    }
    std::cout << std::endl;

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
    
    for (subMap::const_iterator p = subSet.begin(); p != subSet.end(); ++p)
    {
        std::cout<< "looped" << std::endl;

        if ((p->second->second.get().getGlobalBounds().contains(MousePos.x,MousePos.y)))
        {
            i = p;
            break;
        }
    }
    
    //iterate through the subset, and see if the mouse is touching any stick
//    while (i != up || !(i->second->second.get().getGlobalBounds().contains(MousePos.x,MousePos.y)))
//    {
//        ++i;
//    }
//    
    std::cout<< "subset made!" << std::endl;

    
    //if the mouse isn't touching a stick, exit the function
    if (!(i->second->second.get().getGlobalBounds().contains(MousePos.x,MousePos.y)))
        return;
    
    std::cout << "Mouse @ (" << MousePos.x << "," << MousePos.y << ")" << std::endl;
    std::cout << "Stick @ (" << i->second->second.getLocation().first << "," << i->second->second.getLocation().second << ")" << std::endl;

    
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
//    std::cout << "Mouse @ (" << MousePos.x << "," << MousePos.y << ")" << std::endl;
    
    yCoordinateMap ySortedSticks;
    
    for (xCoordinateMap::const_iterator i = m_xSortedSticks.lower_bound(location(MousePos.x - STICK_SIZE.y, 1));
         i !=  m_xSortedSticks.upper_bound(location(MousePos.x + STICK_SIZE.y, 1)); ++i)
    {
//        std::cout << "added stick to Ymap @ (" << (i->first).first << "," << (i->first).second << ")" << std::endl;
        ySortedSticks.insert(*i);
    }
    
    subMap subSet;
    
//    std::cout << std::endl;
    
    for (yCoordinateMap::const_iterator i = ySortedSticks.lower_bound(location(1, MousePos.y - STICK_SIZE.y));
         i !=  ySortedSticks.upper_bound(location(1, MousePos.y + STICK_SIZE.y)); ++i)
    {
//        std::cout << "added stick to SubMap @ (" << (i->first).first << "," << (i->first).second << ")" << std::endl;
        subSet.insert(subMap::value_type((i->second) -> first , i->second));
    }
    

    
    return subSet;
}

void Board::deleteStick(subMap::const_iterator i)
{
    std::cout << "Delete this stick" << std::endl; //FIXME
}
