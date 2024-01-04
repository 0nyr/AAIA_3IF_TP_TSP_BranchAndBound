#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <math.h>
#include <time.h>
#include <stdbool.h>
#include <string.h>

#include "utils.h"

int iseed = 1;     // Seed used to initialize the random number generator
int** cost;        // cost[i][j] = cost[j][i] = cost of edge {i,j}
long int nbCalls = 0; // Number of calls to the recursive permut function
FILE* fd;          // File descriptor of the Python script
int bestCost = INT_MAX; // Best cost found so far

bool generatePython = false;

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
    int** cost = (int**) malloc(n*sizeof(int*));

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

void permut(
    int visited[], int nbVisited, 
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

        // log permutation in terminal
        printf("[");
        for (int i = 0; i < nbVisited; i++) {
            printf("%d, ", visited[i]);
        }
        printf("0]");

        // compute and display cost
        int totalCost = 0;
        for (int i = 0; i < nbVisited-1; i++) {
            totalCost += cost[visited[i]][visited[i+1]];
        }
        totalCost += cost[visited[nbVisited-1]][visited[0]];
        printf(" cost: %d\n", totalCost);

        // update best cost
        if (totalCost < bestCost) {
            bestCost = totalCost;
        }
    }
    for (int i = 0; i < nbNotVisited; i++) {
        // add notVisited[i] to visited
        visited[nbVisited] = notVisited[i];

        // remove notVisited[i] from notVisited
        // we need to swap notVisited[i] with notVisited[nbNotVisited-1] for 
        // easy restoration of the array after the recursive call
        int tmp = notVisited[i];
        notVisited[i] = notVisited[nbNotVisited-1];
        notVisited[nbNotVisited-1] = tmp;

        // recursive call
        permut(
            visited, nbVisited+1, 
            notVisited, nbNotVisited-1,
            cost    
        );
        
        // backtrack
        notVisited[nbNotVisited-1] = notVisited[i];
        notVisited[i] = tmp;
    }
}

int main(int argc, char *argv[]) {
    int n = getInputNumberOfVertices(argc, argv);
    generatePython = getGeneratePythonFlag(argc, argv);

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
    
    permut(visited, 1, notVisited, n-1, costMatrix);
    printf("best cost: %d\n", bestCost);
    printf("n=%d nbCalls=%ld time=%.3fs\n", n, nbCalls, ((double) (clock() - t)) / CLOCKS_PER_SEC);
    
    // clean up
    if (generatePython)
        fclose(fd);
    for (int i = 0; i < n; i++) free(costMatrix[i]);

    return 0;
}
