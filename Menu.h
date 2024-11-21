#ifndef MENU_H
#define MENU_H

#include <SFML/Graphics.hpp>

#define MAX_NUMBER_OF_ITEMS 5 // Main menu options
#define MAX_SUBMENU_ITEMS 6   // Maximum number of items in any submenu
#define mainColor sf::Color::Magenta

class Menu {
public:
    Menu(float width, float height);
    ~Menu();

    void draw(sf::RenderWindow &window);
    void MoveUp(int size);
    void MoveDown(int size);
    void ShowSubMenu(int index);
    void ExitSubMenu();

    int GetPressedItem() const { return selectedItemIndex; }
    int GetCurrentSubMenu() const;

private:
    int selectedItemIndex;
    bool inSubMenu;            // Indicates if the user is in a submenu
    int currentSubMenu;        // Index of the current submenu

    sf::Font font;
    sf::Text menu[MAX_NUMBER_OF_ITEMS];                      // Main menu items
    sf::Text subMenu[MAX_NUMBER_OF_ITEMS - 1][MAX_SUBMENU_ITEMS]; // Submenu items

    void ResetMenu(); // Resets menu state when exiting a submenu
};

#endif // MENU_H
