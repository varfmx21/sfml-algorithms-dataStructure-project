#include "LinearData.h"

// ----------------------------------------------------------- //
// -------------------------- STACK -------------------------- //
// ----------------------------------------------------------- //

Stack::Stack(sf::RenderWindow& window) {
    if (!font.loadFromFile("3.ttf")) {
        throw std::runtime_error("Unable to load font.");
    }
    userInput = "";  // Initialize the user input string
    showInputPrompt = false;
}

// Push method
void Stack::push(int value) {
    stack.push_back(value);
}

// Pop method
void Stack::pop() {
    if (!stack.empty()) {
        stack.pop_back();
    }
}

// Draw method to render stack and input prompt
void Stack::draw(sf::RenderWindow& window) {
    // Define custom positions for the prompt and input on the left side
    int promptX = 50;  // Position from the left side (adjust as needed)
    int promptY = 50; // Set the vertical position for the prompt (can be adjusted)

    int inputX = 50;   // Position from the left side (same as promptX)
    int inputY = promptY + 100;  // Position the input text just below the prompt

    // Draw the default instruction text
    sf::Text instructionText("Presiona O para pop y presiona P para push", font, mainSize);
    instructionText.setFillColor(sf::Color::White);
    instructionText.setPosition(50, 50);  // Positioned at the top-left of the window
    window.draw(instructionText);

    sf::Text instructionText1("Presiona Esc para salir", font, 30);
    instructionText1.setFillColor(sf::Color::White);

    // Calculate the position for the text to align it to the right
    sf::FloatRect textBounds = instructionText1.getLocalBounds();
    sf::Vector2u windowSize = window.getSize();
    float rightMargin = 10; // Small padding from the right edge
    float xPosition = windowSize.x - textBounds.width - rightMargin - 50;

    instructionText1.setPosition(xPosition, promptY);
    window.draw(instructionText1);

    sf::Text instructionText2("Last In, First Out (LIFO)\npop O(1)\npush O(1)", font, mainSize);
    instructionText2.setFillColor(sf::Color::White);
    instructionText2.setPosition(xPosition, promptY + 50);  // Positioned at the top-left of the window
    window.draw(instructionText2);

    // Display the input prompt on the left side of the window
    if (showInputPrompt) {
        sf::Text promptText("Dame el numero para push:", font, mainSize);
        promptText.setFillColor(sf::Color::White);
        promptText.setPosition(promptX, promptY + 50);  // Use fixed left position
        window.draw(promptText);

        // Display the user's input on the left side of the window
        sf::Text inputText(userInput, font, mainSize);
        inputText.setFillColor(sf::Color::White);
        inputText.setPosition(inputX, inputY);  // Use fixed left position
        window.draw(inputText);
    }

    // Draw the stack elements
    int x = window.getSize().x / 2 - (blockWidth / 2);  // Center the stack horizontally
    int y = window.getSize().y / 2 + 50;  // Start drawing the stack slightly below the prompt

    for (size_t i = 0; i < stack.size(); ++i) {
        // Create a rectangle for each stack element
        sf::RectangleShape block(sf::Vector2f(blockWidth, blockHeight));
        block.setPosition(x, y - i * (blockHeight + 10)); // Adjust y position for each block
        block.setFillColor(mainColor);

        // Draw the block
        window.draw(block);

        // Create and display text for each stack element
        sf::Text valueText;
        valueText.setFont(font);
        valueText.setString(std::to_string(stack[i]));
        valueText.setCharacterSize(mainSize);
        valueText.setFillColor(sf::Color::White);

        // Center the text in the middle of the block
        sf::FloatRect textRect = valueText.getLocalBounds();
        valueText.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f); // Center the text
        valueText.setPosition(x + blockWidth / 2, y - i * (blockHeight + 10) + blockHeight / 2); // Set position to center

        // Draw the text
        window.draw(valueText);
    }
}

// Handle input for pushing and popping
void Stack::handleInput(sf::Event& event, sf::RenderWindow& window) {
    if (event.type == sf::Event::KeyPressed) {
        // If "P" is pressed, activate the input prompt
        if (event.key.code == sf::Keyboard::P) {
            showInputPrompt = true;
        }
        // If "O" is pressed, pop from the stack
        if (event.key.code == sf::Keyboard::O) {
            pop();
        }
    }

    if (event.type == sf::Event::TextEntered) {
        if (showInputPrompt) {
            // Handle character input for the number (and ensure it’s printable)
            if (event.text.unicode == 8 && !userInput.empty()) {
                // Handle Backspace (Unicode 8)
                userInput.pop_back();  // Remove the last character
            } else if (event.text.unicode == 13) {
                // Handle Enter (Unicode 13)
                try {
                    int value = std::stoi(userInput);  // Try to convert input to integer
                    push(value);  // Push to the stack
                    userInput = "";  // Clear the input after pushing
                    showInputPrompt = false;  // Hide the prompt after input
                } catch (const std::exception&) {
                    // Handle invalid input (non-integer value)
                    userInput = "Input Invalido!";
                }
            } else if (event.text.unicode < 128) {
                // Append the character to the input string unless the pressed key is "P"
                // Prevent "P" from appearing in the input
                if (event.text.unicode != 'P') {
                    userInput += static_cast<char>(event.text.unicode);
                }
            }
        }
    }
}

// ----------------------------------------------------------- //
// -------------------------- QUEUE -------------------------- //
// ----------------------------------------------------------- //

Queue::Queue(sf::RenderWindow& window) {
        if (!font.loadFromFile("3.ttf")) {
            throw std::runtime_error("Unable to load font.");
        }
    }

void Queue::enqueue(int value) {
    queue.push_back(value);  // Add to the back
}

void Queue::dequeue() {
    if (!queue.empty()) {
        queue.erase(queue.begin());  // Remove from the front
    }
}

void Queue::draw(sf::RenderWindow& window) {
    int leftMargin = 50;       // Left margin for text and input
    int yOffset = 50;          // Vertical offset for elements
    int centerY = window.getSize().y / 2;

    // Display instruction text on the left side
    sf::Text instructionText("Presiona P para enqueue, O para dequeue", font, mainSize);
    instructionText.setFillColor(sf::Color::White);
    instructionText.setPosition(leftMargin, yOffset);
    window.draw(instructionText);

    // Display input prompt and user input on the left side
    if (showInputPrompt) {
        sf::Text promptText("Ingresa un numero para enqueue:", font, mainSize);
        promptText.setFillColor(sf::Color::White);
        promptText.setPosition(leftMargin, yOffset + 40);
        window.draw(promptText);

        sf::Text inputText(userInput, font, mainSize);
        inputText.setFillColor(sf::Color::White);
        inputText.setPosition(leftMargin, yOffset + 80);
        window.draw(inputText);
    }

    // Draw queue elements
    int xStart = 200;  // Horizontal start position for the queue
    int y = centerY;   // Vertical center for the blocks

    for (size_t i = 0; i < queue.size(); ++i) {
        sf::RectangleShape block(sf::Vector2f(blockWidth, blockHeight));
        block.setPosition(xStart + i * (blockWidth + 10), y);
        block.setFillColor(mainColor);

        // Draw block
        window.draw(block);

        // Draw text inside the block, centered
        sf::Text valueText;
        valueText.setFont(font);
        valueText.setString(std::to_string(queue[i]));
        valueText.setCharacterSize(mainSize);
        valueText.setFillColor(sf::Color::White);

        float textX = xStart + i * (blockWidth + 10) + blockWidth / 2 - valueText.getLocalBounds().width / 2;
        float textY = y + blockHeight / 2 - valueText.getLocalBounds().height / 2;
        valueText.setPosition(textX, textY);

        window.draw(valueText);
    }

    // Display "Press Esc to exit the program" on the right side
    sf::Text exitText("Press Esc to exit the program", font, 30);
    exitText.setFillColor(sf::Color::White);

    // Calculate position on the right side
    float rightMargin = 50;  // Margin from the right edge
    float xPosition = window.getSize().x - exitText.getLocalBounds().width - rightMargin;
    float yPosition = yOffset;  // Align with the top offset

    exitText.setPosition(xPosition, yPosition);
    window.draw(exitText);

    sf::Text infoText("First In, First Out (FIFO)\nEnqueue O(1)\nDequeue O(1)", font, mainSize  );
    infoText.setFillColor(sf::Color::White);
    infoText.setPosition(xPosition, yPosition + 50);
    window.draw(infoText);
}

void Queue::handleInput(sf::Event& event, sf::RenderWindow& window) {
    if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::P) {
            showInputPrompt = true;  // Activate input prompt
        } else if (event.key.code == sf::Keyboard::O) {
            dequeue();  // Dequeue an element
        }
    }

    if (event.type == sf::Event::TextEntered) {
        if (showInputPrompt) {
            if (event.text.unicode == 8 && !userInput.empty()) {  // Backspace
                userInput.pop_back();
            } else if (event.text.unicode == 13) {  // Enter key
                try {
                    int value = std::stoi(userInput);
                    enqueue(value);  // Enqueue the entered number
                    userInput = "";  // Clear input
                    showInputPrompt = false;  // Hide prompt
                } catch (const std::exception&) {
                    userInput = "Input Invalido!";
                }
            } else if (event.text.unicode < 128 && event.text.unicode != 'p') {
                userInput += static_cast<char>(event.text.unicode);
            }
        }
    }
}

// ----------------------------------------------------------------- //
// -------------------------- LINKED LIST -------------------------- //
// ----------------------------------------------------------------- //

LinkedList::Node::Node(int val, const sf::Font& font) : value(val), next(nullptr) {
    // Setup node visual representation
    shape.setSize(sf::Vector2f(60, 40));
    shape.setFillColor(sf::Color::White);
    shape.setOutlineThickness(2);
    shape.setOutlineColor(sf::Color::White);

    // Setup value text with center alignment
    valueText.setFont(font);
    valueText.setCharacterSize(mainSize);
    valueText.setFillColor(sf::Color::Black);
    valueText.setString(std::to_string(value));
    
    // Center the text origin
    sf::FloatRect textRect = valueText.getLocalBounds();
    valueText.setOrigin(textRect.left + textRect.width/2.0f,
                       textRect.top + textRect.height/2.0f);

    // Setup arrow
    arrow.setSize(sf::Vector2f(40, 2));
    arrow.setFillColor(sf::Color::White);
}

LinkedList::LinkedList(sf::RenderWindow& window) : head(nullptr) {
    if (!font.loadFromFile("3.ttf")) {
        std::cerr << "Error loading font!" << std::endl;
    }

    instructionText.setFont(font);
    instructionText.setCharacterSize(mainSize);
    instructionText.setFillColor(sf::Color::White);
    instructionText.setPosition(10, 10);
    instructionText.setString("Press P to insert, O to delete, I to search");
}

void LinkedList::updatePositions() {
    float x = 100;
    float y = 300;
    Node* current = head;

    while (current) {
        current->shape.setPosition(x, y);
        
        // Center the text in the node
        current->valueText.setPosition(
            x + 30,  // Half of shape width (60/2)
            y + 20   // Half of shape height (40/2)
        );

        if (current->next) {
            current->arrow.setPosition(x + 60, y + 20);
            current->arrow.setRotation(0);
        }

        x += 120;
        current = current->next;
    }
}

void LinkedList::insert(int value) {
    Node* newNode = new Node(value, font);
    
    if (!head) {
        head = newNode;
    } else {
        Node* current = head;
        while (current->next) {
            current = current->next;
        }
        current->next = newNode;
        animateInsertion(newNode, current);
    }
    
    updatePositions();
}

void LinkedList::deleteValue(int value) {
    Node* current = head;
    Node* previous = nullptr;
    bool found = false;

    while (current) {
        if (current->value == value) {
            found = true;
            break;
        }
        previous = current;
        current = current->next;
    }

    if (found) {
        if (previous) {
            previous->next = current->next;
        } else {
            head = current->next;
        }
        animateDelete(current);
        delete current;
        updatePositions();
        message = "Value deleted successfully!";
    } else {
        message = "Value not found!";
    }
}

bool LinkedList::search(int value) {
    Node* current = head;
    while (current) {
        current->shape.setFillColor(sf::Color::Blue);
        sf::sleep(sf::milliseconds(250));
        
        if (current->value == value) {
            current->shape.setFillColor(sf::Color::Green);
            message = "Value found!";
            return true;
        }
        
        current->shape.setFillColor(sf::Color::White);
        current = current->next;
    }
    
    message = "Value not found!";
    return false;
}

void LinkedList::animateInsertion(Node* newNode, Node* prevNode) {
    // Animation for insertion
    sf::Clock clock;
    float duration = 0.25f;
    
    while (clock.getElapsedTime().asSeconds() < duration) {
        float progress = clock.getElapsedTime().asSeconds() / duration;
        // Animate node appearing and arrow extending
        newNode->shape.setFillColor(sf::Color(255, 255, 255, static_cast<sf::Uint8>(255 * progress)));
        if (prevNode) {
            prevNode->arrow.setSize(sf::Vector2f(40 * progress, 2));
        }
    }
}

void LinkedList::animateDelete(Node* nodeToDelete) {
    // Animation for deletion
    sf::Clock clock;
    float duration = 0.25f;
    
    while (clock.getElapsedTime().asSeconds() < duration) {
        float progress = clock.getElapsedTime().asSeconds() / duration;
        // Fade out the node being deleted
        nodeToDelete->shape.setFillColor(sf::Color(255, 255, 255, static_cast<sf::Uint8>(255 * (1 - progress))));
        nodeToDelete->arrow.setFillColor(sf::Color(255, 255, 255, static_cast<sf::Uint8>(255 * (1 - progress))));
    }
}

void LinkedList::draw(sf::RenderWindow& window) {
    int leftMargin = 50;
    int yOffset = 50;

    // Draw instruction text
    sf::Text instructionText("Presiona P para Insercion, O para Eliminacion, I para Busqueda", font, mainSize);
    instructionText.setFillColor(sf::Color::White);
    instructionText.setPosition(leftMargin, yOffset);
    window.draw(instructionText);

    sf::Text instructionText1("Presiona Esc para salir", font, 30);
    instructionText1.setFillColor(sf::Color::White);

    // Calculate the position for the text to align it to the right
    sf::FloatRect textBounds = instructionText1.getLocalBounds();
    sf::Vector2u windowSize = window.getSize();
    float rightMargin = 10; // Small padding from the right edge
    float xPosition = windowSize.x - textBounds.width - rightMargin - 50;

    instructionText1.setPosition(xPosition, yOffset);
    window.draw(instructionText1);

    sf::Text instructionText2("Insercion O(n)\nEmliminacion O(n)\nBusqueda O(n)", font, mainSize);
    instructionText2.setFillColor(sf::Color::White);
    instructionText2.setPosition(xPosition, yOffset+50);
    window.draw(instructionText2);

    

    // Draw input prompt and user input
    if (showInputPrompt) {
        sf::Text promptText(message, font, mainSize);
        promptText.setFillColor(sf::Color::White);
        promptText.setPosition(leftMargin, yOffset + 40);
        window.draw(promptText);

        sf::Text inputText(userInput, font, mainSize);
        inputText.setFillColor(sf::Color::White);
        inputText.setPosition(leftMargin, yOffset + 80);
        window.draw(inputText);
    }

    // Draw linked list nodes
    Node* current = head;
    float x = 100;
    float y = 300;

    while (current) {
        window.draw(current->shape);
        window.draw(current->valueText);
        if (current->next) {
            window.draw(current->arrow);
        }
        current = current->next;
    }
}

void LinkedList::handleInput(sf::Event& event, sf::RenderWindow& window) {
    if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::P) {
            showInputPrompt = true;
            message = "Ingresa el valor a Insertar:";
            userInput = "";
        } 
        else if (event.key.code == sf::Keyboard::O) {
            showInputPrompt = true;
            message = "Ingresa el valor a Eliminar:";
            userInput = "";
        }
        else if (event.key.code == sf::Keyboard::I) {
            showInputPrompt = true;
            message = "Ingresa el valor a Buscar:";
            userInput = "";
        }
    }

    if (event.type == sf::Event::TextEntered && showInputPrompt) {
        if (event.text.unicode == 8 && !userInput.empty()) {  // Backspace
            userInput.pop_back();
        } 
        else if (event.text.unicode == 13) {  // Enter key
            try {
                int value = std::stoi(userInput);
                
                if (message.find("Insertar") != std::string::npos) {
                    insert(value);
                }
                else if (message.find("Eliminar") != std::string::npos) {
                    deleteValue(value);
                }
                else if (message.find("Buscar") != std::string::npos) {
                    search(value);
                }

                userInput = "";
                showInputPrompt = false;
            } 
            catch (const std::exception&) {
                userInput = "Invalid Input!";
            }
        } 
        else if (event.text.unicode < 128 && 
                 event.text.unicode != 'p' && 
                 event.text.unicode != 'o' && 
                 event.text.unicode != 'i') {
            userInput += static_cast<char>(event.text.unicode);
        }
    }
}