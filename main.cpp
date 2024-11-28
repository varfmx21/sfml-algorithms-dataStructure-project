// LUIS FERNANDO VALDERRABANO GARCIA A01644530

// g++ -IC:\SFML-2.6.1\include -LC:\SFML-2.6.1\lib main.cpp Menu.cpp -o app.exe -lmingw32 -lsfml-graphics -lsfml-window -lsfml-system -lsfml-main -mwindows
#include "Constants.h"
#include "Menu.h"
#include "Algorithms.h"
#include "Structures.h"
#include "LinearData.h"

// Declare the number of items for each submenu
std::vector<int> subMenuSizes = {
    6,  // Sorting Algorithms submenu (5 items)
    4,  // Linear Data Structures submenu (3 items)
    5,  // Non-Linear Data Structures submenu (4 items)
    3   // Searching Algorithms submenu (2 items)
};

int main() {
    sf::RenderWindow window(sf::VideoMode(1600, 800), "Algorithms and Structures - Project");
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
                                        case 0:
                                        //----------------------------------------//
                                        //-----------SORTING ALGORITMS-----------//
                                        //--------------------------------------//
                                            switch (menu.GetPressedItem()) {
                                                case 0: {

                                                    //---------------------------------//
                                                    //-----------BUBBLESORT-----------//
                                                    //-------------------------------//

                                                    std::vector<int> numbers = menu.getNumbers(window);
                                                    
                                                    bubbleSortVisualized(window, numbers);

                                                    menu.ExitSubMenu();

                                                    break;
                                                }
                                                case 1: {

                                                    //------------------------------------//
                                                    //-----------SELECTIONSORT-----------//
                                                    //----------------------------------//

                                                    std::vector<int> numbers = menu.getNumbers(window);

                                                    selectionSortVisualized(window, numbers);

                                                    menu.ExitSubMenu();

                                                    break;
                                                }
                                                case 2: {

                                                    //------------------------------------//
                                                    //-----------INSERTIONSORT-----------//
                                                    //----------------------------------//

                                                    std::vector<int> numbers = menu.getNumbers(window);

                                                    insertionSortVisualized(window, numbers);

                                                    menu.ExitSubMenu();

                                                    break;
                                                }
                                                case 3: {

                                                    //--------------------------------//
                                                    //-----------MERGESORT-----------//
                                                    //------------------------------//

                                                    std::vector<int> numbers = menu.getNumbers(window);

                                                    mergeSortVisualized(window, numbers);

                                                    menu.ExitSubMenu();

                                                    break;
                                                }
                                                case 4: {

                                                    //--------------------------------//
                                                    //-----------QUICKSORT-----------//
                                                    //------------------------------//

                                                    std::vector<int> numbers = menu.getNumbers(window);

                                                    quickSortVisualized(window, numbers);

                                                    menu.ExitSubMenu();

                                                    break;
                                                }
                                            }
                                            break;
                                        case 1:
                                        //----------------------------------------//
                                        //-----------LINEAL STRUCTURES-----------//
                                        //--------------------------------------//
                                            switch (menu.GetPressedItem()) {
                                                case 0: {

                                                    //----------------------------//
                                                    //-----------STACK-----------//
                                                    //--------------------------//

                                                    Stack stack(window);
                                                    bool isSubMenuActive = true;  // Control the submenu loop

                                                    while (isSubMenuActive && window.isOpen()) {
                                                        sf::Event event;
                                                        while (window.pollEvent(event)) {
                                                            if (event.type == sf::Event::Closed) {
                                                                window.close();  // Close the entire application
                                                            }

                                                            // Check for ESC key to exit the submenu
                                                            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
                                                                isSubMenuActive = false;  // Exit the submenu loop
                                                            }

                                                            stack.handleInput(event, window);  // Handle input for the stack
                                                        }

                                                        window.clear(sf::Color::Black);  // Clear the window with a black background
                                                        stack.draw(window);  // Draw the stack and input prompt
                                                        window.display();  // Display the updated window content
                                                    }

                                                    menu.ExitSubMenu();  // Call the method to handle submenu exit logic
                                                    break;
                                                }
                                                case 1: {
                                                    
                                                    //------------------------------//
                                                    //-------------QUEUE-----------//
                                                    //----------------------------//

                                                    Queue queue(window);
                                                    bool isSubMenuActive = true;

                                                    while (isSubMenuActive && window.isOpen()) {
                                                        sf::Event event;
                                                        while (window.pollEvent(event)) {
                                                            if (event.type == sf::Event::Closed) {
                                                                window.close();
                                                            }

                                                            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
                                                                isSubMenuActive = false;
                                                            }

                                                            queue.handleInput(event, window);
                                                        }

                                                        window.clear(sf::Color::Black);
                                                        queue.draw(window);
                                                        window.display();
                                                    }

                                                    menu.ExitSubMenu();
                                                    break;
                                                }
                                                case 2: {

                                                    //--------------------------------//
                                                    //-----------LINKEDLIST-----------//
                                                    //--------------------------------//

                                                    LinkedList linkedList(window);
                                                    bool isSubMenuActive = true;

                                                    while (isSubMenuActive && window.isOpen()) {
                                                        sf::Event event;
                                                        while (window.pollEvent(event)) {
                                                            if (event.type == sf::Event::Closed) {
                                                                window.close();
                                                            }

                                                            if (event.type == sf::Event::KeyPressed && 
                                                                event.key.code == sf::Keyboard::Escape) {
                                                                isSubMenuActive = false;
                                                            }

                                                            linkedList.handleInput(event, window);
                                                        }

                                                        window.clear(sf::Color::Black);
                                                        linkedList.draw(window);
                                                        window.display();
                                                    }
                                                    
                                                    menu.ExitSubMenu();
                                                    break;
                                                }
                                            }
                                            break;
                                        case 2:
                                        //------------------------------------------//
                                        //-----------STRUCTRAS NO LINEAL-----------//
                                        //----------------------------------------//
                                            switch (menu.GetPressedItem()) {
                                                case 0: {
                                                    //--------------------------//
                                                    //-----------AVL-----------//
                                                    //------------------------//

                                                    AVLTree avlTree(window);
                                                    bool isSubMenuActive = true;

                                                    while (isSubMenuActive && window.isOpen()) {
                                                        sf::Event event;
                                                        while (window.pollEvent(event)) {
                                                            if (event.type == sf::Event::Closed) {
                                                                window.close();
                                                            }

                                                            if (event.type == sf::Event::KeyPressed && 
                                                                event.key.code == sf::Keyboard::Escape) {
                                                                isSubMenuActive = false;
                                                            }

                                                            avlTree.handleInput(event, window);
                                                        }

                                                        window.clear(sf::Color::Black);
                                                        avlTree.draw(window);
                                                        window.display();
                                                    }
                                                    
                                                    menu.ExitSubMenu();
                                                    break;

                                                    break;
                                                }
                                                case 1: {
                                                    //------------------------------//
                                                    //-----------DJIKSTRA-----------//
                                                    //------------------------------//

                                                    Graph graph(window);
                                                    bool isSubMenuActive = true;

                                                    while (isSubMenuActive && window.isOpen()) {
                                                        sf::Event event;
                                                        while (window.pollEvent(event)) {
                                                            if (event.type == sf::Event::Closed) {
                                                                window.close();
                                                            }
                                                            if (event.type == sf::Event::MouseButtonPressed) {
                                                                graph.handleClick(sf::Mouse::getPosition(window));
                                                            }
                                                            if (event.type == sf::Event::KeyPressed && 
                                                                event.key.code == sf::Keyboard::Escape) {
                                                                isSubMenuActive = false;
                                                            }
                                                            if (event.type == sf::Event::KeyPressed && 
                                                                event.key.code == sf::Keyboard::R) {
                                                                graph.reset();
                                                            }
                                                        }

                                                        window.clear(sf::Color::Black);
                                                        graph.draw(window);
                                                        window.display();
                                                    }
                                                    
                                                    menu.ExitSubMenu();
                                                    break;
                                                }
                                                case 2: {

                                                    //-------------------------//
                                                    //-----------BFS-----------//
                                                    //-------------------------//

                                                    visualizeMazeAlgorithm("BFS");
                                                    menu.ExitSubMenu();
                                                    break;
                                                }
                                                case 3:  {

                                                    //-------------------------//
                                                    //-----------DFS-----------//
                                                    //-------------------------//

                                                    visualizeMazeAlgorithm("DFS");
                                                    menu.ExitSubMenu();
                                                    break;
                                                }
                                            }
                                            break;
                                        case 3: // Searching Algorithms
                                            switch (menu.GetPressedItem()) {
                                                case 0: {
                                                    std::vector<int> numbers = menu.getNumbers(window);

                                                    int target = menu.getTarget(window);

                                                    linearSearchVisualized(window, numbers, target);

                                                    menu.ExitSubMenu();

                                                    break;
                                                }
                                                case 1: {
                                                    std::vector<int> numbers = menu.getNumbers(window);

                                                    int target = menu.getTarget(window);

                                                    binarySearchVisualized(window, numbers, target);

                                                    menu.ExitSubMenu();

                                                    break;
                                                    
                                                }
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