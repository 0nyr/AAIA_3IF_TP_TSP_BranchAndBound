#ifndef UTILS_H
#define UTILS_H

#include <stdbool.h>

int getInputNumberOfVertices(int argc, char *argv[]);
bool getGeneratePythonFlag(int argc, char *argv[]);
bool getVerboseFlag(int argc, char *argv[]);
void printArray(int array[], int n);
char * formatNumber(long number);
int min(int a, int b);

#endif // UTILS_H
