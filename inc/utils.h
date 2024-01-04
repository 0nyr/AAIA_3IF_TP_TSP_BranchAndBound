#ifndef UTILS_H  // Include guard to avoid double inclusion
#define UTILS_H

#include <stdio.h>  // For printf
#include <stdlib.h> // For exit() and atoi()
#include <stdbool.h> // For bool type

int getInputNumberOfVertices(int argc, char *argv[]);

bool getGeneratePythonFlag(int argc, char *argv[]);

#endif // UTILS_H
