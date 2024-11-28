// LUIS FERNANDO VALDERRABANO GARCIA A01644530

#pragma once
#include "Constants.h"

// --------------------------------------------- //
// ----------------- DJIKSTRA  ----------------- //
// --------------------------------------------- //

struct Node {
    int id;
    sf::Vector2f position;
    sf::CircleShape shape;
    sf::Text label;

    Node(int id, const sf::Vector2f& pos, const sf::Font& font) 
        : id(id), position(pos) {
        shape.setRadius(20);
        shape.setPosition(pos);
        shape.setFillColor(sf::Color::White);
        shape.setOutlineThickness(2);
        shape.setOutlineColor(sf::Color::White);

        label.setFont(font);
        label.setString(std::to_string(id));
        label.setCharacterSize(18);
        label.setFillColor(sf::Color::Black);
        label.setPosition(pos.x + 15, pos.y + 10);
    }
};

struct Edge {
    int from, to;
    float weight;
    sf::Vertex line[2];
    sf::Text weightText;

    Edge(int f, int t, float w, const sf::Vector2f& pos1, const sf::Vector2f& pos2, const sf::Font& font)
        : from(f), to(t), weight(w) {
        line[0] = sf::Vertex(pos1, sf::Color::White);
        line[1] = sf::Vertex(pos2, sf::Color::White);

        weightText.setFont(font);
        weightText.setString(std::to_string(static_cast<int>(weight)));
        weightText.setCharacterSize(15);
        weightText.setFillColor(sf::Color::Yellow);
        
        // Position weight text at middle of edge
        sf::Vector2f midpoint = (pos1 + pos2) / 2.0f;
        weightText.setPosition(midpoint);
    }
};

void generateDefaultGraph(std::vector<Node>& nodes, std::vector<Edge>& edges, 
                        const sf::Font& font, int nodeCount = 8);
void runDijkstra(sf::RenderWindow& window, std::vector<Node>& nodes, 
                 std::vector<Edge>& edges, int start, int end);
void drawGraph(sf::RenderWindow& window, const std::vector<Node>& nodes, 
              const std::vector<Edge>& edges, const sf::Text& infoText);

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