/*
    Boar Daniel-Ioan
    Grupa 30223 

    Am implementat parcurgerea in latime (BFS).
    Am implementat o metoda ce ne afla vecinii unui nod, imi face parcurgerea si apoi imi afiseaza cu un pretty_print nodurile care fac parte din BFS.
*/

#include <stdlib.h>
#include <string.h>
#include "bfs.h"

int get_neighbors(const Grid *grid, Point p, Point neighb[])
{
    int count = 0;
    //verificam daca punctul este in tabela
    if ((p.row > 0 && p.row < 9) && (p.col > 0 && p.col < 17) && grid->mat[p.row][p.col] == 0) {
        //vecinul de sus
        if (p.row - 1 > 0 && grid->mat[p.row - 1][p.col] == 0) {
            neighb[count].row = p.row - 1;
            neighb[count].col = p.col;
            count++;
        }

        //vecinul de jos
        if (p.row + 1 < 9 && grid->mat[p.row + 1][p.col] == 0) {
            neighb[count].row = p.row + 1;
            neighb[count].col = p.col;
            count++;
        }

        //vecinul din stanga
        if (p.col - 1 > 0 && grid->mat[p.row][p.col - 1] == 0) {
            neighb[count].row = p.row;
            neighb[count].col = p.col - 1;
            count++;
        }

        // vecinul din dreapta
        if (p.col + 1 < 17 && grid->mat[p.row][p.col + 1] == 0) {
            neighb[count].row = p.row;
            neighb[count].col = p.col + 1;
            count++;
        }
        return count;
    }
    return 0;
}

void grid_to_graph(const Grid *grid, Graph *graph)
{
    //we need to keep the nodes in a matrix, so we can easily refer to a position in the grid
    Node *nodes[MAX_ROWS][MAX_COLS];
    int i, j, k;
    Point neighb[4];

    //compute how many nodes we have and allocate each node
    graph->nrNodes = 0;
    for(i=0; i<grid->rows; ++i){
        for(j=0; j<grid->cols; ++j){
            if(grid->mat[i][j] == 0){
                nodes[i][j] = (Node*)malloc(sizeof(Node));
                memset(nodes[i][j], 0, sizeof(Node)); //initialize all fields with 0/NULL
                nodes[i][j]->position.row = i;
                nodes[i][j]->position.col = j;
                ++graph->nrNodes;
            }else{
                nodes[i][j] = NULL;
            }
        }
    }
    graph->v = (Node**)malloc(graph->nrNodes * sizeof(Node*));
    k = 0;
    for(i=0; i<grid->rows; ++i){
        for(j=0; j<grid->cols; ++j){
            if(nodes[i][j] != NULL){
                graph->v[k++] = nodes[i][j];
            }
        }
    }

    //compute the adjacency list for each node
    for(i=0; i<graph->nrNodes; ++i){
        graph->v[i]->adjSize = get_neighbors(grid, graph->v[i]->position, neighb);
        if(graph->v[i]->adjSize != 0){
            graph->v[i]->adj = (Node**)malloc(graph->v[i]->adjSize * sizeof(Node*));
            k = 0;
            for(j=0; j<graph->v[i]->adjSize; ++j){
                if( neighb[j].row >= 0 && neighb[j].row < grid->rows &&
                    neighb[j].col >= 0 && neighb[j].col < grid->cols &&
                    grid->mat[neighb[j].row][neighb[j].col] == 0){
                        graph->v[i]->adj[k++] = nodes[neighb[j].row][neighb[j].col];
                }
            }
            if(k < graph->v[i]->adjSize){
                //get_neighbors returned some invalid neighbors
                graph->v[i]->adjSize = k;
                graph->v[i]->adj = (Node**)realloc(graph->v[i]->adj, k * sizeof(Node*));
            }
        }
    }
}

void free_graph(Graph *graph)
{
    if(graph->v != NULL){
        for(int i=0; i<graph->nrNodes; ++i){
            if(graph->v[i] != NULL){
                if(graph->v[i]->adj != NULL){
                    free(graph->v[i]->adj);
                    graph->v[i]->adj = NULL;
                }
                graph->v[i]->adjSize = 0;
                free(graph->v[i]);
                graph->v[i] = NULL;
            }
        }
        free(graph->v);
        graph->v = NULL;
    }
    graph->nrNodes = 0;
}

void bfs(Graph *graph, Node *s, Operation *op)
{
    for (int i = 0; i < graph->nrNodes; i++) {
        graph->v[i]->color = COLOR_WHITE;
        graph->v[i]->dist = 0;
        graph->v[i]->parent = NULL;
    }
    s->color = COLOR_GRAY;
    s->dist = 0;
    s->parent = NULL;
    Node** Q = (Node**)malloc(sizeof(Node*));
    int i = 0, j = 0;
    Q[i] = s; // enqueue(Q,s)
    j++;
    while (i != j) {
        Node* u = Q[i]; // dequeue(Q)
        i++;
        for (int k = 0; k < u->adjSize; k++) {
            Node* q = u->adj[k];
            if (q->color == COLOR_WHITE) {
                q->color = COLOR_GRAY;
                q->dist = u->dist + 1;
                q->parent = u;
                Q[j] = q; // enqueue(Q,q)
                j++;
            }
        }
        u->color = COLOR_BLACK;
    }
}

void pretty_print(int* p, Point* repr, int space, int n, int r) {
    if (p == NULL)
        return;
    for (int i = 0; i < n; i++) {
        if (p[i] == r) {
            for (int j = 0; j < space; j++)
                printf("        ");
            printf("(%d, %d)\n", repr[i].row, repr[i].col);
            pretty_print(p, repr, space + 1, n, i);
        }
    }
}

void print_bfs_tree(Graph *graph)
{
    //first, we will represent the BFS tree as a parent array
    int n = 0; //the number of nodes
    int *p = NULL; //the parent array
    Point *repr = NULL; //the representation for each element in p

    //some of the nodes in graph->v may not have been reached by BFS
    //p and repr will contain only the reachable nodes
    int *transf = (int*)malloc(graph->nrNodes * sizeof(int));
    for(int i=0; i<graph->nrNodes; ++i){
        if(graph->v[i]->color == COLOR_BLACK){
            transf[i] = n;
            ++n;
        }else{
            transf[i] = -1;
        }
    }
    if(n == 0){
        //no BFS tree
        free(transf);
        return;
    }

    int err = 0;
    p = (int*)malloc(n * sizeof(int));
    repr = (Point*)malloc(n * sizeof(Node));
    for(int i=0; i<graph->nrNodes && !err; ++i){
        if(graph->v[i]->color == COLOR_BLACK){
            if(transf[i] < 0 || transf[i] >= n){
                err = 1;
            }else{
                repr[transf[i]] = graph->v[i]->position;
                if(graph->v[i]->parent == NULL){
                    p[transf[i]] = -1;
                }else{
                    err = 1;
                    for(int j=0; j<graph->nrNodes; ++j){
                        if(graph->v[i]->parent == graph->v[j]){
                            if(transf[j] >= 0 && transf[j] < n){
                                p[transf[i]] = transf[j];
                                err = 0;
                            }
                            break;
                        }
                    }
                }
            }
        }
    }
    free(transf);
    transf = NULL;

    if(!err){
        int space = 0;
        pretty_print(p, repr, space, n, -1);
    }

    if(p != NULL){
        free(p);
        p = NULL;
    }
    if(repr != NULL){
        free(repr);
        repr = NULL;
    }
}

int shortest_path(Graph *graph, Node *start, Node *end, Node *path[])
{
    // TODO: compute the shortest path between the nodes start and end in the given graph
    // the nodes from the path, should be filled, in order, in the array path
    // the number of nodes filled in the path array should be returned
    // if end is not reachable from start, return -1
    // note: the size of the array path is guaranteed to be at least 1000
    return -1;
}


void performance()
{
    int n, i;
    Profiler p("bfs");

    // vary the number of edges
    for(n=1000; n<=4500; n+=100){
        Operation op = p.createOperation("bfs-edges", n);
        Graph graph;
        graph.nrNodes = 100;
        //initialize the nodes of the graph
        graph.v = (Node**)malloc(graph.nrNodes * sizeof(Node*));
        for(i=0; i<graph.nrNodes; ++i){
            graph.v[i] = (Node*)malloc(sizeof(Node));
            memset(graph.v[i], 0, sizeof(Node));
        }
        // TODO: generate n random edges
        // make sure the generated graph is connected

        bfs(&graph, graph.v[0], &op);
        free_graph(&graph);
    }

    // vary the number of vertices
    for(n=100; n<=200; n+=10){
        Operation op = p.createOperation("bfs-vertices", n);
        Graph graph;
        graph.nrNodes = n;
        //initialize the nodes of the graph
        graph.v = (Node**)malloc(graph.nrNodes * sizeof(Node*));
        for(i=0; i<graph.nrNodes; ++i){
            graph.v[i] = (Node*)malloc(sizeof(Node));
            memset(graph.v[i], 0, sizeof(Node));
        }
        // TODO: generate 4500 random edges
        // make sure the generated graph is connected

        bfs(&graph, graph.v[0], &op);
        free_graph(&graph);
    }

    p.showReport();
}
