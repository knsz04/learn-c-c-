#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTICES 100

// 邻接表节点
typedef struct Node {
    int vertex;
    struct Node *next;
} Node;

// 图结构
typedef struct Graph {
    int numVertices;
    Node *adjLists[MAX_VERTICES];
    int visited[MAX_VERTICES];
} Graph;

// 创建新节点
Node *createNode(int v) {
    Node *newNode = (Node *)malloc(sizeof(Node));
    if (newNode == NULL) {
        perror("malloc");
        exit(EXIT_FAILURE);
    }
    newNode->vertex = v;
    newNode->next = NULL;
    return newNode;
}

// 初始化图
Graph *createGraph(int vertices) {
    Graph *graph = (Graph *)malloc(sizeof(Graph));
    if (graph == NULL) {
        perror("malloc");
        exit(EXIT_FAILURE);
    }
    graph->numVertices = vertices;
    for (int i = 0; i < vertices; i++) {
        graph->adjLists[i] = NULL;
        graph->visited[i] = 0;
    }
    return graph;
}

// 添加边
void addEdge(Graph *graph, int src, int dest) {
    // src -> dest
    Node *newNode = createNode(dest);
    newNode->next = graph->adjLists[src];
    graph->adjLists[src] = newNode;

    // 无向图的话再添加 dest -> src
    newNode = createNode(src);
    newNode->next = graph->adjLists[dest];
    graph->adjLists[dest] = newNode;
}

// 队列结构
typedef struct Queue {
    int items[MAX_VERTICES];
    int front;
    int rear;
} Queue;

Queue *createQueue() {
    Queue *q = (Queue *)malloc(sizeof(Queue));
    if (q == NULL) {
        perror("malloc");
        exit(EXIT_FAILURE);
    }
    q->front = -1;
    q->rear = -1;
    return q;
}

int isEmpty(Queue *q) {
    return q->rear == -1;
}

void enqueue(Queue *q, int value) {
    if (q->rear == MAX_VERTICES - 1) {
        return;
    }
    if (q->front == -1) {
        q->front = 0;
    }
    q->rear++;
    q->items[q->rear] = value;
}

int dequeue(Queue *q) {
    int item;
    if (isEmpty(q)) {
        return -1;
    }
    item = q->items[q->front];
    q->front++;
    if (q->front > q->rear) {
        q->front = q->rear = -1;
    }
    return item;
}

void bfs(Graph *graph, int startVertex) {
    Queue *q = createQueue();
    graph->visited[startVertex] = 1;
    enqueue(q, startVertex);

    while (!isEmpty(q)) {
        int currentVertex = dequeue(q);
        printf("%d ", currentVertex);

        Node *temp = graph->adjLists[currentVertex];
        while (temp) {
            int adjVertex = temp->vertex;
            if (!graph->visited[adjVertex]) {
                graph->visited[adjVertex] = 1;
                enqueue(q, adjVertex);
            }
            temp = temp->next;
        }
    }
    printf("\n");
    free(q);
}

int main() {
    int vertices = 6;
    Graph *graph = createGraph(vertices);

    addEdge(graph, 0, 1);
    addEdge(graph, 0, 2);
    addEdge(graph, 1, 3);
    addEdge(graph, 1, 4);
    addEdge(graph, 2, 4);
    addEdge(graph, 3, 5);
    addEdge(graph, 4, 5);

    printf("广度优先遍历结果: ");
    bfs(graph, 0);

    // 释放邻接表
    for (int i = 0; i < vertices; i++) {
        Node *temp = graph->adjLists[i];
        while (temp) {
            Node *next = temp->next;
            free(temp);
            temp = next;
        }
    }
    free(graph);
    return 0;
}
