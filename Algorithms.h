#ifndef ALGORITHMS_H
#define ALGORITHMS_H

#include <SFML/Graphics.hpp>
#include <vector>

void drawArray(sf::RenderWindow&, const std::vector<int>&, int = -1, int = -1);

void bubbleSortVisualized(sf::RenderWindow&, std::vector<int>&);

void selectionSortVisualized(sf::RenderWindow&, std::vector<int>&);

void insertionSortVisualized(sf::RenderWindow&, std::vector<int>&);

void mergeSortVisualized(sf::RenderWindow&, std::vector<int>&);
void mergeSortRecursive(sf::RenderWindow&, std::vector<int>&, int, int, sf::Font&);
void merge(sf::RenderWindow&, std::vector<int>&, int, int, int, sf::Font&);

int partition(sf::RenderWindow &window, std::vector<int> &v, int low, int high);
void quickSortVisualizedRecursive(sf::RenderWindow &window, std::vector<int> &v, int low, int high);
void quickSortVisualized(sf::RenderWindow &window, std::vector<int> &v);

#endif // ALGORITHMS_H