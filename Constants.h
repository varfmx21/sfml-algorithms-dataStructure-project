#include <SFML/Graphics.hpp>
#include <vector>
#include <chrono>                 
#include <thread>                 
#include <algorithm>              
#include <iostream>               
#include <sstream>

#define mainColor sf::Color::Magenta // Color que resalta
#define mainSize 35 // Tamaño de la letra
#define MAX_NUMBER_OF_ITEMS 5 // Main menu options
#define MAX_SUBMENU_ITEMS 6   // Maximum number of items in any submenu