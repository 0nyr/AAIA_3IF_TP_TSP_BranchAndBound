#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <math.h>
#include <time.h>
#include <stdbool.h>

#include "utils.h"

int iseed = 1;     // Seed used to initialize the random number generator
int** cost;        // cost[i][j] = cost[j][i] = cost of edge {i,j}
long int nbCalls = 0; // Number of calls to the recursive permut function
FILE* fd;          // File descriptor of the Python script

int nextRand(int n) {
    // Postcondition: return an integer value in [0,n-1], according to a pseudo-random sequence which is initialized with iseed
    int i = 16807 * (iseed % 127773) - 2836 * (iseed / 127773);
    if (i > 0) iseed = i;
    else iseed = 2147483647 + i;
    return iseed % n;
}

void createCost(int n) {
    // input: the number n of vertices
    // return a symmetrical cost matrix such that, for each i,j in [0,n-1], cost[i][j] = cost of arc (i,j)
    int x[n], y[n];
    int max = 20000;
    cost = (int**) malloc(n*sizeof(int*));
    fprintf(fd, "import turtle\n");
    fprintf(fd, "turtle.setworldcoordinates(0, 0, %d, %d)\n", max, max+100);
    for (int i=0; i<n; i++) {
        x[i] = nextRand(max);
        y[i] = nextRand(max);
        fprintf(fd, "p%d=(%d,%d)\n", i, x[i], y[i]);
        cost[i] = (int*)malloc(n*sizeof(int));
    }
    for (int i=0; i<n; i++) {
        cost[i][i] = max*max;
        for (int j=i+1; j<n; j++) {
            cost[i][j] = sqrt((x[i]-x[j])*(x[i]-x[j]) + (y[i]-y[j])*(y[i]-y[j]));
            cost[j][i] = cost[i][j];
        }
    }
}

void print(int visited[], int n) {
    // input: n = number n of vertices; sol[0..n-1] = permutation of [0,n-1]; fd = file descriptor
    // side effect: print in fd the Python script for displaying the tour associated with sol
    fprintf(fd, "turtle.clear()\n");
    fprintf(fd, "turtle.tracer(0,0)\n");
    fprintf(fd, "turtle.penup()\n");
    fprintf(fd, "turtle.speed(0)\n");
    fprintf(fd, "turtle.goto(p%d)\n", visited[0]);
    fprintf(fd, "turtle.pendown()\n");
    for (int i=1; i<n; i++) fprintf(fd, "turtle.goto(p%d)\n", visited[i]);
    fprintf(fd, "turtle.goto(p%d)\n", visited[0]);
    fprintf(fd, "turtle.update()\n");
    fprintf(fd, "wait = input(\"Enter return to continue\")\n");
}

void permut(int visited[], int nbVisited, int notVisited[], int nbNotVisited) {
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
}

int main(int argc, char *argv[]) {
    int n = getInputNumberOfVertices(argc, argv);

    fd  = fopen("script.py", "w");
    createCost(n);

    clock_t t = clock();
    int visited[n], notVisited[n-1];
    visited[0] = 0;
    for (int i=0; i<n-1; i++)
        notVisited[i] = i+1;
    permut(visited, 1, notVisited, n-1);
    printf("n=%d nbCalls=%ld time=%.3fs\n", n, nbCalls, ((double) (clock() - t)) / CLOCKS_PER_SEC);
    
    return 0;
}
