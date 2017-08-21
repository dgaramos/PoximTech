#include <stdio.h> 
#include <stdlib.h>
#include <string.h>

typedef struct result{
    
        char* code;
        float percentage;
    
}result;


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
    printf("Genetic Sequencing Error Finder - GSEF v1.0 \n");
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

int *compute_prefix_function(char *pattern, int psize)
{
	int k = -1;
	int i = 1;
	int *pi = malloc(sizeof(int)*psize);
	if (!pi)
		return NULL;

	pi[0] = k;
	for (i = 1; i < psize; i++) {
		while (k > -1 && pattern[k+1] != pattern[i])
			k = pi[k];
		if (pattern[i] == pattern[k+1])
			k++;
		pi[i] = k;
	}
	return pi;
}

int kmp(char *target, int tsize, char *pattern, int psize)
{
	int i;
	int *pi = compute_prefix_function(pattern, psize);
	int k = -1;
	if (!pi)
		return -1;
	for (i = 0; i < tsize; i++) {
		while (k > -1 && pattern[k+1] != target[i])
			k = pi[k];
		if (target[i] == pattern[k+1])
			k++;
		if (k == psize - 1) {
			free(pi);
			return i-k;
		}
	}
	free(pi);
	return -1;
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
    
    int sizeCadeia = atoi(buff);

    printf("File %s is being read!\n", argv[1]);
    printf("Tamanho da Cadeia: %d\n", sizeCadeia);
    printSeparator();

    fscanf(fp, "%s", buff);

    char dna[sizeof(buff)/sizeof(buff[0])];

    strcpy(dna,buff);
    printf("Cadeia de DNA: %s\n", dna);

    fscanf(fp, "%s", buff);

    int n = atoi(buff);
    result percentages[n];
    
    printf("Quantidade de doenças: %d\n", n);

    for ( int i = 0; i < n; i++ ) {
        fscanf(fp, "%s", buff);
        percentages[i].code = buff;
        printf("Cadeia de DNA: %s\n", percentages[i].code);
        fscanf(fp, "%s", buff);
        int m = atoi(buff);
        char

    }

    
    fclose(fp);

}