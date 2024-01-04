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