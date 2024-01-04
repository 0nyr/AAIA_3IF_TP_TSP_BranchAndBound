#ifndef UTILS_H  // Include guard to avoid double inclusion
#define UTILS_H

#include <stdio.h>  // For printf
#include <stdlib.h> // For exit() and atoi()
#include <stdbool.h> // For bool type

/**
 * @brief Returns the number of vertices, 
 * or exits the program if the number of arguments is 
 * incorrect.
 * 
 * @param argc Number of arguments
 * @param argv Array of arguments
 * @return int The number of vertices
 */
int getInputNumberOfVertices(int argc, char *argv[]);

#endif // UTILS_H
