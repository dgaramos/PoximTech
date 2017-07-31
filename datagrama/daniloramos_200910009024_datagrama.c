#include <stdio.h> 
#include <stdlib.h>
#include <string.h>

typedef struct Payload{

   int order;
   char* content;

}Payload;

#define SWAP(arr, a, b) \
  do { \
    Payload tmp = arr[a]; \
    arr[a] = arr[b]; \
    arr[b] = tmp; \
  } while (0)

int total;
void heapify(Payload arr[], int i){
    int lft = i * 2;
    int rgt = lft + 1;
    int grt = i;

    if (lft <= total && arr[lft].order > arr[grt].order){
        grt = lft;
    }
    if (rgt <= total && arr[rgt].order > arr[grt].order){
        grt = rgt; 
    }
    if (grt != i) {
        SWAP(arr, i, grt);
        heapify(arr, grt);
    }
}

void sort(Payload arr[], int size){
    total = size - 1;

    for (int i = total / 2; i >= 0; i--)
        heapify(arr, i);

    for (int i = total; i > 0; i--) {
        SWAP(arr, 0, i);
        total--;
        heapify(arr, 0);
    }
}


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
    printf("Payload Organizer 'Irineu'- POI v1.0 \n");
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


int main(int argc, char **argv){
    
    header();

    verifyArgs(argv);

    FILE *fp;
    char buff[255];
    
    //Reading File and scanning the arrays to realize the experiment
    fp = fopen(argv[1], "r");
    fscanf(fp, "%s", buff);

    int n = atof(buff);
    printf("Payloads: %d \n", n);
    Payload payloads[n];
    
    fscanf(fp, "%s", buff);
    int payloadQuantity = atof(buff);
    //printf("second number: %d \n", payloadQuantity);
    printSeparator();

    for ( int i = 0; i < n; i++ ) {
        fscanf(fp, "%s", buff);
        payloads[i].order = atof(buff);
        //printf("order of payload %d: %d \n", i, payloads[i].order);
        
        fscanf(fp, "%s", buff);
        int tmp =  atof(buff);
        //printf("size of payload %d: %d \n", i, tmp);

        payloads[i].content = malloc((sizeof(char)*tmp*3)+1);

        fscanf(fp, "%s", buff);
        strcpy(payloads[i].content, buff);
        strcat(payloads[i].content, " ");
        for ( int j = 0; j < tmp-1; j++ ) {
            fscanf(fp, "%s", buff);
            strcat(payloads[i].content, buff);
            strcat(payloads[i].content, " ");
        }
        
        printf("%d: %s \n",  payloads[i].order, payloads[i].content);
    }
    printSeparator();
    fclose(fp);

    
    fp = fopen(argv[2], "w+");
    int index = 0;
    int i = 0;
    
    while(i<n){
        fprintf(fp,"%d: ", index);
        for (int j = 0; j < payloadQuantity; j++){
            if (i == payloads[i].order){
                fprintf(fp,"%s", payloads[i].content);
                i++;
            }
        }
        fprintf(fp,"\n");
        int k = 0;
        if(i != payloads[i].order){
            sort(payloads, i+1);
            k++;
        }   
        index++;
    }   
    
    for(int i = 0; i < n; i++){
        printf("%d: %s \n",  payloads[i].order, payloads[i].content);
    }
     for(int i = 0; i < n; i++){
        free(payloads[i].content);
        payloads[i].content = NULL;
    }
    fclose(fp);
    printf("ENDING APPLICATION!");
}