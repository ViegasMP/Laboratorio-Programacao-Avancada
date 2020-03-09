#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

int *visitedA;
int *visitedL;
int best=0;

double** le_inputs(int* qtd){
    char info[100],*token;
    double **matrix;
    int i=0;
    fgets(info,100,stdin);
    *qtd=atoi(strtok(info," "));
    matrix = malloc(sizeof(double*)*(*qtd));
    for (i = 0; i < *qtd; i++) {
        matrix[i] = (double*)malloc (2 * sizeof (double));
        fgets(info, 100, stdin);
        token = strtok(info, " ");
        matrix[i][0]=atoi(token);
        token = strtok(NULL, " ");
        matrix[i][1]=atoi(token);
    }
    return matrix;
}

double calculateDistance(double x1,double x2,double y1,double y2){
    double distance =  sqrt(pow(x2 - x1,2) + pow(y2 - y1,2));
    return distance;
}

// A utility function to check if the antenna is doing any favor 
void markAntenna(double **posNewListeners, int nNewListeners, int xAntenna, int yAntenna, int raio) { 
    int i=0;
    double distance=0;
    // if the antenna can't reach any unreached listener return false 
    for(i=0; i < nNewListeners; i++){
        distance = calculateDistance(posNewListeners[i][0], xAntenna, posNewListeners[i][1], yAntenna);
        if (distance <= raio && visitedL[i]== 0){
            visitedL[i]=1;
        }
    }
}

void unmarkAntenna(double **posNewListeners, int nNewListeners, int xAntenna, int yAntenna, int raio) { 
    int i=0;
    double distance=0; 
    for(i=0; i < nNewListeners; i++){
        distance = calculateDistance(posNewListeners[i][0], xAntenna, posNewListeners[i][1], yAntenna);
        if (distance <= raio){
            visitedL[i]=0;
        }
    }
}

int btAlgorithm(double **posNewListeners, double **posAntennas, int nNewListeners, int nAntennasPos, int n) { 
    int i=0;
    int mod=0;
    // if every listener is visited return true
    for(i=0; i < nNewListeners; i++){
        if (visitedL[i]== 1){
            mod++;
        } else {
            break;
        }
    } 
    if (mod == nNewListeners) { 
        return 1; 
    }
    
    printf("Listeners:\n"); 
    for(i=0; i < nNewListeners; i++){
        printf("%d\n", visitedL[i]);
    }
    printf("\n");

    printf("Antennas:\n");
    for(i=0; i < nAntennasPos; i++){
        printf("%d\n", visitedA[i]);
    }
    printf("\n");
  
    // Check if maze[x][y] is valid 
    if (n < nAntennasPos && mod != nNewListeners) { 
        // mark antenna x as visited
        visitedA[n] = 1; 
        printf("Antennas no if:\n");
        for(i=0; i < nAntennasPos; i++){
            printf("%d\n", visitedA[i]);
        }
        markAntenna(posNewListeners, nNewListeners, posAntennas[n][0], posAntennas[n][1], 1);
        // analyse next antenna
        printf("Antennas depois de marcar:\n");
        for(i=0; i < nAntennasPos; i++){
            printf("%d\n", visitedA[i]);
        }
        if (btAlgorithm(posNewListeners, posAntennas, nNewListeners, nAntennasPos, n+1) == 1) 
            return 1; 
  
        // If none of the above movements work then BACKTRACK: unmark antenna x as visited 
        visitedA[x] = 0;
        unmarkAntenna(posNewListeners, nNewListeners, posAntennas[n][0], posAntennas[n][1], 1); 
    }
  
    return 0; 
} 

void findSolution(double **posNewListeners, double **posAntennas, double **infoAntennasTypes, int nNewListeners, int nAntennasPos, int nAntennasTypes) { 
    int i=0;
    printf("aqui!!\n");
    if (btAlgorithm(posNewListeners, posAntennas, nNewListeners, nAntennasPos, 0) == 0) { 
        printf("no solution\n"); 
    } 
    else{
        printf("Solution:\n");
        for(i=0; i < nNewListeners; i++){
            printf("%d\n", visitedL[i]);
        }
    } 
}


int main() {
    
    int nNewListeners, nAntennasPos, nAntennasTypes;
    double **posNewListeners, **posAntennas, **infoAntennasTypes;
    
    posNewListeners= le_inputs(&nNewListeners);
    posAntennas = le_inputs(&nAntennasPos);
    infoAntennasTypes = le_inputs(&nAntennasTypes);

    visitedA = malloc(sizeof(int)*nAntennasTypes);
    visitedL = malloc(sizeof(int)*nNewListeners);

    findSolution(posNewListeners, posAntennas, infoAntennasTypes, nNewListeners, nAntennasPos, nAntennasTypes);

    /*
    int i;
    printf("pos new listeners:\n");
    for (i=0; i<nNewListeners; i++){
        printf("%d %d\n",posNewListeners[i][0], posNewListeners[i][1]);
    }
    printf("possible pos antennas:\n");
    for (i=0; i<nAntennasPos; i++){
        printf("%d %d\n",posAntennas[i][0], posAntennas[i][1]);
    }
    printf("info antennas:\n");
    for (i=0; i<nAntennasTypes; i++){
        printf("%d %d\n",infoAntennasTypes[i][0], infoAntennasTypes[i][1]);
    }
    */
   free(posNewListeners);
   free(posAntennas);
   free(infoAntennasTypes);
   free(visitedA);
   free(visitedL);

    return 0;
}
