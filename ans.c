#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTICES 100

// Structure for a node in the adjacency list
struct Node {
    int data;
    struct Node* next;
};

// Structure for the graph
struct Graph {
    int numVertices;
    struct Node* adjList[MAX_VERTICES];
    int visited[MAX_VERTICES];
};

// Function to create a node
struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

// Function to create a graph
struct Graph* createGraph(int vertices) {
    struct Graph* graph = (struct Graph*)malloc(sizeof(struct Graph));
    graph->numVertices = vertices;

    for (int i = 0; i < vertices; ++i) {
        graph->adjList[i] = NULL;
        graph->visited[i] = 0;
    }

    return graph;
}

// Function to add an edge to an undirected graph
void addEdge(struct Graph* graph, int src, int dest) {
    // Add edge from source to destination
    struct Node* newNode = createNode(dest);
    newNode->next = graph->adjList[src];
    graph->adjList[src] = newNode;

    // Add edge from destination to source
    newNode = createNode(src);
    newNode->next = graph->adjList[dest];
    graph->adjList[dest] = newNode;
}

// Function for Breadth-First Search (BFS)
void BFS(struct Graph* graph, int startVertex) {
    struct Node* queue[MAX_VERTICES];
    int front = 0, rear = 0;
    graph->visited[startVertex] = 1;
    queue[rear] = graph->adjList[startVertex];
    rear++;

    printf("Breadth First Search starting from vertex %d: ", startVertex);

    while (front < rear) {
        struct Node* currentNode = queue[front];
        printf("%d ", currentNode->data);
        front++;

        while (currentNode != NULL) {
            int adjVertex = currentNode->data;

            if (graph->visited[adjVertex] == 0) {
                queue[rear] = graph->adjList[adjVertex];
                rear++;
                graph->visited[adjVertex] = 1;
            }
            currentNode = currentNode->next;
        }
    }
    printf("\n");
}

// Function for Depth-First Search (DFS)
void DFS(struct Graph* graph, int startVertex) {
    graph->visited[startVertex] = 1;
    printf("%d ", startVertex);

    struct Node* currentNode = graph->adjList[startVertex];
    while (currentNode != NULL) {
        int adjVertex = currentNode->data;
        if (!graph->visited[adjVertex]) {
            DFS(graph, adjVertex);
        }
        currentNode = currentNode->next;
    }
}

int main() {
    struct Graph* graph = createGraph(5);

    addEdge(graph, 0, 1);
    addEdge(graph, 0, 2);
    addEdge(graph, 1, 3);
    addEdge(graph, 1, 4);

    // Perform BFS starting from vertex 0
    BFS(graph, 0);

    // Reset visited array for DFS
    for (int i = 0; i < graph->numVertices; ++i) {
        graph->visited[i] = 0;
    }

    // Perform DFS starting from vertex 0
    printf("Depth First Search starting from vertex 0: ");
    DFS(graph, 0);
    printf("\n");

    return 0;
}
