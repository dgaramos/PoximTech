#include <stdio.h> 
#include <stdlib.h>
#include <string.h>

typedef struct package{

   int order;
   char* content;

}package;

void header(){
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("    dMMMMb  .aMMMb  dMP dMP dMP dMMMMMMMMb      dMMMMMMP dMMMMMP .aMMMb  dMP dMP\n");
    printf("   dMP.dMP dMP dMP dMK.dMP amr dMP dMP dMP        dMP   dMP     dMP VMP dMP dMP \n");
    printf("  dMMMMP  dMP dMP .dMMMKK dMP dMP dMP dMP        dMP   dMMMP   dMP     dMMMMMP  \n");
    printf(" dMP     dMP.aMP dMP AMF dMP dMP dMP dMP        dMP   dMP     dMP.aMP dMP dMP   \n");
    printf("dMP      VMMMP  dMP dMP dMP dMP dMP dMP        dMP   dMMMMMP  VMMMP  dMP dMP    \n");
    printf("================================================================================\n");
    printf("Package Organizer 'Irineu'- POI v1.0 \n");
    printf("================================================================================\n");

}

void printSeparator(){
    printf("-=-=-=-=-=-=-=-=-=-=-=-=-=-\n" );
}

void verifyArgs(char **argv){
    if(argv[1] == NULL || argv[2]== NULL){
        printf("No input or output file detected, closing the application...\n\n\n\n"); 
        exit(0);
    }
}
/*void swap(int* a, int* b){
    int t = *a;
    *a = *b;
    *b = t;
}
void heapify(int V[], int i, int n) {
    unsigned int P = i;
    unsigned int E = left(i);
    unsigned int D = right(i);
    if(E < n && V[E] > V[P]) P = E;
    if(D < n && V[D] > V[P]) P = D;
    if(P != i) {
        swap(&V[P], &V[i]);
        heapify(V, P, n);
    }
}

void heapsort(int V[], int n) {
    construir_heap(V, n);
    int i;
    for(i = n - 1; i > 0; i--) {
        swap(&V[0], &V[i]);
        heapify(V, 0, i);
    }
}

*/
int main(int argc, char **argv){
    
    header();

    verifyArgs(argv);

    FILE *fp;
    char buff[255];
    
    //Reading File and scanning the arrays to realize the experiment
    fp = fopen(argv[1], "r");
    fscanf(fp, "%s", buff);

    int n = atof(buff);
    printf("Packages: %d \n", n);
    package packages[n];
    
    fscanf(fp, "%s", buff);
    int packageQuantity = atof(buff);
    //printf("second number: %d \n", packageQuantity);
    printSeparator();

    for ( int i = 0; i < n; i++ ) {
        fscanf(fp, "%s", buff);
        packages[i].order = atof(buff);
        //printf("order of package %d: %d \n", i, packages[i].order);
        
        fscanf(fp, "%s", buff);
        int tmp =  atof(buff);
        //printf("size of package %d: %d \n", i, tmp);

        packages[i].content = malloc((sizeof(char)*tmp*3)+1);

        fscanf(fp, "%s", buff);
        strcpy(packages[i].content, buff);
        strcat(packages[i].content, " ");
        for ( int j = 0; j < tmp-1; j++ ) {
            fscanf(fp, "%s", buff);
            strcat(packages[i].content, buff);
            strcat(packages[i].content, " ");
        }
        printf("%d: %s \n",  packages[i].order, packages[i].content);
    }
    printSeparator();
    fclose(fp);
    
    for(int i = 0; i < n; i++){
        
        free(packages[i].content);
        packages[i].content = NULL;
    }
    printf("ENDING APPLICATION!");
}