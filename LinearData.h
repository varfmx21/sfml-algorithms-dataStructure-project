#pragma once
#include "Constants.h"

// ----------------------------------------------------------- //
// -------------------------- STACK -------------------------- //
// ----------------------------------------------------------- //

class Stack {
private:
    std::vector<int> stack;             // The stack of integers
    sf::Font font;                      // Font for text rendering
    int blockWidth = 200;               // Width of each block
    int blockHeight = 50;               // Height of each block
    std::string userInput;
    bool showInputPrompt;

public:
    Stack(sf::RenderWindow& window);    // Constructor
    void push(int value);               // Push method
    void pop();                         // Pop method
    void draw(sf::RenderWindow& window); // Draw method
    void handleInput(sf::Event& event, sf::RenderWindow& window);
};

// ----------------------------------------------------------- //
// -------------------------- QUEUE -------------------------- //
// ----------------------------------------------------------- //

class Queue {
private:
    std::vector<int> queue;  // The internal container for storing elements
    sf::Font font;  // Font for rendering text
    bool showInputPrompt = false;  // Input prompt visibility flag
    std::string userInput = "";  // User input string
    const int blockWidth = 50;  // Width of each queue block
    const int blockHeight = 200;  // Height of each queue block

public:
    Queue(sf::RenderWindow& window);
    void enqueue(int value);
    void dequeue();
    void draw(sf::RenderWindow& window);
    void handleInput(sf::Event& event, sf::RenderWindow& window);
};

// ----------------------------------------------------------------- //
// -------------------------- LINKED LIST -------------------------- //
// ----------------------------------------------------------------- //

class LinkedList {
private:
    struct Node {
        int value;
        Node* next;
        sf::RectangleShape shape;
        sf::Text valueText;
        sf::RectangleShape arrow;

        Node(int val, const sf::Font& font);
    };

    Node* head;
    sf::Font font;
    sf::Text instructionText;
    std::string message;
    bool showInputPrompt = false;
    std::string userInput;
    void updatePositions();
    void animateInsertion(Node* newNode, Node* prevNode);
    void animateDelete(Node* nodeToDelete);

public:
    LinkedList(sf::RenderWindow& window);
    void insert(int value);
    void deleteValue(int value);
    bool search(int value);
    void draw(sf::RenderWindow& window);
    void handleInput(sf::Event& event, sf::RenderWindow& window);
};