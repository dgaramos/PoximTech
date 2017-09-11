#include <stdio.h> 
#include <stdlib.h>
#include <string.h>

typedef struct peer{
    char name;
    int key;
}peer;

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
    printf("\n");
    printf("================================================================================\n");

}

void verifyArgs(char **argv){
    if(argv[1] == NULL || argv[2]== NULL){
    printf("No input or output file detected, closing the application...\n\n\n\n");
    exit(0);
    }
}

void printSeparator(){
    printf("-=-=-=-=-=-=-=-=-=-=-=-=-=-\n" );
}

//Main method, requires 2 files as args to run.
int main(int argc, char **argv){

    header();
    
    //Verifying if there is two arguments.
    verifyArgs(argv);

    FILE *fp;
    FILE *fp2;
    char buff[100];

    printf("File %s is being read!\n", argv[1]);

    printf("File %s is being written!\n", argv[2]);

    fp = fopen(argv[1], "r");
    fp2 = fopen(argv[2], "w+");

    int M = 1103515245;
    int D = 12345;    

    peer A;

    fscanf(fp, "%s", buff);
    A.name = buff[0];
    fscanf(fp, "%s", buff);
    A.key = atoi(buff);
    
    peer B;

    fscanf(fp, "%s", buff);
    B.name = buff[0];
    fscanf(fp, "%s", buff);
    B.key = atoi(buff);

    char DH[3];

    fscanf(fp, "%s", &DH);

    int p;
    fscanf(fp, "%s", buff);
    p = atoi(buff);
    int g;
    fscanf(fp, "%s", buff);
    g = atoi(buff);
    



}