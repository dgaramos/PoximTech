#include <stdio.h> 
#include <stdlib.h>
#include <string.h>

typedef struct container{

   int order;
   char code[11];
   char cnpj[18];
   float weight;

}container;

typedef struct containerDiff{

    int order;
    char code[11];
    char cnpjDiff[18];
    float weightDiff;
    int percentageDiff;
}containerDiff;

void header(){
    printf("    dMMMMb  .aMMMb  dMP dMP dMP dMMMMMMMMb      dMMMMMMP dMMMMMP .aMMMb  dMP dMP\n");
    printf("   dMP.dMP dMP dMP dMK.dMP amr dMP dMP dMP        dMP   dMP     dMP VMP dMP dMP \n");
    printf("  dMMMMP  dMP dMP .dMMMKK dMP dMP dMP dMP        dMP   dMMMP   dMP     dMMMMMP  \n");
    printf(" dMP     dMP.aMP dMP AMF dMP dMP dMP dMP        dMP   dMP     dMP.aMP dMP dMP   \n");
    printf("dMP      VMMMP  dMP dMP dMP dMP dMP dMP        dMP   dMMMMMP  VMMMP  dMP dMP    \n");
    printf("================================================================================\n");
    printf("Containers Audit System 'Muito Fácil'- CASMF v1.0 \n");
    printf("================================================================================\n");

}

void separator(){
    printf("-=-=-=-=-=-=-=-=-=-=-=-=-=-\n" );
}

int main(){
    
    header();

    FILE *fp;
    char buff[255];
    
    //Reading File and scanning the size of the first array of elements
    fp = fopen("containerList.txt", "r");
    fscanf(fp, "%s", buff);

    int n = buff[0]-'0';
    container containerList[n];
    printf("Container Quantity: %d\n", n);
    separator();

    //Populating array with file information about the Containers of the first list
    for ( int i = 0; i < n; i++ ) {

        containerList[i].order = i+1;
        printf("Container Order: %d\n", containerList[i].order);

        fscanf(fp, "%s", buff);
        strcpy(containerList[i].code,buff);
        printf("Container Code : %s\n", containerList[i].code );

        fscanf(fp, "%s", buff);
        strcpy(containerList[i].cnpj, buff);
        printf("Buyer's CNPJ : %s\n", containerList[i].cnpj );

        fscanf(fp, "%s", buff);
        containerList[i].weight = atof(buff);
        printf("Weight : %.3f\n", containerList[i].weight );
        separator();
    }

    //Checking the size of array
    printf("Container Elements read on array: %lu\n", (int) sizeof(containerList)/sizeof(containerList[0]));
    separator();

    //Reading File and scanning the size of the second array of elements (Containers to be audited)
    fscanf(fp, "%s", buff);

    n = buff[0]-'0';
    container containerAudit[n];
    printf("Containers to Audition: %d\n", n);
    separator();
    
    //Populating array with file information about the Containers of the second list
    for ( int i = 0; i < n; i++ ) {

        fscanf(fp, "%s", buff);
        strcpy(containerList[i].code,buff);
        printf("Container Code : %s\n", containerList[i].code );

        fscanf(fp, "%s", buff);
        strcpy(containerList[i].cnpj, buff);
        printf("Buyer's CNPJ : %s\n", containerList[i].cnpj );

        fscanf(fp, "%s", buff);
        containerList[i].weight = atof(buff);
        printf("Weight : %.3f\n", containerList[i].weight );

        separator();

    }
    //Checking the size of array
    printf("Container Elements read on array: %lu\n", (int) sizeof(containerAudit)/sizeof(containerAudit[0]));
    separator();

    fclose(fp);
}