#include "utils.h"

/**
 * @brief Returns the number of vertices, 
 * or exits the program if the number of arguments is 
 * incorrect.
 * 
 * @param argc Number of arguments
 * @param argv Array of arguments
*/
int getInputNumberOfVertices(int argc, char *argv[]) {
    bool isInputValid = true;
    int n;
    if (argc < 2) {
        printf("Error: missing argument <n>.\n");
        isInputValid = false;
    } else {
        n = atoi(argv[1]);
        if (n < 1) {
            printf("Error: argument <n> must be a strictly positive integer.\n");
            isInputValid = false;
        }
    }

    if (!isInputValid) {
        printf(
            "usage: '%s <n>', where <n> is a strictly positive integer.\n",
            argv[0]
        );
        exit(1); // Exit the program with error code 1
    }
    return n;
}

/**
 * @brief Returns true if the "generate python(-g)" option is given,
 * or false otherwise.
 * 
 * @param argc Number of arguments
 * @param argv Array of arguments
*/
bool getGeneratePythonFlag(int argc, char *argv[]) {
    bool generatePython = false;
    if (argc >= 3) {
        for (int i = 2; i < argc; i++) {
            if (strcmp(argv[i], "-g") == 0) {
                generatePython = true;
            }
        }
    }
    return generatePython;
}

/**
 * @brief Returns true if the "verbose(-v)" option is given,
 * or false otherwise.
*/
bool getVerboseFlag(int argc, char *argv[]) {
    bool verbose = false;
    if (argc >= 3) {
        for (int i = 2; i < argc; i++) {
            if (strcmp(argv[i], "-v") == 0) {
                verbose = true;
            }
        }
    }
    return verbose;
}

/**
 * @brief Print an array of integers in the console.
*/
void printArray(int array[], int n) {
    printf("[");
    for (int i = 0; i < n - 1; i++) {
        printf("%d, ", array[i]);
    }
    printf("%d]", array[n - 1]);
}