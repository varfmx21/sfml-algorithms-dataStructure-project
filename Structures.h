// LUIS FERNANDO VALDERRABANO GARCIA A01644530

#pragma once
#include "Constants.h"

// ----------------------------------------- //
// ----------------- AVL  ----------------- //
// --------------------------------------- //

class AVLTree {
private:
    struct Node {
        int value;
        int height;
        Node* left;
        Node* right;
        sf::CircleShape shape;
        sf::Text valueText;
        sf::RectangleShape leftEdge;
        sf::RectangleShape rightEdge;
        sf::Text complexityText;
        sf::Text timingText;
        sf::Text exitText;

        Node(int val, const sf::Font& font) : 
            value(val), height(1), left(nullptr), right(nullptr) {
            shape.setRadius(25);
            shape.setFillColor(sf::Color::White);
            shape.setOutlineThickness(2);
            shape.setOutlineColor(sf::Color::White);

            valueText.setFont(font);
            valueText.setString(std::to_string(val));
            valueText.setCharacterSize(20);
            valueText.setFillColor(sf::Color::Black);

            // Initialize edges with proper thickness
            leftEdge.setSize(sf::Vector2f(50, 2));
            rightEdge.setSize(sf::Vector2f(50, 2));
            leftEdge.setFillColor(sf::Color::White);
            rightEdge.setFillColor(sf::Color::White);
            
            // Center origin for better rotation
            leftEdge.setOrigin(0, 1);
            rightEdge.setOrigin(0, 1);
        }
    };

    Node* root;
    sf::Font font;
    std::string message;
    bool showInputPrompt;
    std::string userInput;
    std::chrono::duration<double> lastOperationTime;  // Add this line


    // AVL Tree operations
    int getHeight(Node* node);
    int getBalance(Node* node);
    Node* rightRotate(Node* y);
    Node* leftRotate(Node* x);
    Node* insert(Node* node, int value);
    Node* deleteNode(Node* root, int value);
    Node* minValueNode(Node* node);
    
    // Visualization helpers
    void updatePositions(Node* node, float x, float y, float horizontalSpacing);
    void drawNode(sf::RenderWindow& window, Node* node);
    void animateRotation(sf::RenderWindow& window, Node* node, bool isLeftRotation);

public:
    AVLTree(sf::RenderWindow& window);
    void insertValue(int value);
    void deleteValue(int value);
    void draw(sf::RenderWindow& window);
    void handleInput(sf::Event& event, sf::RenderWindow& window);
};

// --------------------------------------------- //
// ----------------- DJIKSTRA  ----------------- //
// --------------------------------------------- //

// In Structures.h after AVLTree class

class Graph {
private:
    struct Node {
        int id;
        sf::Vector2f position;
        sf::CircleShape shape;
        sf::Text label;

        Node(int id, const sf::Vector2f& pos, const sf::Font& font) : id(id) {
            position = pos;
            shape.setRadius(20);
            shape.setPosition(pos);
            shape.setFillColor(sf::Color::White);
            shape.setOutlineThickness(2);
            shape.setOutlineColor(sf::Color::White);

            label.setFont(font);
            label.setString(std::to_string(id));
            label.setCharacterSize(18);
            label.setFillColor(sf::Color::Black);
            
            // Center the text in the node
            sf::FloatRect textRect = label.getLocalBounds();
            label.setOrigin(textRect.width/2.0f, textRect.height/2.0f);
            label.setPosition(pos.x + 20, pos.y + 20);
        }
    };

    struct Edge {
        int from, to;
        int weight;
        sf::Vertex line[2];
        sf::Text weightText;

        Edge(int f, int t, int w, const sf::Vector2f& pos1, const sf::Vector2f& pos2, const sf::Font& font)
            : from(f), to(t), weight(w) {
            line[0] = sf::Vertex(pos1, sf::Color::White);
            line[1] = sf::Vertex(pos2, sf::Color::White);
            
            weightText.setFont(font);
            weightText.setString(std::to_string(w));
            weightText.setCharacterSize(20);  // Change this value (default was 15)
            weightText.setFillColor(sf::Color::Yellow);
            
            // Center the weight text
            sf::FloatRect textRect = weightText.getLocalBounds();
            weightText.setOrigin(textRect.width/2.0f, textRect.height/2.0f);
            sf::Vector2f midpoint = (pos1 + pos2) / 2.0f;
            weightText.setPosition(midpoint);
        }
    };

    std::vector<Node> nodes;
    std::vector<Edge> edges;
    sf::Font font;
    int startNode;
    int endNode;
    std::vector<int> shortestPath;
    std::chrono::duration<double> executionTime;
    bool pathFound;
    int totalPathWeight;

public:
    Graph(sf::RenderWindow& window);
    void generateRandomGraph();
    void draw(sf::RenderWindow& window);
    void handleClick(sf::Vector2i mousePos);
    void runDijkstra();
    void reset();
};

// ------------------------------------------------ //
// ----------------- BFS AND DFS  ----------------- //
// ------------------------------------------------ //
class Maze {
public:
    Maze(int width, int height, int cellSize);
    void generateMaze();
    bool solveMaze(sf::RenderWindow& window);  // Declaración del método solveMaze
    bool solveMazeBFS(sf::RenderWindow& window);  // Método para resolver con BFS
    void draw(sf::RenderWindow& window);

private:
    enum Cell { WALL, PATH, VISITED, START, END, SOLUTION };

    struct Position {
        int x, y;

        Position() : x(0), y(0) {}  // Default constructor
        Position(int x, int y) : x(x), y(y) {}

        // Equality operator for Position to use it in unordered_map
        bool operator==(const Position& other) const {
            return x == other.x && y == other.y;
        }

        bool operator!=(const Position& other) const {
            return !(*this == other);
        }
        
    };

    // Hash function for Position to be used in unordered_map
    struct PositionHash {
        std::size_t operator()(const Position& p) const {
            // Combine the hash values of x and y
            return std::hash<int>()(p.x) ^ std::hash<int>()(p.y);
        }
    };

    int width, height, cellSize;
    std::vector<std::vector<Cell>> grid;
    Position start, end;

    void generateDFS(Position pos);
    bool solveDFS(Position pos, sf::RenderWindow& window);  // Declaración de la función solveDFS
    std::vector<Position> getNeighbors(const Position& pos);
};

void visualizeMazeAlgorithm(const std::string& algorithm);