#pragma once

#include <vector>
#include <map>

class Stick;

const int BOARD_X = 1500;
const int BOARD_Y = 1000;

const int STICK_NUM = 100; //FIXME change this based on level of hardness


typedef std::pair<float, float> location;
typedef std::multimap< float, std::pair<int, Stick> *, std::less< float > > coordinateMap;
typedef std::multimap< int, std::pair<int, Stick> *, std::less<int>> subMap;
typedef std::vector<std::pair<int, Stick>> stickVector;

const sf::Vector2f STICK_SIZE (20,350);
const float STICK_ANGLE(50);
const float STICK_OUTLINE_THICKNESS(1);
