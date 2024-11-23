#include <SFML/Graphics.hpp>      // For SFML graphics, including window rendering and sf::Text
#include <vector>                 // For using std::vector
#include <chrono>                 // For timing the sorting process
#include <thread>                 // For introducing delays using std::this_thread::sleep_for
#include <algorithm>              // For std::max_element and std::swap
#include <iostream>               // For debugging or error messages
#include <sstream>                // For dynamically formatting strings using std::ostringstream
#include "Algorithms.h"

void drawArray(sf::RenderWindow &window, const std::vector<int> &v, int highlighted1, int highlighted2) {
    window.clear();

    int n = v.size();
    float barWidth = (window.getSize().x * 0.8f) / n;         // Width for 80% of window width
    float maxBarHeight = window.getSize().y * 0.8f;           // Max height at 80% of window height
    float startX = (window.getSize().x - n * barWidth) / 2.0; // Center start position

    int maxValue = *std::max_element(v.begin(), v.end()); // Maximum value for height scaling

    for (int i = 0; i < n; i++) {
        float barHeight = maxBarHeight * (static_cast<float>(v[i]) / maxValue);

        sf::RectangleShape bar(sf::Vector2f(barWidth - 2, barHeight)); // Width with gap
        bar.setPosition(startX + i * barWidth, window.getSize().y - barHeight);

        if (i == highlighted1 || i == highlighted2) {
            bar.setFillColor(sf::Color::Red);
        } else {
            bar.setFillColor(sf::Color::White);
        }

        window.draw(bar);
    }

    window.display();
}

void bubbleSortVisualized(sf::RenderWindow &window, std::vector<int> &v) {
    int n = v.size();
    sf::Font font;
    
    // Load font for text rendering
    if (!font.loadFromFile("3.ttf")) {
        std::cerr << "Failed to load font!" << std::endl;
        return;
    }

    auto start = std::chrono::high_resolution_clock::now();

    // Bubble sort visualization
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            drawArray(window, v, j, j + 1);
            std::this_thread::sleep_for(std::chrono::milliseconds(200));

            if (v[j] > v[j + 1]) {
                std::swap(v[j], v[j + 1]);

                drawArray(window, v, j, j + 1);
                std::this_thread::sleep_for(std::chrono::milliseconds(200));
            }
        }
    }

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end - start;

    drawArray(window, v);

    // Prepare sorting information text
    sf::Text infoText;
    infoText.setFont(font);
    infoText.setCharacterSize(24);
    infoText.setFillColor(sf::Color::White);

    std::ostringstream infoStream;
    infoStream << "Bubble Sort Visualization\n";
    infoStream << "Time Complexity: O(n^2)\n";
    infoStream << "Elapsed Time: " << elapsed.count() << " seconds\n";
    infoStream << "Sorted Array: ";
    for (const int &num : v) {
        infoStream << num << " ";
    }
    infoStream << "\n\nPress Enter to return to the main menu...";
    
    infoText.setString(infoStream.str());
    infoText.setPosition(50, 50); // Adjust position as needed

    // Display the information and wait for the user to press Enter
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            } else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter) {
                return; // Exit to main menu
            }
        }


        window.clear();
        drawArray(window, v); // Draw the final sorted array
        window.draw(infoText); // Draw the information text
        window.display();
    }
}

void selectionSortVisualized(sf::RenderWindow &window, std::vector<int> &v) {
    int n = v.size();
    sf::Font font;

    // Load font for text rendering
    if (!font.loadFromFile("3.ttf")) {
        std::cerr << "Failed to load font!" << std::endl;
        return;
    }

    auto start = std::chrono::high_resolution_clock::now();

    // Selection sort visualization
    for (int i = 0; i < n - 1; i++) {
        int minIdx = i;
        
        for (int j = i + 1; j < n; j++) {
            drawArray(window, v, minIdx, j); // Highlight the current minimum and the current element
            std::this_thread::sleep_for(std::chrono::milliseconds(200));

            if (v[j] < v[minIdx]) {
                minIdx = j;
            }
        }

        // Swap the found minimum element with the first element of the unsorted portion
        std::swap(v[i], v[minIdx]);

        drawArray(window, v, i, minIdx); // Highlight the swapped elements
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end - start;

    drawArray(window, v); // Draw the final sorted array

    // Prepare sorting information text
    sf::Text infoText;
    infoText.setFont(font);
    infoText.setCharacterSize(24);
    infoText.setFillColor(sf::Color::White);

    std::ostringstream infoStream;
    infoStream << "Selection Sort Visualization\n";
    infoStream << "Time Complexity: O(n^2)\n";
    infoStream << "Elapsed Time: " << elapsed.count() << " seconds\n";
    infoStream << "Sorted Array: ";
    for (const int &num : v) {
        infoStream << num << " ";
    }
    infoStream << "\n\nPress Enter to return to the main menu...";

    infoText.setString(infoStream.str());
    infoText.setPosition(50, 50); // Adjust position as needed

    // Display the information and wait for the user to press Enter
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            } else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter) {
                return; // Exit to main menu
            }
        }

        window.clear();
        drawArray(window, v); // Draw the final sorted array
        window.draw(infoText); // Draw the information text
        window.display();
    }
}

void insertionSortVisualized(sf::RenderWindow &window, std::vector<int> &v) {
    int n = v.size();
    sf::Font font;

    // Load font for text rendering
    if (!font.loadFromFile("3.ttf")) {
        std::cerr << "Failed to load font!" << std::endl;
        return;
    }

    auto start = std::chrono::high_resolution_clock::now();

    // Insertion sort visualization
    for (int i = 1; i < n; i++) {
        int key = v[i];  // Element to be inserted into the sorted part
        int j = i - 1;

        // Highlight the current key element
        drawArray(window, v, i, -1); 
        std::this_thread::sleep_for(std::chrono::milliseconds(500));

        // Move elements of v[0..i-1] that are greater than the key, to one position ahead
        while (j >= 0 && v[j] > key) {
            v[j + 1] = v[j];
            drawArray(window, v, j, j + 1);  // Highlight the current element being shifted
            std::this_thread::sleep_for(std::chrono::milliseconds(200));
            j = j - 1;
        }

        v[j + 1] = key; // Insert the key into its correct position
        drawArray(window, v, j + 1, -1);  // Highlight the final position of the key
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end - start;

    drawArray(window, v); // Draw the final sorted array

    // Prepare sorting information text
    sf::Text infoText;
    infoText.setFont(font);
    infoText.setCharacterSize(24);
    infoText.setFillColor(sf::Color::White);

    std::ostringstream infoStream;
    infoStream << "Insertion Sort Visualization\n";
    infoStream << "Time Complexity: O(n^2)\n";
    infoStream << "Elapsed Time: " << elapsed.count() << " seconds\n";
    infoStream << "Sorted Array: ";
    for (const int &num : v) {
        infoStream << num << " ";
    }
    infoStream << "\n\nPress Enter to return to the main menu...";

    infoText.setString(infoStream.str());
    infoText.setPosition(50, 50); // Adjust position as needed

    // Display the information and wait for the user to press Enter
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            } else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter) {
                return; // Exit to main menu
            }
        }

        window.clear();
        drawArray(window, v); // Draw the final sorted array
        window.draw(infoText); // Draw the information text
        window.display();
    }
}

void mergeSortVisualized(sf::RenderWindow &window, std::vector<int> &v) {
    int n = v.size();
    sf::Font font;

    // Load font for text rendering
    if (!font.loadFromFile("3.ttf")) {
        std::cerr << "Failed to load font!" << std::endl;
        return;
    }

    auto start = std::chrono::high_resolution_clock::now();

    // Merge Sort visualization
    mergeSortRecursive(window, v, 0, n - 1, font);

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end - start;

    // Draw the final sorted array
    drawArray(window, v); 

    // Prepare sorting information text
    sf::Text infoText;
    infoText.setFont(font);
    infoText.setCharacterSize(24);
    infoText.setFillColor(sf::Color::White);

    std::ostringstream infoStream;
    infoStream << "Merge Sort Visualization\n";
    infoStream << "Time Complexity: O(n log n)\n";
    infoStream << "Elapsed Time: " << elapsed.count() << " seconds\n";
    infoStream << "Sorted Array: ";
    for (const int &num : v) {
        infoStream << num << " ";
    }
    infoStream << "\n\nPress Enter to return to the main menu...";

    infoText.setString(infoStream.str());
    infoText.setPosition(50, 50); // Adjust position as needed

    // Display the information and wait for the user to press Enter
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            } else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter) {
                return; // Exit to main menu
            }
        }

        window.clear();
        drawArray(window, v); // Draw the final sorted array
        window.draw(infoText); // Draw the information text
        window.display();
    }
}

void mergeSortRecursive(sf::RenderWindow &window, std::vector<int> &v, int left, int right, sf::Font &font) {
    if (left < right) {
        int mid = left + (right - left) / 2; // Find the middle point

        // Recursively split and sort the two halves
        mergeSortRecursive(window, v, left, mid, font);
        mergeSortRecursive(window, v, mid + 1, right, font);

        // Merge the two halves
        merge(window, v, left, mid, right, font);
    }
}

void merge(sf::RenderWindow &window, std::vector<int> &v, int left, int mid, int right, sf::Font &font) {
    // Visualize the array being merged
    drawArray(window, v, left, right);
    std::this_thread::sleep_for(std::chrono::milliseconds(500));

    int n1 = mid - left + 1;
    int n2 = right - mid;

    // Create temporary arrays
    std::vector<int> leftArr(n1), rightArr(n2);

    // Copy data to temporary arrays
    for (int i = 0; i < n1; i++) {
        leftArr[i] = v[left + i];
    }
    for (int i = 0; i < n2; i++) {
        rightArr[i] = v[mid + 1 + i];
    }

    // Merge the temporary arrays back into the original array
    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (leftArr[i] <= rightArr[j]) {
            v[k] = leftArr[i];
            i++;
        } else {
            v[k] = rightArr[j];
            j++;
        }
        k++;
        drawArray(window, v, left, right); // Visualize after each merge step
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
    }

    // Copy remaining elements of leftArr[] if any
    while (i < n1) {
        v[k] = leftArr[i];
        i++;
        k++;
        drawArray(window, v, left, right); // Visualize after each merge step
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
    }

    // Copy remaining elements of rightArr[] if any
    while (j < n2) {
        v[k] = rightArr[j];
        j++;
        k++;
        drawArray(window, v, left, right); // Visualize after each merge step
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
    }
}

int partition(sf::RenderWindow &window, std::vector<int> &v, int low, int high) {
    int pivot = v[high];
    int i = (low - 1);

    for (int j = low; j <= high - 1; j++) {
        if (v[j] < pivot) {
            i++;
            std::swap(v[i], v[j]);
            drawArray(window, v, i, j);
            std::this_thread::sleep_for(std::chrono::milliseconds(200));
        }
    }
    std::swap(v[i + 1], v[high]);
    drawArray(window, v, i + 1, high);
    std::this_thread::sleep_for(std::chrono::milliseconds(200));
    return (i + 1);
}

void quickSortVisualizedRecursive(sf::RenderWindow &window, std::vector<int> &v, int low, int high) {
    if (low < high) {
        int pi = partition(window, v, low, high);

        quickSortVisualizedRecursive(window, v, low, pi - 1);
        quickSortVisualizedRecursive(window, v, pi + 1, high);
    }
}

void quickSortVisualized(sf::RenderWindow &window, std::vector<int> &v) {
    auto start = std::chrono::high_resolution_clock::now(); // Start timing the sort

    quickSortVisualizedRecursive(window, v, 0, v.size() - 1);

    auto end = std::chrono::high_resolution_clock::now(); // End timing the sort
    std::chrono::duration<double> elapsed = end - start;

    // Display the final sorted array and information text
    sf::Font font;
    if (!font.loadFromFile("3.ttf")) {
        std::cerr << "Failed to load font!" << std::endl;
        return;
    }

    drawArray(window, v); // Draw the final sorted array

    // Prepare sorting information text
    sf::Text infoText;
    infoText.setFont(font);
    infoText.setCharacterSize(24);
    infoText.setFillColor(sf::Color::White);

    std::ostringstream infoStream;
    infoStream << "Quick Sort Visualization\n";
    infoStream << "Time Complexity: O(n log n) average, O(n^2) worst\n";
    infoStream << "Elapsed Time: " << elapsed.count() << " seconds\n";
    infoStream << "Sorted Array: ";
    for (const int &num : v) {
        infoStream << num << " ";
    }
    infoStream << "\n\nPress Enter to return to the main menu...";

    infoText.setString(infoStream.str());
    infoText.setPosition(50, 50); // Adjust position as needed

    // Display the information and wait for the user to press Enter
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            } else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter) {
                return; // Exit to main menu
            }
        }

        window.clear();
        drawArray(window, v); // Draw the final sorted array
        window.draw(infoText); // Draw the information text
        window.display();
    }
}