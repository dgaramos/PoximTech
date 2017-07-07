#include <stdio.h> 
#include <stdlib.h>
#include <string.h>

typedef struct evaluation{

   char type[3];
   int counter;

}evaluation;

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
    printf("Quicksort Evaluation Experiment 'Esse É O Bom'- Q4EOB v1.0 \n");
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

void swap(int* a, int* b, int* counter){
    int t = *a;
    *a = *b;
    *b = t;
    *counter = *counter + 1;
    
    printf("Counter %d\n", *counter);
    //printf("SWAP counter memory address %p\n", counter);
    
    
}
            
//Normal method (picking the last element as the pivot) 
int normalPartition (int arr[], int first, int last, int type, int* counter){
    
    switch(type){
            case 1:
            
            break;
            case 2:{
                int ar[3];
                int tmp;
                ar[0] = arr[(last+1)/4];
                ar[1] = arr[(last+1)/2];
                if (ar[1] < ar[0]){
                    ar[2] = ar[0];
                    ar[0] = ar[1];
                    ar[1] = ar[2];
                }
                ar[2] = arr[3*(last+1)/4];
                if(ar[2] < ar[0]){
                    swap(&arr[(last+1)/4], &arr[last] , counter); 
                } else if(ar[2]<ar[1]){
                    swap(&arr[3*(last+1)/4], &arr[last] , counter);
                }
                swap(&arr[(last+1)/2], &arr[last] , counter);
            }
            break;
            case 3:
                swap(&arr[last], &arr[first + (abs(arr[first])%(last+1))], counter);
            break;
    }

    int pivot = arr[last]; 

    int i = (first - 1);

    for (int j = first; j <= last- 1; j++){
        if (arr[j] <= pivot){
            i++; 
            //printf("After SWAP1 counter memory address %p\n", counter);
            swap(&arr[i], &arr[j], counter);
        }
    }
    //printf("After SWAP2 counter memory address %p\n", counter);
    swap(&arr[i + 1], &arr[last], counter);
    return (i + 1);
}
    
// The main function of the quicksort
void quickSort(int arr[], int first, int last, int type, int* counter){
    *counter = *counter + 1;
    printf("Counter %d\n", *counter);

    if (first < last){

        int pi; 

        switch(type){
            case 1 ... 3:
                pi = normalPartition(arr, first, last, type, counter);
            break;
            default:
                printf("No valid option has been chosen, closing the application...\n");
                exit(0);

        }
            
        // Separately sort elements before
        // partition and after partition
        quickSort(arr, first, pi - 1, type, counter);
        
        quickSort(arr, pi + 1, last, type, counter);
        
    }
}

int main(int argc, char **argv){
    
    header();

    verifyArgs(argv);

    FILE *fp;
    FILE *fp2;
    char buff[255];
    
    //Reading File and scanning the arrays to realize the experiment
    fp = fopen(argv[1], "r");
    fscanf(fp, "%s", buff);

    fp2 = fopen(argv[2], "w+");

    int n = atof(buff);

    evaluation grid[7][n];

    printSeparator();
    printf("Arrays to be created: %d\n", n);
    printSeparator();

    for ( int i = 0; i < n; i++ ) {
        fscanf(fp, "%s", buff);
        int m = atof(buff);
        grid[0][i].counter = m;
        strcpy(grid[0][i].type, "N");
        int arr[m];
        int arrTmp[m]; 
        printf("Elements of the array %d:\n",i);
        for ( int j = 0; j < m; j++ ){
            fscanf(fp, "%s", buff);
            arr[j] = atof(buff);
            printf("%d ", arr[j]);
            arrTmp[j] = arr[j];
            
        }
        printf("\n");
        printSeparator();

        

        //First method
        int sortVariation = 1;

        strcpy(grid[sortVariation][i].type, "PP");
        grid[sortVariation][i].counter = 0;

        printf("SWAP and calls counter memory address: %p\n", &grid[sortVariation][i].counter);
        printSeparator();
        quickSort(arrTmp, 0, m - 1, sortVariation, &grid[sortVariation][i].counter);
        printf("Elements of the array %d sorted by Normal QuickSort:\n", i);
        for ( int j = 0; j < m; j++ ){
            printf("%d ", arrTmp[j]);
            arrTmp[j] = arr[j]; 
        }
        printf("\nSWAP and calls Counter: %d\n", grid[sortVariation][i].counter);
        printSeparator();

        //Second method
        sortVariation = 2;
        strcpy(grid[sortVariation][i].type, "PM");
        grid[sortVariation][i].counter  = 0;

        printf("SWAP and calls counter memory address: %p\n", &grid[sortVariation][i].counter);
        printSeparator();
        quickSort(arrTmp, 0, m - 1, 2, &grid[sortVariation][i].counter);
        printf("Elements of the array %d sorted by Median Quicksort:\n", i);
        for ( int j = 0; j < m; j++ ){
            printf("%d ", arrTmp[j]);
            arrTmp[j] = arr[j]; 
        }
        printf("\nSWAP and calls Counter: %d\n", grid[sortVariation][i].counter);
        printSeparator();

        while(grid[sortVariation][i].counter < grid[sortVariation-1][i].counter){
            evaluation tmp = grid[sortVariation-1][i];
            grid[sortVariation-1][i] = grid[sortVariation][i];
            grid[sortVariation][i] = tmp;
            sortVariation--;
        }      

        //Third method
        sortVariation = 3;

        strcpy(grid[sortVariation][i].type, "PA");
        grid[sortVariation][i].counter  = 0;

        printf("SWAP and calls counter memory address: %p\n", &grid[sortVariation][i].counter);
        printSeparator();
        quickSort(arrTmp, 0, m - 1, sortVariation, &grid[sortVariation][i].counter);
        printf("Elements of the array %d sorted by Random QuickSort:\n", i);
        for ( int j = 0; j < m; j++ ){
            printf("%d ", arrTmp[j]);
            arrTmp[j] = arr[j]; 
        }
        printf("\nSWAP and calls Counter: %d\n", grid[sortVariation][i].counter);
        printSeparator();
        
        while(grid[sortVariation][i].counter < grid[sortVariation-1][i].counter){
            evaluation tmp = grid[sortVariation-1][i];
            grid[sortVariation-1][i] = grid[sortVariation][i];
            grid[sortVariation][i] = tmp;
            sortVariation--;
        }   

        //Fourth method
        sortVariation = 4;

        strcpy(grid[sortVariation][i].type, "HP");
        grid[sortVariation][i].counter  = 0;

        /*printf("SWAP and calls counter memory address: %p\n", &grid[sortVariation][i].counter);
        printSeparator();
        quickSort(arrTmp, 0, m - 1, sortVariation, &grid[sortVariation][i].counter);
        printf("Elements of the array %d sorted by Normal QuickSort:\n", i);
        for ( int j = 0; j < m; j++ ){
            printf("%d ", arrTmp[j]);
            arrTmp[j] = arr[j]; 
        }
        printf("\nSWAP and calls Counter: %d\n", grid[sortVariation][i].counter);
        printSeparator();
        
        while(grid[sortVariation][i].counter < grid[sortVariation-1][i].counter){
            evaluation tmp = grid[sortVariation-1][i];
            grid[sortVariation-1][i] = grid[sortVariation][i];
            grid[sortVariation][i] = tmp;
            sortVariation--;
        }   */

        //Fifth method
        strcpy(grid[5][i].type, "HM");
        grid[5][i].counter  = 0;
        //Sixth method
        strcpy(grid[6][i].type, "HA");
        grid[6][i].counter  = 0;

        printf("%d: %s(%d) %s(%d) %s(%d) %s(%d) %s(%d) %s(%d) %s(%d)\n", i, grid[0][i].type, grid[0][i].counter, 
        grid[1][i].type, grid[1][i].counter, grid[2][i].type, grid[2][i].counter, grid[3][i].type, grid[3][i].counter, 
        grid[4][i].type, grid[4][i].counter, grid[5][i].type, grid[5][i].counter, grid[6][i].type, grid[6][i].counter);
        fprintf(fp2,"%d: %s(%d) %s(%d) %s(%d) %s(%d) %s(%d) %s(%d) %s(%d)\n", i, grid[0][i].type, grid[0][i].counter, 
        grid[1][i].type, grid[1][i].counter, grid[2][i].type, grid[2][i].counter, grid[3][i].type, grid[3][i].counter, 
        grid[4][i].type, grid[4][i].counter, grid[5][i].type, grid[5][i].counter, grid[6][i].type, grid[6][i].counter);
        printSeparator();
    }
    fclose(fp);
    fclose(fp2);
}