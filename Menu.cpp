#include "Menu.h"
#include <iostream>

Menu::Menu(float width, float height) : selectedItemIndex(0), inSubMenu(false), currentSubMenu(-1) {
    if (!font.loadFromFile("knightWarrior.otf")) {
        // Manejar error de carga de fuente
    }

    // Configurar opciones del menú principal
    std::string menuOptions[MAX_NUMBER_OF_ITEMS] = {
        "ALGORITMOS DE ORDENAMIENTO",
        "ESTRUCTURAS LINEALES",
        "ESTRUCTURAS NO LINEALES",
        "ALGORITMOS DE BUSQUEDA",
        "EXIT"
    };

    for (int i = 0; i < MAX_NUMBER_OF_ITEMS; i++) {
        menu[i].setFont(font);
        menu[i].setFillColor(i == 0 ? mainColor : sf::Color::White);
        menu[i].setString(menuOptions[i]);
        float textWidth = menu[i].getLocalBounds().width;
        menu[i].setPosition(sf::Vector2f((width - textWidth) / 2, height / (MAX_NUMBER_OF_ITEMS + 1) * (i + 1)));
    }

    // Configurar submenús
    std::string sortingSubMenu[MAX_SUBMENU_ITEMS] = {
        "Bubble Sort", "Selection Sort", "Insertion Sort", "Merge Sort", "Quick Sort", "Back"
    };
    std::string linearDataSubMenu[MAX_SUBMENU_ITEMS] = {
        "Pilas (Stacks)", "Filas (Queues)", "Linked Lists", "Back"
    };
    std::string nonLinearDataSubMenu[MAX_SUBMENU_ITEMS] = {
        "Arboles Binarios AVL", "Algoritmo de Dijkstra", "DFS", "BFS", "Back"
    };
    std::string searchAlgorithmsSubMenu[MAX_SUBMENU_ITEMS] = {
        "Linear Search", "Binaria", "Back"
    };

    std::string* subMenus[MAX_NUMBER_OF_ITEMS - 1] = {
        sortingSubMenu,
        linearDataSubMenu,
        nonLinearDataSubMenu,
        searchAlgorithmsSubMenu,
    };

    // Configurar submenús dinámicamente
    int subMenuSizes[MAX_NUMBER_OF_ITEMS - 1] = {6, 4, 5, 3}; // Cantidad de elementos por submenú

    for (int i = 0; i < MAX_NUMBER_OF_ITEMS - 1; i++) { // Solo configuramos submenús para las opciones especificadas
        for (int j = 0; j < subMenuSizes[i]; j++) {
            subMenu[i][j].setFont(font);
            subMenu[i][j].setString(subMenus[i][j]);
            subMenu[i][j].setCharacterSize(30);
            subMenu[i][j].setPosition(sf::Vector2f(
                (width - subMenu[i][j].getLocalBounds().width) / 2,
                height / (subMenuSizes[i] + 1) * (j + 1)
            ));
        }
    }
}

Menu::~Menu() {}

void Menu::draw(sf::RenderWindow &window) {
    if (inSubMenu) {
        int subMenuSize = 0;

        // Determinar el tamaño del submenú actual
        switch (currentSubMenu) {
            case 0: subMenuSize = 6; break; // Algoritmos de ordenamiento
            case 1: subMenuSize = 4; break; // Estructuras lineales
            case 2: subMenuSize = 5; break; // Estructuras no lineales
            case 3: subMenuSize = 3; break; // Algoritmos de búsqueda
        }

        for (int i = 0; i < subMenuSize; i++) {
            window.draw(subMenu[currentSubMenu][i]);
        }
    } else {
        for (int i = 0; i < MAX_NUMBER_OF_ITEMS; i++) {
            window.draw(menu[i]);
        }
    }
}

void Menu::MoveUp(int size) {
    if (inSubMenu) {
        // Handle submenu navigation
        subMenu[currentSubMenu][selectedItemIndex].setFillColor(sf::Color::White);
        selectedItemIndex = (selectedItemIndex - 1 + size) % size; // Move up in the submenu
        subMenu[currentSubMenu][selectedItemIndex].setFillColor(mainColor);
    } else {
        // Handle main menu navigation
        menu[selectedItemIndex].setFillColor(sf::Color::White);
        selectedItemIndex = (selectedItemIndex - 1 + MAX_NUMBER_OF_ITEMS) % MAX_NUMBER_OF_ITEMS; // Move up in the main menu
        menu[selectedItemIndex].setFillColor(mainColor);
    }
}

void Menu::MoveDown(int size) {
    if (inSubMenu) {
        // Handle submenu navigation
        subMenu[currentSubMenu][selectedItemIndex].setFillColor(sf::Color::White);
        selectedItemIndex = (selectedItemIndex + 1 + size) % size; // Move down in the submenu
        subMenu[currentSubMenu][selectedItemIndex].setFillColor(mainColor);
    } else {
        // Handle main menu navigation
        menu[selectedItemIndex].setFillColor(sf::Color::White);
        selectedItemIndex = (selectedItemIndex + 1 + MAX_NUMBER_OF_ITEMS) % MAX_NUMBER_OF_ITEMS; // Move down in the main menu
        menu[selectedItemIndex].setFillColor(mainColor);
    }
}

void Menu::ShowSubMenu(int index) {
    if (index < MAX_NUMBER_OF_ITEMS - 1) {  // Only show submenus for the first four options
        inSubMenu = true;
        currentSubMenu = index;
        selectedItemIndex = 0;
        subMenu[currentSubMenu][selectedItemIndex].setFillColor(mainColor);
    } else {
        std::cerr << "Invalid submenu index: " << index << std::endl;
    }
}

void Menu::ResetMenu() {
    for (int i = 0; i < MAX_NUMBER_OF_ITEMS; i++) {
        menu[i].setFillColor(sf::Color::White); // Reset all main menu items to white
    }
    for (int i = 0; i < MAX_NUMBER_OF_ITEMS - 1; i++) {
        for (int j = 0; j < MAX_SUBMENU_ITEMS; j++) {
            subMenu[i][j].setFillColor(sf::Color::White); // Reset all submenu items to white
        }
    }
    
    // Reset selection index to the main menu and highlight the first item
    selectedItemIndex = 0;
    menu[selectedItemIndex].setFillColor(mainColor); // Highlight the first item in the main menu
}

void Menu::ExitSubMenu() {
    inSubMenu = false;
    currentSubMenu = -1; // Reset current submenu to -1
    ResetMenu();         // Reset colors and highlight the main menu's first item
}

int Menu::GetCurrentSubMenu() const {
    return currentSubMenu;
}