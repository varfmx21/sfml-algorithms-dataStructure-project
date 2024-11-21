# Proyecto de Algoritmos y Estructuras de Datos con Visualización en SFML

## Objetivo
Crear un programa en C++ que implemente diversos algoritmos y estructuras de datos, utilizando SFML para representar gráficamente un menú o las operaciones. El programa debe incluir algoritmos de búsqueda, ordenamiento, estructuras de datos lineales (pilas, colas, listas enlazadas) y no lineales (árboles binarios AVL, grafos con DFS y BFS). Este enfoque permitirá al usuario entender el funcionamiento interno de cada algoritmo y estructura de datos de manera visual e interactiva.

## Descripción

### 1. Algoritmos de Búsqueda (Ponderación: 15%)
#### Secuencial (Linear Search)
El algoritmo recorre el arreglo elemento por elemento.

- **Visualización:** Cada elemento visitado se resalta, cambiando su color temporalmente. Si encuentra el valor buscado, el elemento coincide y se resalta permanentemente, mientras que el resto vuelve a su estado inicial.
- **Interacción:** El usuario puede introducir el valor que desea buscar. La animación se desarrolla en tiempo real para mostrar el progreso.

#### Binaria (Binary Search)
Utilizado en arreglos previamente ordenados, el algoritmo divide el arreglo en mitades para buscar el elemento.

- **Visualización:** Resalta los límites del rango actual, así como el elemento medio comparado en cada iteración. El rango se reduce a la mitad hasta que encuentra el valor o termina la búsqueda.
- **Interacción:** El usuario puede elegir el valor a buscar. La animación muestra cómo se reduce el rango progresivamente.

### 2. Algoritmos de Ordenamiento
#### Bubble Sort
Intercambia elementos adyacentes si están en orden incorrecto, en múltiples iteraciones.

- **Visualización:** Resalta los elementos comparados en cada paso. Los intercambios se animan para que el usuario observe el progreso.

#### Selection Sort
Encuentra el valor mínimo (o máximo) en cada iteración y lo coloca en su posición correcta.

- **Visualización:** Resalta el mínimo encontrado en cada paso. Anima el intercambio del mínimo con el elemento en la posición actual.

#### Insertion Sort
Ordena el arreglo incrementando un subarreglo ordenado elemento por elemento.

- **Visualización:** Resalta el elemento que se va a insertar. Muestra cómo se desplazan los elementos mayores para hacer espacio.

#### Merge Sort
Divide el arreglo en mitades recursivamente y combina las partes ordenadas.

- **Visualización:** Los subarreglos se resaltan al dividirse. La combinación de elementos se muestra en orden ascendente.

#### Quick Sort
Usa un pivote para dividir el arreglo en elementos menores y mayores, ordenando recursivamente.

- **Visualización:** Resalta el pivote en cada partición. Muestra cómo se reorganizan los elementos en torno al pivote.

### 3. Estructuras Lineales
#### Pilas (Stacks)
Implementa operaciones de apilado (push) y desapilado (pop).

- **Visualización:** Cada elemento se agrega como un bloque en una pila visible. La eliminación muestra cómo el bloque superior desaparece. Ideal para simular una torre o pila de discos.

#### Filas (Queues)
Implementa inserciones (enqueue) al final y eliminaciones (dequeue) al frente.

- **Visualización:** Los elementos se desplazan visualmente al ser agregados o eliminados. Flechas indican las posiciones de frente y final de la cola.

#### Listas enlazadas (Linked Lists)
Representa nodos conectados mediante punteros para operaciones como inserción, eliminación y búsqueda.

- **Visualización:** Cada nodo se muestra como un cuadro conectado con flechas al siguiente. Las inserciones y eliminaciones animan los enlaces y nodos afectados.

### 4. Estructuras No Lineales
#### Árboles Binarios AVL
Árboles auto-balanceados que ajustan su estructura tras operaciones de inserción y eliminación.

#### Algoritmo de Dijkstra
El algoritmo de Dijkstra encuentra el camino más corto desde un nodo fuente a todos los demás nodos en un grafo ponderado (sin pesos negativos).

#### Grafos
Representación de un conjunto de nodos conectados por aristas.

##### DFS (Depth-First Search)
Visualiza la exploración del grafo desde un nodo inicial, profundizando antes de retroceder.

- **Visualización:** Resalta los nodos y aristas en el orden de exploración.

##### BFS (Breadth-First Search)
Visualiza la exploración nivel por nivel desde un nodo inicial.

- **Visualización:** Los nodos y aristas visitados se resaltan en el orden correspondiente.
- **Interacción:** El usuario selecciona el nodo inicial para iniciar DFS o BFS. Se muestra el progreso.