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

### Q2: calcul de longueur des circuits hamiltoniens

Dans cette étape, on modifie `createCost` pour qu'elle renvoie un `int**`, la matrice des coûts.

On peut alors fournir cette matrice à `permut` en modifiant ses paramètres. On ajoute alors dans la scope du `if` le code suivant:

```c
// compute and display cost
        int totalCost = 0;
        for (int i = 0; i < nbVisited-1; i++) {
            totalCost += cost[visited[i]][visited[i+1]];
        }
        totalCost += cost[visited[nbVisited-1]][visited[0]];
        printf(" cost: %d\n", totalCost);
```

Ce code permet de calculer et d'afficher la valeur du chemin.

### Q3: Recherche du plus court circuit hamiltonien

*Comparez ces temps d’exécution à ceux du programme utilisant un principe de programmation dynamique.*

TODO: Répondre
