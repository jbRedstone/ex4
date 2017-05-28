#pragma once

#include <vector>
#include <map>

class Stick;

const int BOARD_X = 1500;
const int BOARD_Y = 1000;

const int STICK_NUM = 100; //FIXME change this based on level of hardness

typedef std::pair<float, float> location;

class xLess {public: bool operator()(const location l1, const location l2) const {return l1.first < l2.first;}};
class yLess {public: bool operator()(const location l1, const location l2) const {return l1.second < l2.second;}};

typedef std::multimap< location, std::pair<int, Stick> *, xLess> xCoordinateMap;
typedef std::multimap< location, std::pair<int, Stick> *, yLess> yCoordinateMap;

typedef std::multimap< int, std::pair<int, Stick> *, std::less<int>> subMap;
typedef std::vector<std::pair<int, Stick>> stickVector;
//FIXME: maybe make stick vector a <int, Stick*> map instead of all this pair business. this might fix the vector length error...

const sf::Vector2f STICK_SIZE (20,350);
const float STICK_ANGLE(50);
const float STICK_OUTLINE_THICKNESS(1);
