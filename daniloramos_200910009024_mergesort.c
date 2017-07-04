#include <stdio.h> 
#include <stdlib.h>
#include <string.h>

typedef struct container{

   int order;
   char code[12];
   char cnpj[19];
   float weight;

}container;

typedef struct containerDiff{

    int order;
    char code[12];
    char cnpjDiff[40];
    float weightDiff;
    float percentageDiff;
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

void printSeparator(){
    printf("-=-=-=-=-=-=-=-=-=-=-=-=-=-\n" );
}

// Merges two subarrays of arr[].
// First subarray is arr[l..m]
// Second subarray is arr[m+1..r]
void mergeContainerList(container arr[], int l, int m, int r)
{
    int i, j, k;
    int n1 = m - l + 1;
    int n2 =  r - m;
 
    /* creating sub arrays */
    container L[n1], R[n2];
 
    /* Populating sub arrays L[] and R[] */
    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1+ j];
 
    /* Merging the sub arrays back into arr[l..r]*/
    i = 0; 
    j = 0; 
    k = l;

    char* end;

    while (i < n1 && j < n2)
    {
         printf(" %s || %s\n", L[i].code, R[j].code );

        if (strtoll(L[i].code, &end ,36) <= strtoll(R[j].code, &end ,36))
        {
            printSeparator();
            printf(" %s <= %s\n", L[i].code, R[j].code );
            arr[k] = L[i];
            printSeparator();
            printf("Container %d :\n", k);
            printf("Container Code : %s\n", arr[k].code );
            printf("Container Code on int: %lld\n", strtoll(arr[k].code, &end ,36));
            printf("Container Buyer's CNPJ : %s\n", arr[k].cnpj );
            printf("Container's Weight : %.3f\n", arr[k].weight );
            i++;
        }
        else
        {
            printSeparator();
            printf(" %s > %s\n", L[i].code, R[j].code );
            arr[k] = R[j];
            printSeparator();
            printf("Container %d : \n", k );
            printf("Container Code : %s\n", arr[k].code );
            printf("Container Code on int: %lld\n", strtoll(arr[k].code, &end ,36));
            printf("Container Buyer's CNPJ : %s\n", arr[k].cnpj );
            printf("Container's Weight : %.3f\n", arr[k].weight );
            j++;
        }
        k++;
    }
 
    /* Copy the remaining elements of L[], if there are any */
    while (i < n1)
    {
        arr[k] = L[i];
        i++;
        k++;
    }
 
    /* Copy the remaining elements of R[], if there are any */
    while (j < n2)
    {
        arr[k] = R[j];
        j++;
        k++;
    }
}
 

/* l is for left index and r is right index of the
   subarray of arr */
void mergeSortContainerList(container arr[], int l, int r)
{
    if (l < r)
    {
        // Same as (l+r)/2, but avoids overflow in case of large l and h
        int m = l+(r-l)/2;
 
        // Calling mergeSort for splitted subarrays
        mergeSortContainerList(arr, l, m);
        mergeSortContainerList(arr, m+1, r);
 
        mergeContainerList(arr, l, m, r);
        printSeparator();
    }
}

// Merges two subarrays of arr[].
// First subarray is arr[l..m]
// Second subarray is arr[m+1..r]
void mergeContainerDiff(containerDiff arr[], int l, int m, int r)
{
    int i, j, k;
    int n1 = m - l + 1;
    int n2 =  r - m;
 
    /* creating sub arrays */
    containerDiff L[n1], R[n2];
 
    /* Populating sub arrays L[] and R[] */
    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1+ j];
 
    /* Merging the sub arrays back into arr[l..r]*/
    i = 0; 
    j = 0; 
    k = l;

    char* end;

    while (i < n1 && j < n2)
    {
         printf(" %s || %s\n", L[i].order, R[j].order );

        if (L[i].order <= R[j].order)
        {
            printSeparator();
            printf(" %s <= %s\n", L[i].order, R[j].order );
            arr[k] = L[i];
            printSeparator();
            printf("Container %d :\n", k);
            /*printf("Container Order: %d\n", arr.order);
            printf("Container Code: %s\n", arr.code);
            printf("Container CNPJ diff: %s\n", arr.cnpjDiff);
            printf("Container Weight Diff: %f\n", arr.weightDiff);
            printf("Container Weight Percentage Diff: %f\n", arr.percentageDiff);*/
            i++;
        }
        else
        {
            printSeparator();
            printf(" %s > %s\n", L[i].order, R[j].order );
            arr[k] = R[j];
            printSeparator();
            /*printf("Container %d : \n", k );
            printf("Container Order: %d\n", arr.order);
            printf("Container Code: %s\n", arr.code);
            printf("Container CNPJ diff: %s\n", arr.cnpjDiff);
            printf("Container Weight Diff: %f\n", arr.weightDiff);
            printf("Container Weight Percentage Diff: %f\n", arr.percentageDiff);*/
            j++;
        }
        k++;
    }
 
    /* Copy the remaining elements of L[], if there are any */
    while (i < n1)
    {
        arr[k] = L[i];
        i++;
        k++;
    }
 
    /* Copy the remaining elements of R[], if there are any */
    while (j < n2)
    {
        arr[k] = R[j];
        j++;
        k++;
    }
}
 

/* l is for left index and r is right index of the
   subarray of arr */
void mergeSortContainerDiff(containerDiff arr[], int l, int r)
{
    if (l < r)
    {
        // Same as (l+r)/2, but avoids overflow in case of large l and h
        int m = l+(r-l)/2;
 
        // Calling mergeSort for splitted subarrays
        mergeSortContainerDiff(arr, l, m);
        mergeSortContainerDiff(arr, m+1, r);
 
        mergeContainerDiff(arr, l, m, r);
        printSeparator();
    }
}


containerDiff binarySearch(container arr[], int l, int r, container x, containerDiff diff){
    
    if (r >= l)
    {
        char* end;
        int mid = l + (r - l)/2;
        
        // Finding the element
        if (strtoll(arr[mid].code, &end ,36) == strtoll(x.code, &end ,36)){
            if(strcmp(arr[mid].cnpj, x.cnpj) != 0){

                diff.order = arr[mid].order;
                strcpy(diff.code, arr[mid].code);
                strcpy(diff.cnpjDiff, arr[mid].cnpj);
                strcat(diff.cnpjDiff, "<->");
                strcat(diff.cnpjDiff, x.cnpj);
                diff.weightDiff = 0;
                printf("Container Order: %d\n", diff.order);
                printf("Container Code: %s\n", diff.code);
                printf("Container CNPJ diff: %s\n", diff.cnpjDiff);
                printSeparator();

            }else if(arr[mid].weight != x.weight){

                diff.order = arr[mid].order;
                strcpy(diff.code, arr[mid].code);
                diff.weightDiff = x.weight - arr[mid].weight;
                diff.percentageDiff = (x.weight/ arr[mid].weight) * 100.0;
                printf("Container Order: %d\n", diff.order);
                printf("Container Code: %s\n", diff.code);
                printf("Container Weight Diff: %f\n", diff.weightDiff);
                printf("Container Weight Percentage Diff: %f\n", diff.percentageDiff);
                printSeparator();

            }
            
        }  

        if (strtoll(arr[mid].code, &end ,36) > strtoll(x.code, &end ,36)) return binarySearch(arr, l, mid-1, x, diff);

        return binarySearch(arr, mid+1, r, x, diff);
    }
    diff.order = 0;
}



int main(int argc, char **argv){
    
    header();

    FILE *fp;
    char buff[255];
    
    //Reading File and scanning the size of the first array of elements
    fp = fopen(argv[1], "r");
    fscanf(fp, "%s", buff);

    int n = buff[0]-'0';
    container containerList[n];
    printf("Container Quantity: %d\n", n);
    printSeparator();

    //Populating array with file information about the Containers of the first list
    for ( int i = 0; i < n; i++ ) {

        containerList[i].order = i+1;
        printf("Container Order: %d\n", containerList[i].order);

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

    n = buff[0]-'0';
    container containerAudit[n];
    printf("Containers to Audition: %d\n", n);
    printSeparator();
    
    //Populating array with file information about the Containers of the second list
    for ( int i = 0; i < n; i++ ) {

        containerAudit[i].order = 0;
        printf("Container Order: %d\n", containerAudit[i].order);

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

    n = sizeof(containerList)/sizeof(containerList[0]);

    mergeSortContainerList(containerList, 0, n-1);
    printSeparator();

    printf("AAAAA\n");
    for ( int i = 0; i < n; i++ ) {
        
        printf("Container Order: %d\n", containerList[i].order);
        printf("Container Code : %s\n", containerList[i].code );

        char* end;
        printf("Container Code on int: %lld\n", strtoll(containerList[i].code, &end ,36));

        printf("Container Buyer's CNPJ : %s\n", containerList[i].cnpj );

        printf("Container's Weight : %.3f\n", containerList[i].weight );
        printSeparator();
         
    }

    n = sizeof(containerAudit)/sizeof(containerAudit[0]);
    

    printf("Container Diffs\n");
    printSeparator();

    containerDiff diffList[n];
    containerDiff diff;

    for ( int i = 0; i < n-1; i++ ) {
        binarySearch(containerList, 0, (sizeof(containerList)/sizeof(containerList[0]) - 1), containerAudit[i], diff);
        if(diff.order != 0){
            strcpy(diffList[i].cnpjDiff, diff.cnpjDiff);
            diffList[i].order = diff.order;
            strcpy(diffList[i].code, diff.code);
            diffList[i].weightDiff = diff.weightDiff;
            diffList[i].percentageDiff = diff.percentageDiff;
            printf("Container Order: %d\n", diffList.order);
            printf("Container Code: %s\n", diffList.code);
            printf("Container CNPJ diff: %s\n", diffList.cnpjDiff);
            printf("Container Weight Diff: %f\n", diffList.weightDiff);
            printf("Container Weight Percentage Diff: %f\n", diffList.percentageDiff);
            
        }
    }

    n = sizeof(diffList)/sizeof(diffList[0]);
    //mergeSortContainerDiff(diffList, 0, n-1);

    for ( int i = 0; i < n; i++ ) {
 
       
        char* end;
        printf("Container Code on int: %lld\n", strtoll(diffList[i].code, &end ,36));

        
        printSeparator();
         
    }
}