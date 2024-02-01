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

    int expectedMSTCost;
    if (fscanf(file, "%d", &expectedMSTCost) != 1) {
        printf("Error reading the expected MST cost from the file.\n");
        // Free allocated memory and close the file before returning
        for (int i = 0; i < n; i++) {
            free(cost[i]);
        }
        free(cost);
        fclose(file);
        return;
    }

    // initialize vertices
    int* vertices = (int*)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        vertices[i] = i; // Assume vertices are labeled 0 to n-1
    }

    // calculate MST cost
    int mstCost = costPrimMST(vertices, n, n, cost);
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
 * @brief Runs the tests for the costPrimMST function.
 * Call this function from main.c to run the tests.
*/
void run_prim_cost_tests() {
    test_mst_cost("test_graphs/fully_connected_graph_2024-02-01-14-17-51.txt");
    test_mst_cost("test_graphs/fully_connected_graph_2024-02-01-14-20-09.txt");
    test_mst_cost("test_graphs/fully_connected_graph_2024-02-01-15-01-59.txt");
    test_mst_cost("test_graphs/fully_connected_graph_2024-02-01-15-02-04.txt");
    test_mst_cost("test_graphs/fully_connected_graph_2024-02-01-16-19-35.txt");
}
