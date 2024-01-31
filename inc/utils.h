#ifndef UTILS_H  // Include guard to avoid double inclusion
#define UTILS_H

#include <stdio.h>  // For printf
#include <stdlib.h> // For exit() and atoi()
#include <stdbool.h> // For bool type
#include <string.h> // For strcmp()

int getInputNumberOfVertices(int argc, char *argv[]);
bool getGeneratePythonFlag(int argc, char *argv[]);
bool getVerboseFlag(int argc, char *argv[]);
void printArray(int array[], int n);
char * formatNumber(long number);
int min(int a, int b);

#endif // UTILS_H
