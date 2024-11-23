#ifndef ALGORITHMS_H
#define ALGORITHMS_H

#include "Constants.h"

#define mainColor sf::Color::Magenta
#define mainSize 35

// -------------------------------------------------------------- //
// ----------------- ALGORITMOS DE ORDENAMIENTO ----------------- //
// -------------------------------------------------------------- //

void drawArray(sf::RenderWindow&, const std::vector<int>&, int = -1, int = -1);
void drawArray2(sf::RenderWindow &window, const std::vector<int> &v, int left = -1, int right = -1, int mid = -1, const std::string& info = "");

void bubbleSortVisualized(sf::RenderWindow&, std::vector<int>&);

void selectionSortVisualized(sf::RenderWindow&, std::vector<int>&);

void insertionSortVisualized(sf::RenderWindow&, std::vector<int>&);

void mergeSortVisualized(sf::RenderWindow&, std::vector<int>&);
void mergeSortRecursive(sf::RenderWindow&, std::vector<int>&, int, int, sf::Font&);
void merge(sf::RenderWindow&, std::vector<int>&, int, int, int, sf::Font&);

int partition(sf::RenderWindow &window, std::vector<int> &v, int low, int high);
void quickSortVisualizedRecursive(sf::RenderWindow &window, std::vector<int> &v, int low, int high);
void quickSortVisualized(sf::RenderWindow &window, std::vector<int> &v);

// ---------------------------------------------------------- //
// ----------------- ALGORITMOS DE BUSQUEDA ----------------- //
// ---------------------------------------------------------- //

void linearSearchVisualized(sf::RenderWindow &window, std::vector<int> &v, int target);

int partition2(std::vector<int> &vec, int low, int high);
void quickSort(std::vector<int> &vec, int low, int high);
int binarySearchVisualized(sf::RenderWindow &window, std::vector<int> &v, int target);

#endif // ALGORITHMS_H