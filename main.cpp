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
                                                case 0: std::cout << "Binary Tree AVL selected!" << std::endl; break;
                                                case 1: {
                                                    //------------------------------//
                                                    //-----------DJIKSTRA-----------//
                                                    //------------------------------//

                                                    sf::Font font;
                                                    if (!font.loadFromFile("path/to/font.ttf")) {
                                                        std::cerr << "Error loading font" << std::endl;
                                                    }
                                                    sf::Text infoText("Select start node (click), then end node, press SPACE to run", font, 20);
                                                    infoText.setFillColor(sf::Color::White);
                                                    infoText.setPosition(10, 10);

                                                    std::vector<Node> nodes;
                                                    std::vector<Edge> edges;

                                                    // Generate default graph with 8 nodes
                                                    generateDefaultGraph(nodes, edges, font, 8);

                                                    int startNode = -1, endNode = -1;
                                                    bool selectingStart = true;
                                                    bool isSubMenuActive = true;

                                                    while (isSubMenuActive && window.isOpen()) {
                                                        sf::Event event;
                                                        while (window.pollEvent(event)) {
                                                            if (event.type == sf::Event::Closed) {
                                                                window.close();
                                                            }
                                                            if (event.type == sf::Event::MouseButtonPressed) {
                                                                sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                                                                for (auto& node : nodes) {
                                                                    if (node.shape.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos))) {
                                                                        if (selectingStart) {
                                                                            startNode = node.id;
                                                                            node.shape.setFillColor(sf::Color::Green);
                                                                            selectingStart = false;
                                                                            infoText.setString("Select end node (click)");
                                                                        } else if (!selectingStart && node.id != startNode) {
                                                                            endNode = node.id;
                                                                            node.shape.setFillColor(sf::Color::Red);
                                                                            infoText.setString("Press SPACE to find shortest path");
                                                                        }
                                                                    }
                                                                }
                                                            }
                                                            if (event.type == sf::Event::KeyPressed) {
                                                                if (event.key.code == sf::Keyboard::Escape) {
                                                                    isSubMenuActive = false;
                                                                }
                                                                else if (event.key.code == sf::Keyboard::Space) {
                                                                    if (startNode != -1 && endNode != -1) {
                                                                        runDijkstra(window, nodes, edges, startNode, endNode);
                                                                        // After Dijkstra completes
                                                                        isSubMenuActive = false;
                                                                    }
                                                                }
                                                            }
                                                        }

                                                        window.clear();
                                                        drawGraph(window, nodes, edges, infoText);
                                                        window.display();
                                                    }

                                                    menu.ExitSubMenu();
                                                    break;
                                                }
                                                case 2: {

                                                    //-------------------------//
                                                    //-----------DFS-----------//
                                                    //-------------------------//

                                                    Maze maze(21,21,20);
                                                    maze.draw(window);
                                                    window.display();

                                                    if (maze.solveMazeBFS(window)) { // Using DFS-based solveMaze
                                                        std::cout << "Maze solved using BFS!" << std::endl;
                                                    } else {
                                                        std::cout << "Maze could not be solved using BFS!" << std::endl;
                                                    }

                                                    // Keep the window open to display the solution
                                                    while (true) {
                                                        sf::Event event;
                                                        if (window.pollEvent(event)) {
                                                            menu.ExitSubMenu();
                                                            break;
                                                        }
                                                    }
                                                    break;
                                                }
                                                case 3:  {

                                                    //-------------------------//
                                                    //-----------BFS-----------//
                                                    //-------------------------//

                                                    Maze maze(21,21,20);
                                                    maze.draw(window);
                                                    window.display();

                                                    if (maze.solveMaze(window)) { // Using DFS-based solveMaze
                                                        std::cout << "Maze solved using DFS!" << std::endl;
                                                    } else {
                                                        std::cout << "Maze could not be solved using DFS!" << std::endl;
                                                    }

                                                    // Keep the window open to display the solution
                                                    while (true) {
                                                        sf::Event event;
                                                        if (window.pollEvent(event)) {
                                                            menu.ExitSubMenu();
                                                            break;
                                                        }
                                                    }
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