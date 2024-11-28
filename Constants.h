// LUIS FERNANDO VALDERRABANO GARCIA A01644530

#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <chrono>                 
#include <thread>                 
#include <algorithm>              
#include <iostream>               
#include <sstream>
#include <queue>
#include <random>
#include <string>
#include <unordered_map>
#include <iomanip>

#define mainColor sf::Color::Magenta // Color que resalta
#define mainSize 35 // Tamaño de la letra
#define MAX_NUMBER_OF_ITEMS 5 // Main menu options
#define MAX_SUBMENU_ITEMS 6   // Maximum number of items in any submenu

const int FAST_VISUALIZATION_DELAY = 50;  // Reduced from 200ms to 20ms
const int PATH_TRACE_DELAY = 30;          // Reduced from 50ms to 10ms