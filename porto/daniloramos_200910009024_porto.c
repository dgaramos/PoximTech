#include <stdio.h> 
#include <stdlib.h>
#include <string.h>

typedef struct container{

   char code[12];
   char cnpj[19];
   float weight;

}container;

typedef struct containerDiff{

    char code[12];
    char cnpjDiff[40];
    float weightDiff;
    float percentageDiff;

}containerDiff;

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
    printf("Containers Audit System 'Muito Fácil'- CASMF v1.0 \n");
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

//MergeSort submethod to the conquest phase.
void mergeContainerArray(container arr[], int l, int m, int r){
    
    int i, j, k;
    int n1 = m - l + 1;
    int n2 =  r - m;

    container L[n1], R[n2];

    //Filling the sub arrays
    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1+ j];

    i = 0; 
    j = 0; 
    k = l;

    char* end;

    while (i < n1 && j < n2){

        //Compare phase using the container codes converted to long long
        if (strtoll(L[i].code, &end ,36) <= strtoll(R[j].code, &end ,36)){
            arr[k] = L[i];
            i++;
        }else{
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    //Merging what remains of the left subarray
    while (i < n1){
        arr[k] = L[i];
        i++;
        k++;
    }
    
    //Merging what remains of the right subarray
    while (j < n2){
        arr[k] = R[j];
        j++;
        k++;
    }
}

//MergeSort main method, recursive implementation
void mergeSortContainerArray(container arr[], int l, int r){

    if (l < r){

        int m = l+(r-l)/2;

        //Divide phase's recursion
        mergeSortContainerArray(arr, l, m);
        mergeSortContainerArray(arr, m+1, r);
 
        //Conquest submethod
        mergeContainerArray(arr, l, m, r);
    }
}

//Binary Search based container diference finder.
containerDiff searchContainerDiff(container arr[], int l, int r, container x){
    
    containerDiff diff;

    if (r >= l){
        char* end;
        int mid = l + (r - l)/2;

        // Finding the element
        if (strtoll(x.code, &end ,36) == strtoll(arr[mid].code, &end ,36)){
            if(strcmp(x.cnpj, arr[mid].cnpj) != 0){

                strcpy(diff.code, arr[mid].code);
                strcpy(diff.cnpjDiff, x.cnpj);
                strcat(diff.cnpjDiff, "<->");
                strcat(diff.cnpjDiff, arr[mid].cnpj);

                diff.weightDiff = 0;
                
                return diff;

            }else if(arr[mid].weight != x.weight){

                strcpy(diff.code, arr[mid].code);
                diff.weightDiff = arr[mid].weight - x.weight;
                diff.percentageDiff = (arr[mid].weight / x.weight) * 100.0;

                return diff;
            }
            /*If the container is has no diference between the containers, returns a 
            container with "nodiff" as cnpjDiff and 0 as weight diff*/
            strcpy(diff.code, arr[mid].code);
            strcpy(diff.cnpjDiff, "noDiff");
            diff.weightDiff = -1;
            diff.percentageDiff = 0;
            return diff;
        }  
        if (strtoll(arr[mid].code, &end ,36) > strtoll(x.code, &end ,36)){
            return searchContainerDiff(arr, l, mid-1, x);
        } 

        return searchContainerDiff(arr, mid+1, r, x);
    }
    
    /*If the container is not found in the list of audited containers, returns a 
      container with "notFound" as cnpjDiff and -1 as weight diff*/
    strcpy(diff.cnpjDiff, "notFound");
    diff.weightDiff = -1;
    diff.percentageDiff = 0;
    
    return diff;
}

//Main method, requires 2 files as args to run.
int main(int argc, char **argv){
    
    header();

    //Verifying if there is two arguments.
    verifyArgs(argv);

    FILE *fp;
    char buff[255];
    
    //Reading File and scanning the size of the first array of elements
    fp = fopen(argv[1], "r");
    fscanf(fp, "%s", buff);

    int n = atof(buff);
    container containerList[n];
    printf("File %s is being read!\n", argv[1]);
    printf("Container Quantity: %d\n", n);
    printSeparator();

    //Populating array with file information about the Containers of the first list
    for ( int i = 0; i < n; i++ ) {

        fscanf(fp, "%s", buff);
        strcpy(containerList[i].code,buff);
        printf("Container Code : %s\n", containerList[i].code );

        char* end;
        printf("Container Code on int: %lld\n", strtoll(containerList[i].code, &end ,36));


        fscanf(fp, "%s", buff);
        strcpy(containerList[i].cnpj, buff);
        printf("Container Buyer's CNPJ : %s\n", containerList[i].cnpj );

        fscanf(fp, "%s", buff);
        containerList[i].weight = atof(buff);
        printf("Container's Weight : %.3f\n", containerList[i].weight );
        printSeparator();
    }

    //Checking the size of array
    printf("Number of Container elements on array: %lu\n", sizeof(containerList)/sizeof(containerList[0]));
    printSeparator();

    //Reading File and scanning the size of the second array of elements (Containers to be audited)
    fscanf(fp, "%s", buff);

    int m = atof(buff);
    container containerAudit[m];
    printf("Containers to Audition: %d\n", m);
    printSeparator();
    
    //Populating array with file information about the Containers of the second list
    for ( int i = 0; i < m; i++ ) {

        fscanf(fp, "%s", buff);
        strcpy(containerAudit[i].code,buff);
        printf("Container Code : %s\n", containerAudit[i].code );

        char * end;
        printf("Container Code on int: %lld\n", strtoll(containerAudit[i].code, &end ,36));

        fscanf(fp, "%s", buff);
        strcpy(containerAudit[i].cnpj, buff);
        printf("Container Buyer's CNPJ : %s\n", containerAudit[i].cnpj );

        fscanf(fp, "%s", buff);
        containerAudit[i].weight = atof(buff);
        printf("Container's Weight : %.3f\n", containerAudit[i].weight );

        printSeparator();

    }
    //Checking the size of array
    printf("Number of Containers registered to audition on array: %lu\n", sizeof(containerAudit)/sizeof(containerAudit[0]));
    printSeparator();
    fclose(fp);

    //Sorting containerAudit so the containers can be found more easily via binary search.
    mergeSortContainerArray(containerAudit, 0, m-1);

    printf("File %s was read succesfully!\n", argv[1]);
    printf("Starting Diff verification!\n");
    printf("Printing found Container Differences...\n");
    printf("File %s is being written in the following order: \n", argv[2]);
    printSeparator();

    containerDiff diffList[m];
    containerDiff diff;

    int j = 0;
    int k = m;
    fp = fopen(argv[2], "w+");

    for (int i = 0; i < n; i++) {
        /*Searching and checking diferences between the supposed
          weight and CNPJ of the owner of the container and what was measured*/
        diff = searchContainerDiff(containerAudit, 0, (m - 1), containerList[i]);
        
        if(diff.weightDiff > -1){
            
            if(diff.weightDiff == 0){
                printf("Container Code: %s\n", diff.code);
                printf("Container CNPJ diff: %s\n", diff.cnpjDiff);

                //Printing on file
                fprintf(fp,"%s: ", diff.code);
                fprintf(fp, "%s\n" ,diff.cnpjDiff);

                printSeparator();
            }else{
                diffList[j] = diff;
                j++;
            }
        }
        k--; 
        if (k == 0){
            break;
        }
    }
    for ( int i = 0; i < j; i++ ) {
        printf("Container Code: %s\n", diffList[i].code);
        printf("Container Weight Diff: %.fkg\n", diffList[i].weightDiff);
        printf("Container Weight Percentage Diff: %1.f%% \n", diffList[i].percentageDiff);

        printSeparator();

        //Printing on file
        if(diffList[i].percentageDiff > 100){
            diffList[i].percentageDiff = diffList[i].percentageDiff - 100;
        }else{
            diffList[i].percentageDiff = 100 - diffList[i].percentageDiff;
        }

        if(diffList[i].percentageDiff > 10) {
            fprintf(fp,"%s: ", diffList[i].code);
            fprintf(fp, "%.f (%2.f%%)\n", diffList[i].weightDiff, diffList[i].percentageDiff);
        }else {
            printf("WARNING!\nThe container with code %s has weight diference minor\nthan 10%%, so it is not gonna be printed on file.\n", diffList[i].code);
            printSeparator();
        }

    }

    printf("File %s was written succesfully!\n", argv[2]); 
    printf("Closing application...\n");  
    printSeparator();
    fclose(fp);
}