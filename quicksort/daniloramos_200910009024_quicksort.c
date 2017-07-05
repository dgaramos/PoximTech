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

int main(int argc, char **argv){
    
    header();

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
        printf("Elements of the array %d:\n",i+1);
        for ( int j = 0; j < m; j++ ){
            fscanf(fp, "%s", buff);
            arr[j] = atof(buff);
            printf(" %d, %p \n", arr[j], &arr[j]);
        }

    printSeparator(); 
    

    int N = 0;
    //First method
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