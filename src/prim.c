/**
 * This file including the test cases have been generated
 * using a custom program. See below:
 * https://github.com/0nyr/prim_algorithm
*/

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>

/**
 * @brief Returns the cost of the Minimum Spanning Tree (MST)
 * of given vertices.
 * 
 * NOTE: Because the base graph is complete, no need to pass a 
 * structure other than the number of vertices and the cost matrix.
*/
int costPrimMST(
    int vertices[], // subset of vertices
    int nbVertices, // number of vertices in the subset
    int nbAllVertices, // Number of vertices in the base graph
    int** cost // cost matrix of the base graph
) {
    bool* isVisited = (bool*) malloc(nbAllVertices * sizeof(bool));
    int* minCostfrom = (int*) malloc(nbAllVertices * sizeof(int));
    int* predecesor = (int*) malloc(nbAllVertices * sizeof(int));

    // Assuming vertices[0] is the starting vertex
    int s0 = vertices[0];
    isVisited[s0] = true;
    predecesor[s0] = -1;
    minCostfrom[s0] = 0;
    int nbVisited = 1;

    for (int i = 1; i < nbVertices; i++) {
        int v = vertices[i];
        isVisited[v] = false;
        predecesor[v] = s0;
        minCostfrom[v] = cost[v][s0];
    }

    while (nbVisited < nbVertices) {
        int minCost = INT_MAX;
        int sMinCost = -1;
        for (int i = 1; i < nbVertices; i++) {
            int v = vertices[i];
            if (!isVisited[v] && minCostfrom[v] < minCost) {
                minCost = minCostfrom[v];
                sMinCost = v;
            }
        }

        isVisited[sMinCost] = true;
        nbVisited++;

        for (int i = 1; i < nbVertices; i++) {
            int v = vertices[i];
            if (!isVisited[v] && cost[sMinCost][v] < minCostfrom[v]) {
                predecesor[v] = sMinCost;
                minCostfrom[v] = cost[sMinCost][v];
            }
        }
    }

    int sum = 0;
    // WARN: don't add the cost of the starting vertex
    // WARN: don't do minCostfrom[i], do minCostfrom[vertices[i]]. 
    // This is a terrible mistake that cost me a lot of time.
    // It doesn't get detected by the tests since the test are on 
    // all base graph nodes.
    for (int i = 1; i < nbVertices; i++) {
        sum += minCostfrom[i];
    }

    free(isVisited);
    free(minCostfrom);
    free(predecesor);

    return sum;
}

void test_mst_cost(char * filename) {
    printf("Testing MST cost for %s\n", filename);

    // load file
    FILE *file;
    file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error opening file: %s.\n", filename);
        return;
    }

    // read values from test file
    int n;
    if (fscanf(file, "%d", &n) != 1) {
        printf("Error reading the number of nodes from the file.\n");
        fclose(file);
        return;
    }

    int** cost = (int**)malloc(n * sizeof(int*));
    for (int i = 0; i < n; i++) {
        cost[i] = (int*)malloc(n * sizeof(int));
        for (int j = 0; j < n; j++) {
            if (fscanf(file, "%d", &cost[i][j]) != 1) {
                printf("Error reading cost matrix from the file.\n");
                // Free allocated memory and close the file before returning
                for (int k = 0; k <= i; k++) {
                    free(cost[k]);
                }
                free(cost);
                fclose(file);
                return;
            }
        }
    }

    int nbNodesNotInMSTfromBaseGraph = 0;
    if (fscanf(file, "%d", &nbNodesNotInMSTfromBaseGraph) != 1) {
        printf("Error reading the number of nodes not in the MST from the file.\n");
    }

    int expectedMSTCost;
    if (fscanf(file, "%d", &expectedMSTCost) != 1) {
        printf("Error reading the expected MST cost from the file.\n");
    }

    // determine the number of vertices in the MST
    int nbVerticesInMST;
    if (nbNodesNotInMSTfromBaseGraph > 0) {
        nbVerticesInMST = n - nbNodesNotInMSTfromBaseGraph;
    } else {
        nbVerticesInMST = n;
    }

    // initialize vertices for the MST
    int* vertices = (int*)malloc(n * sizeof(int));
    for (int i = 0; i < nbVerticesInMST; i++) {
        vertices[i] = i;
    }

    // calculate MST cost
    int mstCost = costPrimMST(vertices, nbVerticesInMST, n, cost);
    printf("Calculated MST cost: %d\n", mstCost);

    if (mstCost == expectedMSTCost) {
        printf("🟢 Success: The calculated MST cost matches the expected value (%d).\n", expectedMSTCost);
    } else {
        printf("🔴 Failure: The calculated MST cost does not match the expected value (%d).\n", expectedMSTCost);
    }

    for (int i = 0; i < n; i++) {
        free(cost[i]);
    }
    free(cost);
    free(vertices);
    fclose(file);
}

/**
 * @brief Runs the tests for the costPrimMST function, using the complete MSTs
*/
void run_prim_cost_tests_on_full_mst() {
    test_mst_cost("test_graphs/complete_mst/fully_connected_graph_complete_mst_2024-02-05-09-02-10.txt");
    test_mst_cost("test_graphs/complete_mst/fully_connected_graph_complete_mst_2024-02-05-09-02-17.txt");
    test_mst_cost("test_graphs/complete_mst/fully_connected_graph_complete_mst_2024-02-05-09-02-22.txt");
}

/**
 * @brief Runs the tests for the costPrimMST function, using the partial MSTs
*/
void run_prim_cost_test_on_partial_mst() {
    test_mst_cost("test_graphs/partial_mst/fully_connected_graph_partial_mst__2024-02-02-11-28-22.txt");
    test_mst_cost("test_graphs/partial_mst/fully_connected_graph_partial_mst__2024-02-02-11-29-56.txt");
    test_mst_cost("test_graphs/partial_mst/fully_connected_graph_partial_mst__2024-02-02-11-30-03.txt");
}

/**
 * @brief Runs all the tests for the costPrimMST function
*/
void run_all_prim_cost_tests() {
    run_prim_cost_tests_on_full_mst();
    run_prim_cost_test_on_partial_mst();
}
