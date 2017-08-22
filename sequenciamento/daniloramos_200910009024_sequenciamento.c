#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
#include <math.h>

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

void inicializar(int tab[], int tamanho){
	int i;
	for( i = 0; i < tamanho; i++){
		tab[i] = -1;
	}
}

void calcular_tabela(int tab[], char P[]) {
	unsigned int i, m = strlen(P);
	int j = -1;
	inicializar(tab, m);
	for(i = 1; i < m; i++) {
		while(j >= 0 && P[j + 1] != P[i])
			j = tab[j];
		if(P[j + 1] == P[i])
			j++;
		tab[i] = j;
	}
}

int kmp(int tab[], char T[], char P[], int tSubCad) {
	unsigned int i, n = strlen(T);
	unsigned int m = strlen(P);
	int j = -1, totalAcertos = 0, seq = 0;
	calcular_tabela(tab, P);
	for(i = 0; i < n; i++) {
		
		if(seq >= tSubCad){
			break;
		}
		
		while(j >= 0 && P[j + 1] != T[i]){
			totalAcertos += seq; seq++;
			j = tab[j];
			seq = 0;
		}
		
		if(P[j + 1] == T[i]){
			j++;
			seq++; printf("          seq parcial: %i\n", seq);
		}
		
		if(j == m - 1) {
			j = tab[j];			
			totalAcertos += seq; break;
		}
	}
	printf("          totalAcertos: %i\n", totalAcertos);
	return totalAcertos;
}

float percentual(float acertos, float total){
	return (roundf((acertos/total)*100));
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
    
    int sizeSubString = atoi(buff);

    printf("File %s is being read!\n", argv[1]);
    printf("Tamanho da Cadeia: %d\n", sizeSubString);
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
        int totalCadeias = atoi(buff);
        int cadeiasAtivas = 0;
        int matchedStrings;
        for ( int j = 0; j < totalCadeias; j++ ) {
            fscanf(fp, "%s", buff);
            int sizeString = strlen(buff);

            int tab[sizeString];

            int posicaoDna = 0;
			matchedStrings = 0;

            matchedStrings = kmp(tab, dna, percentages[i].code, sizeSubString);

            if((matchedStrings / sizeString)>=0.9)
				matchedStrings++;
		}
        printf("Acertos: %i\n", matchedStrings);
			
		float perc=0;
		perc = percentual((float)matchedStrings,(float)totalCadeias);
		printf("Probabilidade: %f\n",perc);
		percentages[i].percentage = perc ;
    }
  
    fclose(fp);

}