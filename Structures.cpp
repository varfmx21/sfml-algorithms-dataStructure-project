// LUIS FERNANDO VALDERRABANO GARCIA A01644530

#include "Structures.h"

// ----------------------------------------- //
// ----------------- AVL  ----------------- //
// --------------------------------------- //

AVLTree::AVLTree(sf::RenderWindow& window) 
    : root(nullptr)
    , showInputPrompt(false)
    , lastOperationTime(std::chrono::duration<double>::zero()) {
    if (!font.loadFromFile("3.ttf")) {
        std::cerr << "Error loading font!" << std::endl;
    }
    message = "Presiona P para insertar, O para eliminar";
}

int AVLTree::getHeight(Node* node) {
    return node ? node->height : 0;
}

int AVLTree::getBalance(Node* node) {
    return node ? getHeight(node->left) - getHeight(node->right) : 0;
}

AVLTree::Node* AVLTree::rightRotate(Node* y) {
    if (!y || !y->left) return y;

    Node* x = y->left;
    Node* T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = std::max(getHeight(y->left), getHeight(y->right)) + 1;
    x->height = std::max(getHeight(x->left), getHeight(x->right)) + 1;

    return x;
}

AVLTree::Node* AVLTree::leftRotate(Node* x) {
    if (!x || !x->right) return x;

    Node* y = x->right;
    Node* T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = std::max(getHeight(x->left), getHeight(x->right)) + 1;
    y->height = std::max(getHeight(y->left), getHeight(y->right)) + 1;

    return y;
}

AVLTree::Node* AVLTree::insert(Node* node, int value) {
    if (!node) {
        return new Node(value, font);
    }

    if (value < node->value) {
        node->left = insert(node->left, value);
    } else if (value > node->value) {
        node->right = insert(node->right, value);
    } else {
        return node;
    }

    node->height = 1 + std::max(getHeight(node->left), getHeight(node->right));
    int balance = getBalance(node);

    // Left Left Case
    if (balance > 1 && value < node->left->value) {
        return rightRotate(node);
    }

    // Right Right Case
    if (balance < -1 && value > node->right->value) {
        return leftRotate(node);
    }

    // Left Right Case
    if (balance > 1 && value > node->left->value) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    // Right Left Case
    if (balance < -1 && value < node->right->value) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node;
}

void AVLTree::insertValue(int value) {
    auto start = std::chrono::high_resolution_clock::now();
    
    root = insert(root, value);
    
    auto end = std::chrono::high_resolution_clock::now();
    lastOperationTime = end - start;
    
    message = "Insertado " + std::to_string(value);
}

// Modify the updatePositions method in AVLTree class:
void AVLTree::updatePositions(Node* node, float x, float y, float horizontalSpacing) {
    if (!node) return;

    // Position the node circle
    node->shape.setPosition(x - node->shape.getRadius(), y);
    
    // Center the text in the node
    float textBounds = node->valueText.getLocalBounds().width;
    node->valueText.setPosition(
        x - textBounds/2,
        y + node->shape.getRadius() - node->valueText.getCharacterSize()/2
    );

    if (node->left) {
        float childX = x - horizontalSpacing;
        float childY = y + 80;
        
        // Calculate edge start and end points
        float startX = x;
        float startY = y + node->shape.getRadius() * 2;
        float endX = childX;
        float endY = childY;
        
        // Calculate edge length
        float dx = endX - startX;
        float dy = endY - startY;
        float length = std::sqrt(dx * dx + dy * dy);
        
        // Update edge properties
        node->leftEdge.setSize(sf::Vector2f(length, 2));
        node->leftEdge.setPosition(startX, startY);
        float angle = std::atan2(dy, dx) * 180 / M_PI;
        node->leftEdge.setRotation(angle);
        
        updatePositions(node->left, childX, childY, horizontalSpacing/2);
    }

    if (node->right) {
        float childX = x + horizontalSpacing;
        float childY = y + 80;
        
        // Calculate edge start and end points
        float startX = x + node->shape.getRadius() * 2;
        float startY = y + node->shape.getRadius() * 2;
        float endX = childX + node->shape.getRadius() * 2;
        float endY = childY;
        
        // Calculate edge length
        float dx = endX - startX;
        float dy = endY - startY;
        float length = std::sqrt(dx * dx + dy * dy);
        
        // Update edge properties
        node->rightEdge.setSize(sf::Vector2f(length, 2));
        node->rightEdge.setPosition(startX, startY);
        float angle = std::atan2(dy, dx) * 180 / M_PI;
        node->rightEdge.setRotation(angle);
        
        updatePositions(node->right, childX, childY, horizontalSpacing/2);
    }
}

void AVLTree::draw(sf::RenderWindow& window) {
    // Draw instruction text
    sf::Text instructionText(message, font, mainSize);
    instructionText.setFillColor(sf::Color::White);
    instructionText.setPosition(10, 10);
    window.draw(instructionText);

    if (showInputPrompt) {
        sf::Text inputText(userInput, font, mainSize);
        inputText.setFillColor(sf::Color::White);
        inputText.setPosition(10, 40);
        window.draw(inputText);
    }

    // Draw complexity information (right side)
    sf::Text complexityText;
    complexityText.setFont(font);
    complexityText.setCharacterSize(mainSize);
    complexityText.setFillColor(sf::Color::White);
    complexityText.setPosition(window.getSize().x - 300, 10);
    complexityText.setString("Complejidad de tiempo:\n"
                           "Insercion: O(log n)\n"
                           "Eliminacion: O(log n)\n"
                           "Busqueda: O(log n)");
    window.draw(complexityText);

    // Draw timing information
    sf::Text timingText;
    timingText.setFont(font);
    timingText.setCharacterSize(mainSize);
    timingText.setFillColor(sf::Color::White);
    timingText.setPosition(window.getSize().x - 300, 210);
    timingText.setString("Ultima operacion:\n" + 
                        std::to_string(lastOperationTime.count()) + 
                        " segundos");
    window.draw(timingText);

    // Draw exit instruction
    sf::Text exitText;
    exitText.setFont(font);
    exitText.setCharacterSize(mainSize);
    exitText.setFillColor(sf::Color::White);
    exitText.setPosition(window.getSize().x - 300, 160);
    exitText.setString("Presiona ESC para salir");
    window.draw(exitText);

    // Update and draw tree
    if (root) {
        updatePositions(root, window.getSize().x/2, 100, 300);
        drawNode(window, root);
    }
}

void AVLTree::drawNode(sf::RenderWindow& window, Node* node) {
    if (!node) return;

    // Draw edges first
    if (node->left) {
        window.draw(node->leftEdge);
        drawNode(window, node->left);
    }
    if (node->right) {
        window.draw(node->rightEdge);
        drawNode(window, node->right);
    }

    // Draw node
    window.draw(node->shape);
    window.draw(node->valueText);
}

void AVLTree::handleInput(sf::Event& event, sf::RenderWindow& window) {
    if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::P) {
            showInputPrompt = true;
            message = "Inserta el valor a insertar:";
            userInput = "";
        }
        else if (event.key.code == sf::Keyboard::O) {
            showInputPrompt = true;
            message = "Inserta el valor a eliminar:";
            userInput = "";
        }
    }

    if (event.type == sf::Event::TextEntered && showInputPrompt) {
        if (event.text.unicode == 8 && !userInput.empty()) {  // Backspace
            userInput.pop_back();
        }
        else if (event.text.unicode == 13) {  // Enter
            if (!userInput.empty()) {
                try {
                    int value = std::stoi(userInput);
                    if (message.find("insertar") != std::string::npos) {
                        insertValue(value);
                    }
                    else if (message.find("eliminar") != std::string::npos) {
                        deleteValue(value);
                    }
                }
                catch (const std::exception&) {
                    message = "Input invalido!";
                }
                userInput = "";
                showInputPrompt = false;
            }
        }
        else if (event.text.unicode >= '0' && event.text.unicode <= '9') {
            userInput += static_cast<char>(event.text.unicode);
        }
    }
}

void AVLTree::deleteValue(int value) {
    auto start = std::chrono::high_resolution_clock::now();
    
    root = deleteNode(root, value);
    
    auto end = std::chrono::high_resolution_clock::now();
    lastOperationTime = end - start;
    
    message = "Eliminado " + std::to_string(value);
}

AVLTree::Node* AVLTree::minValueNode(Node* node) {
    Node* current = node;
    while (current && current->left != nullptr)
        current = current->left;
    return current;
}

AVLTree::Node* AVLTree::deleteNode(Node* root, int value) {
    if (!root)
        return root;

    if (value < root->value)
        root->left = deleteNode(root->left, value);
    else if (value > root->value)
        root->right = deleteNode(root->right, value);
    else {
        // Node with only one child or no child
        if (!root->left || !root->right) {
            Node* temp = root->left ? root->left : root->right;
            if (!temp) { // No child case
                temp = root;
                root = nullptr;
            } else // One child case
                *root = *temp; // Copy the contents of the non-empty child
            delete temp;
        } else {
            // Node with two children
            Node* temp = minValueNode(root->right);
            root->value = temp->value;
            root->valueText.setString(std::to_string(temp->value));
            root->right = deleteNode(root->right, temp->value);
        }
    }

    if (!root)
        return root;

    // Update height
    root->height = 1 + std::max(getHeight(root->left), getHeight(root->right));

    // Check balance
    int balance = getBalance(root);

    // Left Left Case
    if (balance > 1 && getBalance(root->left) >= 0)
        return rightRotate(root);

    // Left Right Case
    if (balance > 1 && getBalance(root->left) < 0) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    // Right Right Case
    if (balance < -1 && getBalance(root->right) <= 0)
        return leftRotate(root);

    // Right Left Case
    if (balance < -1 && getBalance(root->right) > 0) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

// --------------------------------------------- //
// ----------------- DJIKSTRA  ----------------- //
// --------------------------------------------- //

Graph::Graph(sf::RenderWindow& window) 
    : startNode(-1)
    , endNode(-1)
    , executionTime(std::chrono::duration<double>::zero())
    , pathFound(false)
    , totalPathWeight(0) {  // Add this line
    if (!font.loadFromFile("3.ttf")) {
        std::cerr << "Error loading font!" << std::endl;
    }
    generateRandomGraph();
}

void Graph::generateRandomGraph() {
    nodes.clear();
    edges.clear();
    
    // Center the graph in the window
    const int NUM_NODES = 10;
    const float RADIUS = 200.0f;  // Reduced radius for better centering
    const float CENTER_X = 800.0f;  // Middle of 1600px window
    const float CENTER_Y = 400.0f;  // Middle of 800px window

    for (int i = 0; i < NUM_NODES; ++i) {
        float angle = (2 * M_PI * i) / NUM_NODES;
        float x = CENTER_X + RADIUS * cos(angle);
        float y = CENTER_Y + RADIUS * sin(angle);
        nodes.emplace_back(i, sf::Vector2f(x, y), font);
    }

    // Generate random edges
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> weightDist(1, 50);
    
    // Ensure connected graph
    for (int i = 0; i < NUM_NODES - 1; ++i) {
        int weight = weightDist(gen);
        edges.emplace_back(i, i + 1, weight, 
            sf::Vector2f(nodes[i].position.x + 20, nodes[i].position.y + 20),
            sf::Vector2f(nodes[i + 1].position.x + 20, nodes[i + 1].position.y + 20),
            font);
    }

    // Add some random edges
    for (int i = 0; i < NUM_NODES * 2; ++i) {
        int from = gen() % NUM_NODES;
        int to = gen() % NUM_NODES;
        if (from != to) {
            int weight = weightDist(gen);
            edges.emplace_back(from, to, weight,
                sf::Vector2f(nodes[from].position.x + 20, nodes[from].position.y + 20),
                sf::Vector2f(nodes[to].position.x + 20, nodes[to].position.y + 20),
                font);
        }
    }
}

void Graph::draw(sf::RenderWindow& window) {
    // Draw edges
    for (const auto& edge : edges) {
        window.draw(edge.line, 2, sf::Lines);
        window.draw(edge.weightText);
    }

    // Draw nodes
    for (const auto& node : nodes) {
        window.draw(node.shape);
        window.draw(node.label);
    }

    // Highlight path if exists
    if (!shortestPath.empty()) {
        for (size_t i = 0; i < shortestPath.size() - 1; ++i) {
            sf::Vertex pathLine[] = {
                sf::Vertex(sf::Vector2f(nodes[shortestPath[i]].position.x + 20,
                                      nodes[shortestPath[i]].position.y + 20),
                          sf::Color::Green),
                sf::Vertex(sf::Vector2f(nodes[shortestPath[i + 1]].position.x + 20,
                                      nodes[shortestPath[i + 1]].position.y + 20),
                          sf::Color::Green)
            };
            window.draw(pathLine, 2, sf::Lines);
        }
    }

    // Draw algorithm information on the right side
    sf::Text infoText;
    infoText.setFont(font);
    infoText.setCharacterSize(mainSize);
    infoText.setFillColor(sf::Color::White);
    infoText.setPosition(window.getSize().x - 400, 10);

    std::stringstream ss;
    ss << "Dijkstra's Algorithm\n\n"
       << "Time Complexity: O(V + E log V)\n"
       << "Space Complexity: O(V)\n\n";
    
    if (startNode != -1 && endNode != -1) {
        ss << "Start Node: " << startNode << "\n"
           << "End Node: " << endNode << "\n\n";
        
        if (!shortestPath.empty()) {
            ss << "Path: ";
            for (size_t i = 0; i < shortestPath.size(); ++i) {
                ss << shortestPath[i];
                if (i < shortestPath.size() - 1) {
                    ss << " -> ";
                }
            }
            ss << "\n\n";
            ss << "Total Path Weight: " << totalPathWeight << "\n\n";  // Add this line
        }

        ss << "Execution Time: \n"
           << std::fixed << std::setprecision(6)
           << executionTime.count() << " seconds\n\n";
    }
    
    infoText.setString(ss.str());
    window.draw(infoText);

    // Draw exit instruction below algorithm info
    sf::Text exitText("Press ESC to exit", font, 30);
    exitText.setFillColor(sf::Color::White);
    exitText.setPosition(window.getSize().x - 400, 300);
    window.draw(exitText);

    // Draw instructions if no nodes selected
    if (startNode == -1) {
        sf::Text instructionText("Click to select start node", font, mainSize);
        instructionText.setFillColor(sf::Color::Yellow);
        instructionText.setPosition(10, 10);
        window.draw(instructionText);
    } else if (endNode == -1) {
        sf::Text instructionText("Click to select end node", font, mainSize);
        instructionText.setFillColor(sf::Color::Yellow);
        instructionText.setPosition(10, 10);
        window.draw(instructionText);
    }
}

void Graph::handleClick(sf::Vector2i mousePos) {
    for (size_t i = 0; i < nodes.size(); ++i) {
        if (nodes[i].shape.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
            if (startNode == -1) {
                startNode = i;
                nodes[i].shape.setFillColor(sf::Color::Green);
            } else if (endNode == -1 && i != startNode) {
                endNode = i;
                nodes[i].shape.setFillColor(sf::Color::Red);
                runDijkstra();
            }
            break;
        }
    }
}

void Graph::runDijkstra() {
    if (startNode == -1 || endNode == -1) return;

    auto startTime = std::chrono::high_resolution_clock::now();

    std::vector<int> dist(nodes.size(), INT_MAX);
    std::vector<int> prev(nodes.size(), -1);
    std::vector<bool> visited(nodes.size(), false);
    
    dist[startNode] = 0;
    totalPathWeight = 0;  // Reset total weight
    
    for (size_t i = 0; i < nodes.size(); i++) {
        int u = -1;
        for (size_t j = 0; j < nodes.size(); j++) {
            if (!visited[j] && (u == -1 || dist[j] < dist[u])) {
                u = j;
            }
        }
        
        if (u == -1 || dist[u] == INT_MAX) break;
        
        visited[u] = true;
        
        for (const Edge& edge : edges) {
            if (edge.from == u) {
                int v = edge.to;
                if (!visited[v] && dist[u] + edge.weight < dist[v]) {
                    dist[v] = dist[u] + edge.weight;
                    prev[v] = u;
                }
            }
        }
    }
    
    // Reconstruct path
    shortestPath.clear();
    int current = endNode;
    while (current != -1) {
        shortestPath.push_back(current);
        current = prev[current];
    }
    std::reverse(shortestPath.begin(), shortestPath.end());

    if (!shortestPath.empty()) {
        for (size_t i = 0; i < shortestPath.size() - 1; ++i) {
            int from = shortestPath[i];
            int to = shortestPath[i + 1];
            // Find the edge weight between these nodes
            for (const Edge& edge : edges) {
                if ((edge.from == from && edge.to == to) || 
                    (edge.from == to && edge.to == from)) {
                    totalPathWeight += edge.weight;
                    break;
                }
            }
        }
    }

    auto endTime = std::chrono::high_resolution_clock::now();
    executionTime = endTime - startTime;
    pathFound = !shortestPath.empty();
}

void Graph::reset() {
    startNode = -1;
    endNode = -1;
    shortestPath.clear();
    executionTime = std::chrono::duration<double>::zero();
    pathFound = false;
    totalPathWeight = 0;  // Add this line
    for (auto& node : nodes) {
        node.shape.setFillColor(sf::Color::White);
    }
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
                sf::sleep(sf::milliseconds(PATH_TRACE_DELAY));  // Pause to visualize solution path
            }
            return true;
        }

        // Visualize each step
        draw(window);
        window.display();
        sf::sleep(sf::milliseconds(FAST_VISUALIZATION_DELAY));  // Pause to show progress

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
    sf::sleep(sf::milliseconds(FAST_VISUALIZATION_DELAY));

    std::vector<Position> neighbors = { {0, -1}, {0, 1}, {-1, 0}, {1, 0} };
    for (const Position& dir : neighbors) {
        int nx = pos.x + dir.x;
        int ny = pos.y + dir.y;

        if (grid[nx][ny] == PATH || grid[nx][ny] == END) {
            if (solveDFS({ nx, ny }, window)) {
                grid[pos.x][pos.y] = SOLUTION;
                draw(window);
                window.display();
                sf::sleep(sf::milliseconds(PATH_TRACE_DELAY));
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

void visualizeMazeAlgorithm(const std::string& algorithm) {
    sf::RenderWindow mazeWindow(sf::VideoMode(1600, 800), "Maze Visualization - " + algorithm);
    
    Maze maze(21, 21, 20);
    maze.draw(mazeWindow);
    mazeWindow.display();
    
    sf::Font font;
    if (!font.loadFromFile("3.ttf")) {
        std::cerr << "Error loading font!" << std::endl;
        return;
    }
    
    // Main instructions message (left side)
    sf::Text message("Press SPACE to start " + algorithm + " visualization\nPress ESC to exit", font, mainSize);
    message.setFillColor(sf::Color::White);
    message.setPosition(10, 10);

    // Status message (right side)
    sf::Text statusMessage("", font, mainSize);
    statusMessage.setFillColor(sf::Color::White);
    statusMessage.setPosition(mazeWindow.getSize().x - 400, 10);

    bool started = false;
    while (mazeWindow.isOpen()) {
        sf::Event event;
        while (mazeWindow.pollEvent(event)) {
            if (event.type == sf::Event::Closed || 
               (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)) {
                mazeWindow.close();
            }
            
            if (!started && event.type == sf::Event::KeyPressed && 
                event.key.code == sf::Keyboard::Space) {
                started = true;
                
                // Start timing
                auto startTime = std::chrono::high_resolution_clock::now();
                bool solved = false;

                // Run the selected algorithm
                if (algorithm == "BFS") {
                    solved = maze.solveMazeBFS(mazeWindow);
                } else if (algorithm == "DFS") {
                    solved = maze.solveMaze(mazeWindow);
                }

                // End timing
                auto endTime = std::chrono::high_resolution_clock::now();
                auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime);

                // Update messages
                std::stringstream ss;
                ss << algorithm << " Results:\n\n"
                   << "Status: " << (solved ? "Solved!" : "Could not solve") << "\n\n"
                   << "Execution Time:\n"
                   << duration.count() << " milliseconds\n\n"
                   << "Time complexity: O(V+E)\n"
                   << "Press ESC to exit";

                statusMessage.setString(ss.str());
                message.setString(solved ? "Maze solved!" : "Maze could not be solved!");
            }
        }

        mazeWindow.clear(sf::Color::Black);
        maze.draw(mazeWindow);
        mazeWindow.draw(message);
        mazeWindow.draw(statusMessage);
        mazeWindow.display();
    }
}