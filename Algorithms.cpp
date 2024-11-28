// LUIS FERNANDO VALDERRABANO GARCIA A01644530

#include "Constants.h"
#include "Algorithms.h"

// -------------------------------------------------------------- //
// ----------------- ALGORITMOS DE ORDENAMIENTO ----------------- //
// -------------------------------------------------------------- //

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
            bar.setFillColor(mainColor);
        } else {
            bar.setFillColor(sf::Color::White);
        }

        window.draw(bar);
    }

    window.display();
}

void drawArray2(sf::RenderWindow &window, const std::vector<int> &v, int left, int right, int mid, const std::string& info, const std::string& elapsedTime, int foundIndex, int target) {
    window.clear();  // Clear the window

    float barWidth = window.getSize().x / v.size();  // Width of each bar

    // Draw each element as a bar
    for (size_t i = 0; i < v.size(); ++i) {
        sf::RectangleShape bar(sf::Vector2f(barWidth, v[i]));
        bar.setPosition(i * barWidth, window.getSize().y - v[i]);
        bar.setFillColor(sf::Color::White);

        // Highlight the current left, right, and middle positions
        if (i == left) {
            bar.setFillColor(sf::Color::Red);  // Highlight the left bound in red
        } else if (i == right) {
            bar.setFillColor(sf::Color::Green);  // Highlight the right bound in green
        } else if (i == mid) {
            bar.setFillColor(sf::Color::Blue);  // Highlight the middle element in blue
        }

        window.draw(bar);
    }

    // Create and display information about the search
    sf::Font font;
    if (!font.loadFromFile("3.ttf")) { // Ensure you have the correct font file path
        // Handle font loading error
        std::cerr << "Error loading font!" << std::endl;
        return;
    }

    sf::Text text;
    text.setFont(font);
    text.setCharacterSize(mainSize);
    text.setFillColor(sf::Color::White);
    text.setPosition(10, 10);  // Position of the information text

    // Update the information text with current search state
    std::stringstream ss;
    ss << "Algorithm: Binary Search\n";
    ss << "Time Complexity: O(log n)\n";
    ss << "Sorted Array: ";
    for (const auto& el : v) {
        ss << el << " ";
    }
    ss << "\nElapsed Time: " << elapsedTime << " seconds\n";
    ss << "Target: " << target <<'\n';

    if (foundIndex != -1) {
        ss << "Target Found at Index: " << foundIndex << "\n";
    } else {
        ss << "Target Not Found\n";
    }

    ss << "\n\n" << info;  // Display current search info

    text.setString(ss.str());

    window.draw(text);  // Display the information

    window.display();  // Display the updated window
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
    infoText.setCharacterSize(mainSize);
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
    infoText.setCharacterSize(mainSize);
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
    infoText.setCharacterSize(mainSize);
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
    infoText.setCharacterSize(mainSize);
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
    infoText.setCharacterSize(mainSize);
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

// ---------------------------------------------------------- //
// ----------------- ALGORITMOS DE BUSQUEDA ----------------- //
// ---------------------------------------------------------- //

void linearSearchVisualized(sf::RenderWindow &window, std::vector<int> &v, int target) {
    auto start = std::chrono::high_resolution_clock::now(); // Start timing the search

    for (int i = 0; i < v.size(); i++) {
        drawArray(window, v, i);  // Highlight the current element
        std::this_thread::sleep_for(std::chrono::milliseconds(300)); // Wait to simulate searching

        if (v[i] == target) {
            // If the target is found, highlight it in green
            drawArray(window, v, i);
            break; // Exit loop once target is found
        }
    }

    auto end = std::chrono::high_resolution_clock::now(); // End timing the search
    std::chrono::duration<double> elapsed = end - start;

    // Display the final search result and information text
    sf::Font font;
    if (!font.loadFromFile("3.ttf")) {
        std::cerr << "Failed to load font!" << std::endl;
        return;
    }

    // Prepare sorting information text
    sf::Text infoText;
    infoText.setFont(font);
    infoText.setCharacterSize(mainSize);
    infoText.setFillColor(sf::Color::White);

    std::ostringstream infoStream;
    infoStream << "Linear Search Visualization\n";
    infoStream << "Target Value: " << target << "\n";
    infoStream << "Time Complexity: O(n)\n";
    infoStream << "Elapsed Time: " << elapsed.count() << " seconds\n";

    bool targetFound = false;
    for (int i = 0; i < v.size(); i++) {
        if (v[i] == target) {
            infoStream << "Found at Index: " << i << "\n";
            targetFound = true;
            break;
        }
    }
    if (!targetFound) {
        infoStream << "Target Not Found\n";
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
        drawArray(window, v); // Draw the final array (target highlighted or not)
        window.draw(infoText); // Draw the information text
        window.display();
    }
}

int partition2(std::vector<int> &vec, int low, int high) {

    // Selecting last element as the pivot
    int pivot = vec[high];

    // Index of elemment just before the last element
    // It is used for swapping
    int i = (low - 1);

    for (int j = low; j <= high - 1; j++) {

        // If current element is smaller than or
        // equal to pivot
        if (vec[j] <= pivot) {
            i++;
            std::swap(vec[i], vec[j]);
        }
    }

    // Put pivot to its position
    std::swap(vec[i + 1], vec[high]);

    // Return the point of partition
    return (i + 1);
}

void quickSort(std::vector<int> &vec, int low, int high) {

    // Base case: This part will be executed till the starting
    // index low is lesser than the ending index high
    if (low < high) {

        // pi is Partitioning Index, arr[p] is now at
        // right place
        int pi = partition2(vec, low, high);

        // Separately sort elements before and after the
        // Partition Index pi
        quickSort(vec, low, pi - 1);
        quickSort(vec, pi + 1, high);
    }
}

int binarySearchVisualized(sf::RenderWindow &window, std::vector<int> &v, int target) {
    int n = v.size();

    // Sort the vector
    quickSort(v, 0, n - 1);

    int left = 0;
    int right = v.size() - 1;

    auto start = std::chrono::high_resolution_clock::now(); // Start timing the search

    while (left <= right) {
        int mid = left + (right - left) / 2;  // Calculate middle index

        // Check for user pressing Enter to stop the visualization
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
                return -1; // Exit if the window is closed
            } else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter) {
                // Exit visualization when Enter is pressed
                return -1;
            }
        }

        // Determine if we need to adjust the search bounds based on comparison
        std::string info;
        if (v[mid] == target) {
            info = "Target found!";
            auto end = std::chrono::high_resolution_clock::now(); // End timing when target is found
            std::chrono::duration<double> elapsed = end - start;
            std::string elapsedTime = std::to_string(elapsed.count());

            // Display the final information with elapsed time and index found
            drawArray2(window, v, left, right, mid, info, elapsedTime, mid, target);  // Draw array with search info
            std::this_thread::sleep_for(std::chrono::milliseconds(1000));  // Pause for effect

            // Wait for the user to press Enter to exit the function
            while (true) {
                sf::Event eventEnd;
                while (window.pollEvent(eventEnd)) {
                    if (eventEnd.type == sf::Event::Closed) {
                        window.close();
                        return -1;  // Exit if the window is closed
                    } else if (eventEnd.type == sf::Event::KeyPressed && eventEnd.key.code == sf::Keyboard::Enter) {
                        // Exit the loop and the function when Enter is pressed
                        return mid;
                    }
                }
            }
        } else if (v[mid] < target) {
            info = "Searching right half";
            left = mid + 1;  // Search in the right half
        } else {
            info = "Searching left half";
            right = mid - 1;  // Search in the left half
        }

        // Visualization: Highlight left, right, and middle
        auto end = std::chrono::high_resolution_clock::now(); // End timing for each step
        std::chrono::duration<double> elapsed = end - start;
        std::string elapsedTime = std::to_string(elapsed.count());

        drawArray2(window, v, left, right, mid, info, elapsedTime, -1, target);
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));  // Pause to visualize the current step
    }

    // If the target is not found, show the final information
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end - start;
    std::string elapsedTime = std::to_string(elapsed.count());
    drawArray2(window, v, left, right, -1, "Target not found", elapsedTime, -1, target);

    // Wait for the user to press Enter to exit the function
    while (true) {
        sf::Event eventEnd;
        while (window.pollEvent(eventEnd)) {
            if (eventEnd.type == sf::Event::Closed) {
                window.close();
                return -1;  // Exit if the window is closed
            } else if (eventEnd.type == sf::Event::KeyPressed && eventEnd.key.code == sf::Keyboard::Enter) {
                // Exit the loop and the function when Enter is pressed
                return -1;
            }
        }
    }
}