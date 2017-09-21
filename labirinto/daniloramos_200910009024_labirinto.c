#include <stdio.h> 
#include <stdlib.h>
#include <string.h>

typedef int bool;
#define true 1
#define false 0

typedef struct position{
    int width;
    int height;
}position;

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
    
    //space labyrinth [100][100];

    FILE *fp;
    FILE *fp2;
    char buff[100];

    printf("File %s is being read!\n", argv[1]);

    printf("File %s is being written!\n", argv[2]);

    fp = fopen(argv[1], "r");
    fp2 = fopen(argv[2], "w+");
    
    fscanf(fp, "%s", buff);

    int labyrinths = atoi(buff);
    printf("Number of labyrinths: %d\n", labyrinths);
    printSeparator();
    
    for ( int i = 0; i < labyrinths; i++ ) {
    
        position start;

        position end; 
      
        end.height = -1;
        end.width = -1;

        fprintf(fp2, "L%d:\n", i);
        start.width = 0;
        start.height = 0;
        fscanf(fp, "%s", buff);
        int width = atoi(buff);
        printf("Labyrinth width: %d\n", width);
        fscanf(fp, "%s", buff);
        int height = atoi(buff);
        printf("Labyrinth height: %d\n", height);
        char labyrinth[height][width];
        printSeparator();
        for (int j = 0; j < height; j++){
            //printf("%d => ", j);
            for (int k = 0; k < width; k++){
                //printf("%d: ", k);
                fscanf(fp, "%s", buff);
                //printf("%s ",buff);
                labyrinth[j][k] = buff[0];
                if (labyrinth[j][k] == 'X'){
                    //printf("%d, %d: ", k, j);
                    start.width = k;
                    start.height = j;
                    //labyrinth[j][k] = '0';
                    printf("%c ",labyrinth[j][k]);
                }else{
                    printf("%c ",labyrinth[j][k]);
                }

            }
            printf("\n");
        }
        printSeparator();
        printf("first position height: %d \n",start.height);
        printf("first position width: %d \n",start.width);
        printSeparator();
        printf("Placing robot at w:%d h:%d \n",start.width, start.height);
        fprintf(fp2, "INICIO [%d,%d]\n", start.height, start.width);
        position robot;
        robot.width = start.width;
        robot.height = start.height;
        printf("Robot placed at w:%d h:%d \n", robot.width, robot.height);
        printSeparator();

        position previous;
        previous.width = robot.width;
        previous.height = robot.height; 
        
        int steps = 0;
        int steps2 = 0;

        int wayLength = (height-2)*(width-2)+1;

        position way[wayLength];

        while (end.height == -1){

            if (0 <= robot.width+1 && robot.width+1 < width && 0 <= robot.height && robot.height < height && labyrinth[robot.height][robot.width+1]== '0' && (previous.height != robot.height || previous.width != robot.width+1) ){
                
                way[steps].height = robot.height;
                way[steps].width = robot.width;

                steps++;
                steps2++;
                
                fprintf(fp2, "D [%i,%i]->[%i,%i]\n",robot.height,robot.width,robot.height,robot.width+1);
                printf("D [%i,%i]->[%i,%i]\n",robot.height,robot.width,robot.height,robot.width+1);
                
                previous.height = robot.height;
                previous.width = robot.width;

                labyrinth[robot.height][robot.width] = '1';
                robot.height = robot.height;
                robot.width = robot.width+1;
                
            }
            else if (0 <= robot.width && robot.width < width && 0 <= robot.height-1 && robot.height-1 < height && labyrinth[robot.height-1][robot.width]== '0' && (previous.height != robot.height-1 || previous.width != robot.width) ){
                
                way[steps].height = robot.height;
                way[steps].width = robot.width;

                steps++;
                steps2++;

                fprintf(fp2, "F [%i,%i]->[%i,%i]\n",robot.height,robot.width,robot.height-1,robot.width);
                printf("F [%i,%i]->[%i,%i]\n",robot.height,robot.width,robot.height-1,robot.width);
                
                previous.height = robot.height;
                previous.width = robot.width;
                
                labyrinth[robot.height][robot.width] = '1';
                robot.height = robot.height-1;
                robot.width = robot.width;
            }
            else if (0 <= robot.width-1 && robot.width-1 < width && 0 <= robot.height && robot.height < height && labyrinth[robot.height][robot.width-1]== '0' && (previous.height != robot.height || previous.width != robot.width-1) ){

                way[steps].height = robot.height;
                way[steps].width = robot.width;

                steps++;
                steps2++;

                fprintf(fp2, "E [%i,%i]->[%i,%i]\n",robot.height,robot.width,robot.height,robot.width-1);
                printf("E [%i,%i]->[%i,%i]\n",robot.height,robot.width,robot.height,robot.width-1);

                previous.height = robot.height;
                previous.width = robot.width;

                labyrinth[robot.height][robot.width] = '1';
                robot.height = robot.height;
                robot.width = robot.width-1;
            }
            else if (0 <= robot.width && robot.width < width && 0 <= robot.height+1 && robot.height+1 < height && labyrinth[robot.height+1][robot.width]== '0' && (previous.height != robot.height+1 || previous.width != robot.width) ){
                
                way[steps].height = robot.height;
                way[steps].width = robot.width;
                
                steps++;
                steps2++;
                
                fprintf(fp2, "T [%i,%i]->[%i,%i]\n",robot.height,robot.width,robot.height+1,robot.width);
                printf("T [%i,%i]->[%i,%i]\n",robot.height,robot.width,robot.height+1,robot.width);
                
                previous.height = robot.height;
                previous.width = robot.width;

                labyrinth[robot.height][robot.width] = '1';
                robot.height = robot.height+1;
                robot.width = robot.width;
                
            }
            else{

                if(robot.height == start.height && robot.width == start.width){
                    break;
                } else{
                    fprintf(fp2, "BT [%i,%i]<-[%i,%i]\n",previous.height,previous.width, robot.height,robot.width);
                    printf("BT [%i,%i]<-[%i,%i]\n",previous.height,previous.width, robot.height,robot.width);
                }
                
                labyrinth[robot.height][robot.width] = '1';
                robot.height = previous.height;
                robot.width = previous.width;
                
                steps--;
                labyrinth[robot.height][robot.width] = '1';
                previous.height = way[steps-1].height ;
                previous.width = way[steps-1].width;
                
            }

            if((robot.height == 0 || robot.height== height-1) || (robot.width == 0 || robot.width== width-1)){				
                end.height = robot.height;
                end.width = robot.width;
            }
        }

        if (steps2 == 0){

        } else if(end.height == -1 || end.width == -1){
            printf( "SEM SAIDA\n");
            printf( "  steps: %d\n", steps);
            printf( "  steps2: %d\n", steps2);
            fprintf(fp2, "SEM SAIDA\n");

        } else {
            printf( "SAIDA [%i,%i]\n",end.height,end.width);
            fprintf(fp2, "SAIDA [%i,%i]\n",end.height,end.width);
        }
    }
}