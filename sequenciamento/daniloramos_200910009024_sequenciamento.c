#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef struct result{
    
        char name[255];
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


int kmp(int tab[], char T[], char P[], int subCad) {
	unsigned int i, n = strlen(T);
	unsigned int m = strlen(P);
	int j = -1, seq=0, acertosValidos=0;
	calcular_tabela(tab, P);
	for(i = 0; i < n; i++) {
        printf("i: %d\n", i);
        printf("T: %c\n",T[i]);
        printf("P: %c\n",P[j+1]);
        
		while(j >= 0 && P[j + 1] != T[i]) {
            j = tab[j];
		}
		
		if(P[j + 1] == T[i]){ 
			j++;
			seq++;
        }
        
		if(j == m - 1) {
			j = tab[j];
			seq=0;
        }
		
        if (seq >= subCad && P[j + 2] != T[i]){
			
			acertosValidos += seq;
			printf("          AV: %i\n",seq);
			printf("          seq: %i\n",seq);
			
			char strTemp[m - seq];
			
			printf("          m-seq: %i\n",m-seq);


			strncpy(strTemp, P+seq, m-seq);	
			
			printf("          strTemp: %s\n",strTemp);
			
			if (seq == m) break;
			
			strcpy(P,strTemp);
			printf("          P: %s\n",strTemp);
			
			calcular_tabela(tab, P);
			m = m - seq;
            

            seq = 0;
			j=-1;
		}
	}
	printf("     Acertos Validos: %i\n",acertosValidos);
	return acertosValidos;
}

float percentual(float acertos, float total){
	return (roundf((acertos/total)*100));
}

//MergeSort submethod to the conquest phase.
void mergeResultArray(result arr[], int l, int m, int r){
    
    int i, j, k;
    int n1 = m - l + 1;
    int n2 =  r - m;

    result L[n1], R[n2];

    //Filling the sub arrays
    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1+ j];

    i = 0; 
    j = 0; 
    k = l;

    while (i < n1 && j < n2){
        if (L[i].percentage <  R[j].percentage){
            arr[k] = R[j];
            j++;
        }else{
            arr[k] = L[i];
            i++;
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
void mergeSortResultArray(result arr[], int l, int r){

    if (l < r){

        int m = l+(r-l)/2;

        //Divide phase's recursion
        mergeSortResultArray(arr, l, m);
        mergeSortResultArray(arr, m+1, r);
 
        //Conquest submethod
        mergeResultArray(arr, l, m, r);
    }
}


//Main method, requires 2 files as args to run.
int main(int argc, char **argv){
    
    int cadeiasAtivas;
    int posicaoDna;
    int matchedStrings;
    int totalCadeias;
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
    printf("Tamanho da sub Cadeia: %d\n", sizeSubString);
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
        
        strcpy(percentages[i].name, buff);
    
        printf("Cadeia de DNA: %s\n", percentages[i].name);
        fscanf(fp, "%s", buff);
        totalCadeias = atoi(buff);
        printf("Numero de genes: %d\n", totalCadeias);
        cadeiasAtivas = 0;
        for ( int j = 0; j < totalCadeias; j++ ) {
            fscanf(fp, "%s", buff);
            int sizeString = strlen(buff);
            printf("cadeia: %s\n", buff);
            printf("tamanho da cadeia: %d\n", sizeString);
            posicaoDna = 0;
            matchedStrings = 0;
            
            int tab[sizeString];

            matchedStrings = kmp(tab, dna, buff, sizeSubString);
            printf("matchedStrings: %d\n", matchedStrings);
            printf("sizeString: %d\n", sizeString);
            printf("%f\n", (float)matchedStrings / (float)sizeString);
            if((float)matchedStrings / (float)sizeString>=0.9){
                printf("a cadeia %s está ativa\n", buff);
                cadeiasAtivas++;
            }
        }
        printf("Acertos: %i\n", cadeiasAtivas);
			
		float perc=0;
		perc = percentual((float)cadeiasAtivas,(float)totalCadeias);
		printf("Probabilidade: %f\n",perc);
		percentages[i].percentage = perc ;
    }

    fclose(fp);

    mergeSortResultArray(percentages, 0, n-1);

    fp = fopen(argv[2], "w+");

    for(int i = 0; i <n; i++){
		fprintf(fp, "%s: %.0f%% \n",percentages[i].name, roundf(percentages[i].percentage));
	}
    
}