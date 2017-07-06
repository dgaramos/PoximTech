#include <stdio.h> 
#include <stdlib.h>
#include <string.h>

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
    //printf("SWAP counter memory address %p\n", counter);
    
    
}
            
//First method (picking the last element as the pivot) 
int normalPartition (int arr[], int first, int last, int* counter){
    int pivot = arr[last];    // pivot
    int i = (first - 1);  // Index of smaller element

    for (int j = first; j <= last- 1; j++){
        // If current element is smaller than or
        // equal to pivot
        if (arr[j] <= pivot){
            i++;    // increment index of smaller element
            //printf("After SWAP1 counter memory address %p\n", counter);
         
            swap(&arr[i], &arr[j], counter);
            
        }
    }
    //printf("After SWAP2 counter memory address %p\n", counter);
    swap(&arr[i + 1], &arr[last], counter);
    
    
    return (i + 1);
}
    
// The main function of the quicksort
void quickSort(int arr[], int first, int last, char type, int* counter){
    
    if (first < last){
         /* pi is partitioning index, arr[p] is now
         at right place */

        int pi; 
        switch (type){
        case 'N':
            //printf("After Partition counter memory address %p\n", counter);
            pi = normalPartition(arr, first, last, counter);
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

    int n = buff[0]-'0';

    printSeparator();
    printf("Arrays to be created: %d\n", n);
    printSeparator();

    for ( int i = 0; i < n; i++ ) {
        fscanf(fp, "%s", buff);
        int m = atof(buff);
        int arr[m];
        int arrTmp[m]; 
        printf("Elements of the array %d:\n",i);
        for ( int j = 0; j < m; j++ ){
            fscanf(fp, "%s", buff);
            arr[j] = atof(buff);
            printf(" %d", arr[j]);
            arrTmp[j] = arr[j];
            
        }
        printf("\n");
        printSeparator();

        int N = 0;
        printf("SWAP counter memory address: %p\n", &N);
        quickSort(arrTmp, 0, m - 1, 'N', &N);
        printf("Elements of the array %d sorted by Normal QuickSort:\n", i);
        
        for ( int j = 0; j < m; j++ ){
            printf(" %d", arrTmp[j]);
            arrTmp[j] = arr[j]; 
        }

        printf("\nSWAP Counter: %d\n", N);

        printSeparator();

        int PP = 0;
        //Second method
        int HP = 0;
        //Third method
        int PM = 0;
        //Fourth method
        int HM = 0;
        //Fifth method
        int HA = 0;
        //Sixth method
        int PA = 0;
        //Seventh method

        printf("%d: N(%d) PP(%d) HP(%d) PM(%d) HM(%d) HA(%d) PA(%d)\n", i, N, PP, HP, PM, HM, HA, PA);
        fprintf(fp2,"%d: N(%d) PP(%d) HP(%d) PM(%d) HM(%d) HA(%d) PA(%d)\n", i, N, PP, HP, PM, HM, HA, PA);
        printSeparator();
    }
    fclose(fp);
    fclose(fp2);
}