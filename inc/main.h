#ifndef MAIN_H
#define MAIN_H

#include <stdbool.h>

int nextRand(int n);
int** createCost(int n);
void genPythonTurtleTour(int visited[], int n);
bool hasCrossingEdges(
    int visited[], 
    int nbVisited, 
    int newVertex, 
    int** cost
);
int costPrimMST(
    int vertices[], 
    int nbVertices, 
    int** cost
);
int bound(
    int lastVisited, 
    int notVisited[], int nbNotVisited,
    int** cost
);
void permutLoop(
    int visited[], int nbVisited, int costVisited,
    int notVisited[], int nbNotVisited,
    int** cost
);
void permut(
    int visited[], int nbVisited, int costVisited,
    int notVisited[], int nbNotVisited,
    int** cost
);
void printCostMatrix(int** cost, int n);

#endif
