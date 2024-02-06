#include <stdio.h>
#include <stdlib.h>

/**
 * @brief Swaps the values of two integers.
 * WARN: Needs to pass the pointers to the integers.
 * 
 * @param a Pointer to the first integer
 * @param b Pointer to the second integer
*/
void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

/**
 * @brief Partitions the array of elements around a pivot.
 * 
 * @param arrayOfElements Array of elements
 * @param low Index of the first element
 * @param high Index of the last element
 * @param cost Array of costs
 * @return int Index of the pivot
*/
int partition(int arrayOfElements[], int low, int high, int cost[]) {
    int pivot = cost[high];
    int i = (low - 1);

    for (int j = low; j <= high - 1; j++) {
        if (cost[j] < pivot) {
            i++;
            swap(&arrayOfElements[i], &arrayOfElements[j]);
            swap(&cost[i], &cost[j]);  // Keep the cost array in sync with the swaps
        }
    }
    swap(&arrayOfElements[i + 1], &arrayOfElements[high]);
    swap(&cost[i + 1], &cost[high]);  // Keep the cost array in sync with the swaps
    return (i + 1);
}

/**
 * @brief Sorts an array of elements using the quicksort algorithm.
 * It modifies the original array.
 * It also modifies the cost array in sync with the swaps.
 * 
 * @param arrayOfElements Array of elements
 * @param low Index of the first element
 * @param high Index of the last element
 * @param cost Array of costs
*/
void quicksortInPlace(int arrayOfElements[], int low, int high, int cost[]) {
    if (low < high) {
        int pivotIndex = partition(arrayOfElements, low, high, cost);

        quicksortInPlace(arrayOfElements, low, pivotIndex - 1, cost);  // Before pivot
        quicksortInPlace(arrayOfElements, pivotIndex + 1, high, cost); // After pivot
    }
}
