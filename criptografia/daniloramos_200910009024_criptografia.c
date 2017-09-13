#include <stdio.h> 
#include <stdlib.h>
#include <string.h>

typedef struct peer{
    char name;
    int key;
}peer;

long long int M = 1103515245;
long long int D = 12345;    
long long int key;

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

unsigned long G(unsigned long k){ 
	static unsigned long int j = 0; 
	if (j == 0){ 
		key = M * key + D;
	} 
	unsigned long z = (key >> j) & 0xFF; 
	j = (j+8) % 32; 
	return z;
}

unsigned long int DHKey(int g,int k,int p){
    unsigned long int t;
    if(k==1){
        return g;
    }
    t = DHKey(g,k/2,p);
    if(k%2==0){
        return (t*t)%p;
    }
    else{
        return (((t*t)%p)*g)%p;
    }
}

int isEven(int i){
    if(i%2==0){
        return 1;
    }else{
        return 0;
    }
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
    

    unsigned long int keyA = DHKey(g, A.key, p);
    printf("A sends to B %d\n", keyA);
    fprintf(fp2, "A->B: %d\n", keyA);
    unsigned long int keyB  = DHKey(g, B.key, p);
    printf("B sends to A %d\n", keyB);
    fprintf(fp2, "B->A: %d\n", keyB);

    printSeparator();

    unsigned long int sA = DHKey(keyB, A.key, p);
    unsigned long int sB = DHKey(keyA, B.key, p);
    printf("s calculated by A: %d\n", sA);
    printf("s calculated by B: %d\n", sB);

    unsigned long int s;

    if (sA==sB){
        s = sA;
        printf("sA and sB are equal so s is: %d\n", s);
    }

    key = s;

    printSeparator();

    fscanf(fp, "%s", buff);
    int nMessages = atoi(buff);
    char arrayMessages[nMessages][1000];
    printf("Number of messages: %d\n", nMessages);
    for (int i = 0; i < nMessages; i++){
        fscanf(fp, "%s", buff);
        strcpy(arrayMessages[i],buff);
        printf("Message number %d: %s\n", i, arrayMessages[i]);

        if(isEven(i)==1){ 
            fprintf(fp2, "A->B: ");
        }else{
            fprintf(fp2, "B->A: ");
        }

        int j = 0;
        unsigned long number;
        while (arrayMessages[i][j] >= 33){
            number = arrayMessages[i][j]^G(s);
            printf("%lu ", number);
            fprintf(fp2,"%lu ", number);
            j++;
        }
        printf("\n");
        fprintf(fp2,"\n");
    }

}