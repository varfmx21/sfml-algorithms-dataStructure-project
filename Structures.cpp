// LUIS FERNANDO VALDERRABANO GARCIA A01644530

#include "Structures.h"

// --------------------------------------------- //
// ----------------- DJIKSTRA  ----------------- //
// --------------------------------------------- //

void generateDefaultGraph(std::vector<Node>& nodes, std::vector<Edge>& edges, 
                        const sf::Font& font, int nodeCount) {
    nodes.clear();
    edges.clear();

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> xDist(100.0f, 700.0f);
    std::uniform_real_distribution<float> yDist(100.0f, 500.0f);
    std::uniform_real_distribution<float> weightDist(1.0f, 10.0f);

    // Generate nodes
    for (int i = 0; i < nodeCount; ++i) {
        nodes.emplace_back(i, sf::Vector2f(xDist(gen), yDist(gen)), font);
    }

    // Generate edges (ensuring connected graph)
    for (int i = 0; i < nodeCount - 1; ++i) {
        float weight = weightDist(gen);
        edges.emplace_back(i, i + 1, weight, 
                          nodes[i].position, nodes[i + 1].position, font);
    }

    // Add some random edges
    int extraEdges = nodeCount * 2;
    for (int i = 0; i < extraEdges; ++i) {
        int from = gen() % nodeCount;
        int to = gen() % nodeCount;
        if (from != to) {
            float weight = weightDist(gen);
            edges.emplace_back(from, to, weight, 
                             nodes[from].position, nodes[to].position, font);
        }
    }
}

void runDijkstra(sf::RenderWindow& window, std::vector<Node>& nodes, 
                 std::vector<Edge>& edges, int start, int end) {
    int n = nodes.size();
    std::vector<float> dist(n, std::numeric_limits<float>::infinity());
    std::vector<int> prev(n, -1);
    dist[start] = 0;

    auto startTime = std::chrono::high_resolution_clock::now();

    std::priority_queue<std::pair<float, int>, 
                       std::vector<std::pair<float, int>>, 
                       std::greater<>> pq;
    pq.push({0, start});

    while (!pq.empty()) {
        int u = pq.top().second;
        pq.pop();

        if (u == end) break;

        // Visualize current node being processed
        nodes[u].shape.setFillColor(sf::Color::Blue);
        drawGraph(window, nodes, edges, sf::Text());
        window.display();
        sf::sleep(sf::milliseconds(300));

        for (const Edge& edge : edges) {
            if (edge.from == u || edge.to == u) {
                int v = (edge.from == u) ? edge.to : edge.from;
                float alt = dist[u] + edge.weight;
                
                if (alt < dist[v]) {
                    dist[v] = alt;
                    prev[v] = u;
                    pq.push({alt, v});
                }
            }
        }
    }

    auto endTime = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = endTime - startTime;

    // Highlight shortest path
    int current = end;
    while (current != -1) {
        nodes[current].shape.setFillColor(sf::Color::Yellow);
        current = prev[current];
        
        drawGraph(window, nodes, edges, sf::Text());
        window.display();
        sf::sleep(sf::milliseconds(200));
    }

    // Display result
    sf::Text resultText;
    resultText.setFont(*nodes[0].label.getFont());
    resultText.setCharacterSize(20);
    resultText.setFillColor(sf::Color::White);
    resultText.setString("Path found! Time: " + 
                        std::to_string(elapsed.count()) + 
                        " seconds\nPress ESC to exit");
    resultText.setPosition(10, 10);

    bool running = true;
    while (running && window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed || 
               (event.type == sf::Event::KeyPressed && 
                event.key.code == sf::Keyboard::Escape)) {
                running = false;
            }
        }

        window.clear(sf::Color::Black);
        drawGraph(window, nodes, edges, resultText);
        window.display();
    }
}

void drawGraph(sf::RenderWindow& window, const std::vector<Node>& nodes, 
              const std::vector<Edge>& edges, const sf::Text& infoText) {
    window.clear(sf::Color::Black);

    // Draw edges
    for (const Edge& edge : edges) {
        window.draw(edge.line, 2, sf::Lines);
        window.draw(edge.weightText);
    }

    // Draw nodes
    for (const Node& node : nodes) {
        window.draw(node.shape);
        window.draw(node.label);
    }

    window.draw(infoText);
}

// ------------------------------------------------ //
// ----------------- BFS AND DFS  ----------------- //
// ------------------------------------------------ //

Maze::Maze(int width, int height, int cellSize)
    : width(width), height(height), cellSize(cellSize), start(1, 1), end(width - 2, height - 2) {
    grid.resize(width, std::vector<Cell>(height, WALL));
    generateMaze();
    grid[start.x][start.y] = START;
    grid[end.x][end.y] = END;
}

void Maze::generateMaze() {
    for (int x = 0; x < width; x++) {
        for (int y = 0; y < height; y++) {
            grid[x][y] = WALL;
        }
    }
    generateDFS(start);
    grid[start.x][start.y] = START;
    grid[end.x][end.y] = END;
}

void Maze::generateDFS(Position pos) {
    grid[pos.x][pos.y] = PATH;
    std::vector<Position> directions = { {0, -2}, {0, 2}, {-2, 0}, {2, 0} };
    std::shuffle(directions.begin(), directions.end(), std::mt19937(std::random_device()()));

    for (const Position& direction : directions) {
        int nx = pos.x + direction.x;
        int ny = pos.y + direction.y;

        if (nx > 0 && ny > 0 && nx < width - 1 && ny < height - 1 && grid[nx][ny] == WALL) {
            grid[nx][ny] = PATH;
            grid[pos.x + direction.x / 2][pos.y + direction.y / 2] = PATH;
            generateDFS({ nx, ny });
        }
    }
}

bool Maze::solveMaze(sf::RenderWindow& window) {
    return solveDFS(start, window);
}

bool Maze::solveMazeBFS(sf::RenderWindow& window) {
    std::queue<Position> q;
    std::unordered_map<Position, Position, PositionHash> predecessors;  // Track predecessors for path retracing
    q.push(start);
    grid[start.x][start.y] = VISITED;

    while (!q.empty()) {
        Position pos = q.front();
        q.pop();

        if (pos.x == end.x && pos.y == end.y) {
            // Mark the end cell as part of the solution
            grid[pos.x][pos.y] = SOLUTION;

            // Retrace the path from end to start
            Position current = pos;
            while (current != start) {
                grid[current.x][current.y] = SOLUTION;
                current = predecessors[current];  // Move to the predecessor
                draw(window);
                window.display();
                sf::sleep(sf::milliseconds(50));  // Pause to visualize solution path
            }
            return true;
        }

        // Visualize each step
        draw(window);
        window.display();
        sf::sleep(sf::milliseconds(200));  // Pause to show progress

        std::vector<Position> neighbors = { {0, -1}, {0, 1}, {-1, 0}, {1, 0} };
        for (const Position& dir : neighbors) {
            int nx = pos.x + dir.x;
            int ny = pos.y + dir.y;

            if (nx >= 0 && ny >= 0 && nx < width && ny < height && (grid[nx][ny] == PATH || grid[nx][ny] == END)) {
                q.push({nx, ny});
                grid[nx][ny] = VISITED;  // Mark as visited
                predecessors[{nx, ny}] = pos;  // Set predecessor for retracing
            }
        }
    }
    return false;
}

bool Maze::solveDFS(Position pos, sf::RenderWindow& window) {
    if (pos.x == end.x && pos.y == end.y) {
        grid[pos.x][pos.y] = SOLUTION;
        return true;
    }

    grid[pos.x][pos.y] = VISITED;
    draw(window);
    window.display();
    sf::sleep(sf::milliseconds(200));

    std::vector<Position> neighbors = { {0, -1}, {0, 1}, {-1, 0}, {1, 0} };
    for (const Position& dir : neighbors) {
        int nx = pos.x + dir.x;
        int ny = pos.y + dir.y;

        if (grid[nx][ny] == PATH || grid[nx][ny] == END) {
            if (solveDFS({ nx, ny }, window)) {
                grid[pos.x][pos.y] = SOLUTION;
                draw(window);
                window.display();
                sf::sleep(sf::milliseconds(50));
                return true;
            }
        }
    }

    grid[pos.x][pos.y] = PATH;
    return false;
}

void Maze::draw(sf::RenderWindow& window) {
    float startX = (window.getSize().x - width * cellSize) / 2.0f;
    float startY = (window.getSize().y - height * cellSize) / 2.0f + 50; // Adding 50px offset for the title

    for (int x = 0; x < width; x++) {
        for (int y = 0; y < height; y++) {
            sf::RectangleShape cell(sf::Vector2f(cellSize, cellSize));
            cell.setPosition(startX + x * cellSize, startY + y * cellSize);

            switch (grid[x][y]) {
                case WALL: cell.setFillColor(sf::Color::Black); break;
                case PATH: cell.setFillColor(sf::Color::White); break;
                case VISITED: cell.setFillColor(sf::Color::Blue); break;
                case START: cell.setFillColor(sf::Color::Green); break;
                case END: cell.setFillColor(sf::Color::Red); break;
                case SOLUTION: cell.setFillColor(sf::Color::Yellow); break;
            }

            window.draw(cell);
        }
    }
}