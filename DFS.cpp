/*
    Boar Daniel-Ioan
    Grupa 30223

    In aceasta tema am implementat algoritmul DFS, folosindu-ma de un algoritm care tine minte prin ce nod am trecut, colorandu-l.
    Am implementat crearea unei liste de adiacenta, am creat vectorul de parinti si apoi am facut un pretty print pentru a vedea care sunt arborii DFS.
    Toate aceste lucruri apar in consola in timpul executarii.
*/

#include <iostream>

using namespace std;

#define MAX_ROWS 100
#define MAX_COLS 100

typedef struct {
    int rows;
    int cols;
    int mat[MAX_ROWS][MAX_COLS];
}Grid;

typedef struct {
    int row;
    int col;
}Point;

enum {
    COLOR_WHITE = 0,
    COLOR_GRAY,
    COLOR_BLACK
};

typedef struct _Node {
    Point position;
    int adjSize;
    struct _Node** adj;
    int varf; //key

    int color;
    int dist;
    int f;
    struct _Node* parent;
}Node;

typedef struct {
    int nrNodes;
    Node** v; // lista 
}Graph;


Node* create(int x) {
    Node* q = (Node*)malloc(sizeof(Node));
    q->varf = x;
    q->adjSize = 0;
    q->parent = NULL;
    return q;
}

Graph* createG(int x) {
    Graph* G = (Graph*)malloc(sizeof(Graph));
    G->nrNodes = x;
    G->v = (Node**)malloc(x * sizeof(Node*));
    Node* u = (Node*)malloc(sizeof(Node));
    for (int i = 0; i < x; i++)
        G->v[i] = create(i); 
    for (int i = 0; i < x; i++) 
        G->v[i]->adj = (Node**)malloc(x * sizeof(Node*));
    return G;
}

void add(Graph* G, int src, int dest) {
    G->v[src]->adj[G->v[src]->adjSize] = G->v[dest];
    G->v[src]->adjSize++;
}

void DFS_VISIT(Graph* G, Node* u, int& time) {
    time++;
    u->dist = time;
    u->color = COLOR_GRAY;
    for (int i = 0; i < u->adjSize; i++) {
        Node* v = u->adj[i];
        if (v->color == COLOR_WHITE) {
            v->parent = u;
            DFS_VISIT(G, v, time);
        }
    }
    u->color = COLOR_BLACK;
    time++;
    u->f = time;
}

void DFS(Graph* G) {
    for (int i = 0; i < G->nrNodes; i++) {
        Node* u = G->v[i];
        u->color = COLOR_WHITE;
        u->parent = NULL;
    }
    int time = 0;
    for (int i = 0; i < G->nrNodes; i++) {
        Node* u = G->v[i];
        if (u->color == COLOR_WHITE);
            DFS_VISIT(G, u, time);
    }
}

void print_list (Graph* G) {
    for (int i = 0; i < G->nrNodes; i++) {
        Node* u = G->v[i];
        cout << "Nodul " << u->varf <<": ";
        for (int j = 0; j < u->adjSize; j++)
            cout << u->adj[j]->varf << " ";
        cout << endl;   
    }
}

void pretty_print(int* p, int space, int n, int r) {
    if (p == NULL)
        return;
    for (int i = 0; i < n; i++) {
        if (p[i] == r) {
            for (int j = 0; j < space; j++)
                printf("  ");
            cout << i <<"\n";
            pretty_print(p, space + 1, n, i);
        }
    }
}

void demo() {
    int x = 6;
    Graph* G = createG(x);
    add(G, 0, 1);
    add(G, 0, 3);
    add(G, 3, 1);
    add(G, 4, 3); 
    add(G, 1, 4);
    add(G, 2, 4);
    add(G, 2, 5);
    add(G, 5, 5);

    cout << "Lista de adiacenta:\n";
    print_list(G);
    cout << endl;

    DFS(G);

    int a[10];
    for (int i = 0; i < x; i++)
        if (G->v[i]->parent == NULL)
            a[i] = -1;
        else
            a[i] = G->v[i]->parent->varf;

    cout << "Vectorul de parinti: ";
    for (int i = 0; i < x; i++)
        cout << a[i] << " ";
    cout << endl;
    
    pretty_print(a, 0, x, -1);
}

int main()
{
    demo();
    return 0;
}

