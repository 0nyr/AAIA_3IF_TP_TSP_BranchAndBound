# Notes de corrections


### Q1: compléter `permut`

Solution possible:

```python
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
    if (nbNotVisited == 0) {
        genTurtleTour(visited, nbVisited);

        // log in terminal
        for (int i = 0; i < nbVisited; i++) {
            printf("%d ", visited[i]);
        }
        printf("0\n");
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
        permut(visited, nbVisited+1, notVisited, nbNotVisited-1);
    
        // backtrack
        notVisited[nbNotVisited-1] = notVisited[i];
        notVisited[i] = tmp;
    }
}
```
