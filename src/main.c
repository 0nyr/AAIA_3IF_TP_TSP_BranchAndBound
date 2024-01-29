#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <math.h>
#include <time.h>
#include <stdbool.h>
#include <string.h>

#include "utils.h"
#include "quicksort.h"
#include "main.h" // WARN: Needed for functions used before they are defined like permut()

int iseed = 1;     // Seed used to initialize the random number generator
int** cost;        // cost[i][j] = cost[j][i] = cost of edge {i,j}
long int nbCalls = 0; // Number of calls to the recursive permut function
FILE* fd;          // File descriptor of the Python script
int bestCost = INT_MAX; // Best cost found so far

// CLI flags
bool generatePython = false;
bool verbose = false;


int nextRand(int n) {
    // Postcondition: return an integer value in [0,n-1], according to a pseudo-random sequence which is initialized with iseed
    int i = 16807 * (iseed % 127773) - 2836 * (iseed / 127773);
    if (i > 0) iseed = i;
    else iseed = 2147483647 + i;
    return iseed % n;
}

int** createCost(int n) {
    // input: the number n of vertices
    // return a symmetrical cost matrix such that, for each i,j in [0,n-1], cost[i][j] = cost of arc (i,j)
    int x[n], y[n];
    int max = 20000;

    for (int i=0; i<n; i++){
        x[i] = nextRand(max);
        y[i] = nextRand(max);
    }

    // allocate memory for cost matrix
    int** cost = (int**) malloc(n*sizeof(int*));
    for (int i=0; i<n; i++) cost[i] = (int*)malloc(n*sizeof(int));

    // init python script
    if (generatePython) {
        fprintf(fd, "import turtle\n\n");
        fprintf(fd, "from utils import mark_point\n\n");
        fprintf(fd, "def draw_path_permutations(turtle_speed):\n");
        fprintf(fd, "    # Configuration initiale\n");
        fprintf(fd, "    turtle.setworldcoordinates(0, 0, %d, %d)\n", max, max+100);
    
        // Generate n random points in python turtle space
        for (int i=0; i<n; i++) {
            x[i] = nextRand(max);
            y[i] = nextRand(max);
            fprintf(fd, "    p%d=(%d,%d)\n", i, x[i], y[i]);
            cost[i] = (int*)malloc(n*sizeof(int));
        }
        fprintf(fd, "\n\n");
        fprintf(fd, "    # Affichage des points\n");
        fprintf(fd, "    def mark_all_points():\n");
        for (int i=0; i<n; i++) fprintf(fd, "        mark_point(p%d)\n", i);
        fprintf(fd, "\n");
        fprintf(fd, "    turtle.speed(turtle_speed)\n");
        fprintf(fd, "    mark_all_points()\n\n");
        fprintf(fd, "    wait = input(\"Enter return to start\")\n\n");
    }

    // create cost matrix
    for (int i=0; i<n; i++) {
        cost[i][i] = max*max;
        for (int j=i+1; j<n; j++) {
            cost[i][j] = sqrt((x[i]-x[j])*(x[i]-x[j]) + (y[i]-y[j])*(y[i]-y[j]));
            cost[j][i] = cost[i][j];
        }
    }

    return cost;
}

/**
 * @brief Generate python code for the tour associated with the given permutation.
 * 
 * @param visited Array of visited vertices
 * @param n Number of vertices
 * 
*/
void genPythonTurtleTour(int visited[], int n) {
    // input: n = number n of vertices; sol[0..n-1] = permutation of [0,n-1]; fd = file descriptor
    // side effect: print in fd the Python script for displaying the tour associated with sol
    fprintf(fd, "    # path permutation\n");
    fprintf(fd, "    turtle.clear()\n");
    fprintf(fd, "    mark_all_points()\n");
    fprintf(fd, "    turtle.penup()\n");
    fprintf(fd, "    turtle.goto(p%d)\n", visited[0]);
    fprintf(fd, "    turtle.pendown()\n");
    for (int i=1; i<n; i++) fprintf(fd, "    turtle.goto(p%d)\n", visited[i]);
    fprintf(fd, "    turtle.goto(p%d)\n", visited[0]);
    fprintf(fd, "    turtle.update()\n");
    fprintf(fd, "    wait = input(\"Enter return to continue\")\n\n");
}

bool isCrossing(
    int node0, 
    int node1,
    int nodeLast, 
    int nodeNew,
    int** cost
) {
    /* check each edge before the last one

    Example:
    Ⓝ◁---①
    ╎◸   ◹╎
    ╎ ╲ ╱ ╎
    ╎  ╳  ╎
    ╎ ╱ ╲ ╎
    ╎╱   ╲╎
    ⓪---▷Ⓛ

    We check that any edge (⓪->① + Ⓛ->Ⓝ) <= (⓪->Ⓛ + ①->Ⓝ)
    */
    // cost Ⓛ->Ⓝ
    int costLastToNew = cost[nodeLast][nodeNew];
    // cost ⓪->①
    int cost0to1 = cost[node0][node1];
    // cost ⓪->Ⓛ
    int cost0toLast = cost[node0][nodeLast];
    // cost ①->Ⓝ
    int cost1toNew = cost[node1][nodeNew];
    if (
        (cost0toLast + cost1toNew) // cost ⓪->Ⓛ + ①->Ⓝ
        < (cost0to1 + costLastToNew) // cost ⓪->① + Ⓛ->Ⓝ
    ) {
        return true;
    } else {
        return false;
    }
}


/**
 * @brief Returns true if the tour would have crossing edges 
 * by adding newVertex to visited[0..nbVisited-1], 
 * false otherwise.
*/
bool hasCrossingEdges(
    int visited[], 
    int nbVisited, 
    int newVertex, 
    int** cost
) {
    if (nbVisited <= 3) {
        return false; // no crossing edges with 3 vertices or less
    }
    /* check each edge before the last one
    that adding the edge (Ⓛ->Ⓝ) would not create a crossing edge
    with previously visited edges (⓪->①)
    */
    for (int i = 0; i < nbVisited - 1; i++) { // from first to last but one
    
        if (isCrossing(
            visited[i], visited[i+1],
            visited[nbVisited-1], newVertex,
            cost
        )) {
            return true;
        }
    }
    return false;
}

/**
 * @brief Returns the cost of the Minimum Spanning Tree (MST)
 * of given vertices.
 * 
 * NOTE: Because the base graph is complete, no need to pass a 
 * structure other than the number of vertices and the cost matrix.
*/
int costPrimMST(
    int baseGraphNbVertices,
    int vertices[], 
    int nbVertices, 
    int** cost
) {
    int s0 = vertices[0];

    // initializations
    bool* isVisited = (bool*) malloc(baseGraphNbVertices*sizeof(bool));
    int* minCostfrom = (int*) malloc(baseGraphNbVertices*sizeof(int));
    int* predecesor = (int*) malloc(baseGraphNbVertices*sizeof(int));
    // for (int i = 0; i < baseGraphNbVertices; i++) {
    //     minCostfrom[i] = INT_MAX;
    //     predecesor[i] = -1;
    //     isVisited[i] = false;
    // }
    isVisited[s0] = true;
    int nbVisited = 1;
    for (int i = 1; i < nbVertices; i++) {
        isVisited[vertices[i]] = false;
        minCostfrom[vertices[i]] = cost[s0][vertices[i]];
        predecesor[vertices[i]] = s0;
    }

    while (nbVisited < nbVertices) {
        // get vertex with minimum cost
        int minCost = INT_MAX;
        int sMinCost;
        for (int i = 1; i < nbVertices; i++) {
            if (minCostfrom[vertices[i]] < minCost) {
                minCost = minCostfrom[vertices[i]];
                sMinCost = vertices[i];
            }
        }

        isVisited[sMinCost] = true;
        nbVisited++;

        for(int i = 1; i < nbVertices; i++) {
            if (isVisited[vertices[i]] == false &
                cost[sMinCost][vertices[i]] < minCostfrom[vertices[i]]
            ) {
                predecesor[vertices[i]] = sMinCost;
                minCostfrom[vertices[i]] = cost[sMinCost][vertices[i]];
            }
        }
    }

    // compute sum of costs (sum of all the predecesor arborescence's costs)
    int sum = 0;
    for (int i = 1; i < nbVertices; i++) {
        sum += cost[predecesor[vertices[i]]][vertices[i]];
    }

    // clean up
    free(isVisited);
    free(minCostfrom);
    free(predecesor);

    return sum;
}

/**
 * @brief Evaluation function (bound), that returns
 * a lower bound of the cost of a path from the last 
 * visited vertex to the end of the tour (vertex 0), 
 * passing by all the remaining unvisited vertices.
*/
int bound(
    int visited[], int nbVisited, 
    int notVisited[], int nbNotVisited,
    int** cost
) {
    int sum = 0;
    // get l, lenght of the smallest edge from the last 
    // visited vertex to one of the remaining unvisited 
    // vertices.
    // Same for lToZero, from any unvisited vertex to 0.
    int lFromLast, lToZero = INT_MAX;
    for (int i; i < nbNotVisited; i++) {
        if (cost[visited[nbVisited-1]][notVisited[i]] < lFromLast) {
            lFromLast = cost[visited[nbVisited-1]][notVisited[i]];
        }
        if (cost[notVisited[i]][0] < lToZero) {
            lToZero = cost[notVisited[i]][0];
        }
    }
    sum += lFromLast + lToZero;

    // Now, for every remaining unvisited vertex, we compute
    // the value of the minimum spanning tree (MST) of the
    // remaining unvisited vertices, and add it to the sum.
    sum += costPrimMST(
        nbNotVisited + nbVisited, // n 
        notVisited, nbNotVisited, cost
    );

    return sum;
}

/**
 * @brief Loop inside the recursive function that computes all 
 * the permutations of the vertices of the graph.
 * 
 * @param visited Array of visited vertices
 * @param nbVisited Number of visited vertices
 * @param costVisited Cost of the visited vertices
 * @param notVisited Array of unvisited vertices
 * @param nbNotVisited Number of unvisited vertices
 * @param cost Cost matrix
*/
void permutLoop(
    int visited[], int nbVisited, int costVisited,
    int notVisited[], int nbNotVisited,
    int** cost
) {
    for (int i = 0; i < nbNotVisited; i++) {
        // constraint: no crossing edges
        if (hasCrossingEdges(visited, nbVisited, notVisited[i], cost))
            continue;

        // add notVisited[i] to visited 
        // WARN: Need to be done BEFORE checking constraints
        visited[nbVisited] = notVisited[i];

        // remove notVisited[i] from notVisited
        // we need to swap notVisited[i] with notVisited[nbNotVisited-1] for 
        // easy restoration of the array after the recursive call
        int tmp = notVisited[i];
        notVisited[i] = notVisited[nbNotVisited-1];
        notVisited[nbNotVisited-1] = tmp;
        
        // constraint: bound
        int nextCost = costVisited + cost[visited[nbVisited-1]][notVisited[i]];
        // int boundedCost = nextCost + bound(
        //     visited, nbVisited, 
        //     notVisited, nbNotVisited,
        //     cost
        // );
        // if (boundedCost > bestCost)
        //     continue;

        // recursive call
        permut(
            visited, nbVisited+1, nextCost,
            notVisited, nbNotVisited-1,
            cost    
        );
        
        // backtrack
        notVisited[nbNotVisited-1] = notVisited[i];
        notVisited[i] = tmp;
    }
}

void permut(
    int visited[], int nbVisited, int costVisited,
    int notVisited[], int nbNotVisited,
    int** cost
) {
    /*
     Input:
     - visited[0..nbVisited-1] = visited vertices
     - notVisited[0..nbNotVisited-1] = unvisited vertices
     Precondition:
     - nbVisited > 0 and visited[0] = 0 (the tour always starts with vertex 0)
     Postcondition: print all tours starting with visited[0..nbVisited-1] and ending with vertices of notVisited[0..nbNotVisited-1] (in any order), followed by 0
     */
    nbCalls++;
    // INSERT YOUR CODE HERE!
    if (nbNotVisited == 0) {
        if (generatePython)
            genPythonTurtleTour(visited, nbVisited);

        // compute cost, don't forget to add the cost of the last edge
        costVisited += cost[visited[nbVisited-1]][0];

        if (verbose) {
            // log permutation in terminal
            printf("[");
            for (int i = 0; i < nbVisited; i++) {
                printf("%d, ", visited[i]);
            }
            printf("0]");
            printf(" cost: %d\n", costVisited);
        }

        // update best cost
        if (costVisited < bestCost) {
            bestCost = costVisited;
        }
    }

    // reordering notVisited array (a copy of it)
    // wrt cost of edge from last visited vertex

    // make copies of arrays before sorting in place
    // int* costsFromLastVisited = (int*) malloc(nbNotVisited*sizeof(int));
    // for (int i = 0; i < nbNotVisited; i++) {
    //     costsFromLastVisited[i] = cost[visited[nbVisited-1]][notVisited[i]];
    // }
    // int* notVisitedIncrOrder = (int*) malloc(nbNotVisited*sizeof(int));
    // for (int i = 0; i < nbNotVisited; i++) {
    //     notVisitedIncrOrder[i] = notVisited[i];
    // }

    // quicksortInPlace(
    //     notVisitedIncrOrder, 
    //     0, // index of first element
    //     nbNotVisited - 1, // WARN: index of last element, not number of elements
    //     costsFromLastVisited
    // );

    // recursive call, with reordered notVisited array
    permutLoop(
        visited, nbVisited, costVisited,
        //notVisitedIncrOrder, nbNotVisited,
        notVisited, nbNotVisited,
        cost
    );

    // clean up
    // free(costsFromLastVisited);
    // free(notVisitedIncrOrder);
}

int main(int argc, char *argv[]) {
    int n = getInputNumberOfVertices(argc, argv);
    generatePython = getGeneratePythonFlag(argc, argv);
    verbose = getVerboseFlag(argc, argv);

    if (generatePython)
        fd  = fopen("python/generated.py", "w");
    
    int** costMatrix = createCost(n);

    // initializations
    clock_t t = clock();
    int visited[n]; // can contain all vertices
    int notVisited[n-1]; // can contain all vertices except 0
    visited[0] = 0;
    for (int i = 0; i < (n-1); i++)
        notVisited[i] = i+1;
    
    permut(visited, 1, 0, notVisited, n-1, costMatrix);
    printf(
        "n=%d, bestCost=%d, nbCalls=%ld, time=%.3fs\n",
        n, 
        bestCost,
        nbCalls, 
        ((double) (clock() - t)) / CLOCKS_PER_SEC
    );
    
    // clean up
    if (generatePython)
        fclose(fd);

    // clean up cost matrix
    for (int i = 0; i < n; i++) free(costMatrix[i]);
    free (costMatrix);

    return 0;
}
