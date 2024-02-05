#ifndef PRIM_H
#define PRIM_H

int costPrimMST(
    int vertices[], // subset of vertices
    int nbVertices, // number of vertices in the subset
    int nbAllVertices, // Number of vertices in the base graph
    int** cost // cost matrix of the base graph
);
void run_all_prim_cost_tests();

#endif // PRIM_H