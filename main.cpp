// LUIS FERNANDO VALDERRABANO GARCIA A01644530

// Crear el archivo o
// g++ -IC:\SFML-2.6.1\include -c main.cpp -o main.o 

// Crear la aplicación exe
// g++ -LC:\SFML-2.6.1\lib .\main.o -o app.exe -lmingw32 -lsfml-graphics -lsfml-window -lsfml-system -lsfml-main -mwindows

// g++ -IC:\SFML-2.6.1\include -LC:\SFML-2.6.1\lib main.cpp Menu.cpp -o app.exe -lmingw32 -lsfml-graphics -lsfml-window -lsfml-system -lsfml-main -mwindows
#include "Menu.h"
#include <SFML/Graphics.hpp>

#include "Algorithms.cpp"

#include <iostream>
#include <vector>

// Declare the number of items for each submenu
std::vector<int> subMenuSizes = {
    6,  // Sorting Algorithms submenu (5 items)
    4,  // Linear Data Structures submenu (3 items)
    5,  // Non-Linear Data Structures submenu (4 items)
    3   // Searching Algorithms submenu (2 items)
};

int main() {
    sf::RenderWindow window(sf::VideoMode(1600, 800), "SFML Menu with Submenus");
    Menu menu(window.getSize().x, window.getSize().y);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            switch (event.type) {
                case sf::Event::KeyReleased:
                    switch (event.key.code) {
                        case sf::Keyboard::Up:
                            if (menu.GetCurrentSubMenu() == -1) {
                                menu.MoveUp(MAX_NUMBER_OF_ITEMS); // Main menu navigation
                            } else {
                                menu.MoveUp(subMenuSizes[menu.GetCurrentSubMenu()]); // Submenu navigation
                            }
                            break;

                        case sf::Keyboard::Down:
                            if (menu.GetCurrentSubMenu() == -1) {
                                menu.MoveDown(MAX_NUMBER_OF_ITEMS); // Main menu navigation
                            } else {
                                menu.MoveDown(subMenuSizes[menu.GetCurrentSubMenu()]); // Submenu navigation
                            }
                            break;

                        case sf::Keyboard::Return:
                            if (menu.GetCurrentSubMenu() == -1) {
                                if (menu.GetPressedItem() == 4) { // Exit option in main menu
                                    window.close();
                                } else {
                                    menu.ShowSubMenu(menu.GetPressedItem()); // Open selected submenu
                                }
                            } else {
                                int currentSubMenu = menu.GetCurrentSubMenu();
                                if (menu.GetPressedItem() == subMenuSizes[currentSubMenu] - 1) { // "Back" option
                                    menu.ExitSubMenu();
                                } else {
                                    // Handle actions for specific submenu items
                                    switch (currentSubMenu) {
                                        case 0: // Sorting Algorithms
                                            switch (menu.GetPressedItem()) {
                                                case 0: std::cout << "Bubble Sort selected!" << std::endl; break;
                                                case 1: std::cout << "Selection Sort selected!" << std::endl; break;
                                                case 2: std::cout << "Insertion Sort selected!" << std::endl; break;
                                                case 3: std::cout << "Merge Sort selected!" << std::endl; break;
                                                case 4: std::cout << "Quick Sort selected!" << std::endl; break;
                                            }
                                            break;
                                        case 1: // Linear Data Structures
                                            switch (menu.GetPressedItem()) {
                                                case 0: std::cout << "Stacks selected!" << std::endl; break;
                                                case 1: std::cout << "Queues selected!" << std::endl; break;
                                                case 2: std::cout << "Linked Lists selected!" << std::endl; break;
                                            }
                                            break;
                                        case 2: // Non-Linear Data Structures
                                            switch (menu.GetPressedItem()) {
                                                case 0: std::cout << "Binary Tree AVL selected!" << std::endl; break;
                                                case 1: std::cout << "Dijkstra's Algorithm selected!" << std::endl; break;
                                                case 2: std::cout << "DFS (Depth-First Search) selected!" << std::endl; break;
                                                case 3: std::cout << "BFS (Breadth-First Search) selected!" << std::endl; break;
                                            }
                                            break;
                                        case 3: // Searching Algorithms
                                            switch (menu.GetPressedItem()) {
                                                case 0: std::cout << "Linear Search selected!" << std::endl; break;
                                                case 1: std::cout << "Binary Search selected!" << std::endl; break;
                                            }
                                            break;
                                    }
                                }
                            }
                            break;
                    }
                    break;

                case sf::Event::Closed:
                    window.close();
                    break;
            }
        }

        window.clear();
        menu.draw(window);
        window.display();
    }

    return 0;
}