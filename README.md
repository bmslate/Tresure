/*Student Name： Huijun Bu
  Student Number: 041121881
  Course Name: CST8234_302 C Language
  Lab Section: 302
  Lab Number: Assignment 1
  Professor: Shavit Lupo
  Description: This program is to allow user create a rectangle table,and fill the 
  field with the value designated by user. 
  Due Date: 25, Feb, 2024
  Submission Date: 25, Feb, 2024*/
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<ctype.h>
#include<string.h>
#define ctrD 3
#define LOM 4
#define TRUE 0
#define FALSE 1
    /*create a structure of treasure*/
    struct Treasure{
        char treasureCode[5];
        unsigned int treasureRow;
        unsigned int treasureCol;
    };
    /*free array memory function*/
    void freeMemory(char ***array, unsigned int row){
    unsigned int i;
    if (array != NULL && *array != NULL) {
        for (i = 0; i < row; i++) {
            free((*array)[i]); /*free memory of row*/
        }
        free(*array); /*free memory of array*/
    }
    printf("\nEOF detected. Program terminated.\n");
    exit(ctrD);
    }

    /**Receiveing a char 2D array memory array, and col,row as parameter*/
    int allocateCharArray(char ***array,unsigned int col,unsigned int row){
        int i,j;

        if (col == 0 || row == 0) {
            return FALSE;
        }

        *array = (char **)malloc(row * sizeof(char*));
        if(*array == NULL){
            return FALSE;
        }

        for(i = 0; i< row; i++){
            (*array)[i] = (char *)malloc(col * sizeof(char));
            if((*array)[i] == NULL){/*if memmory is not enough */
                while(i > 0){
                    free((*array)[--i]);/*free the colume memory which has already allocated.*/
                }
                free(*array);/*free the allocated width memory of rectangle.*/
                return FALSE;/*exit(LOM);*/
            }
             /*set all colume to ' '*/
            for(j = 0; j < col;j++){
                (*array)[i][j] =' ';
            }
            
        }
        return TRUE;
    }
    /*print method*/
    void printMap(char **array,unsigned int col,unsigned int row){
        int i,j,k;
        printf("   ");
        for(k = 0; k < col; k++){
             printf("%d",k);
            }
        printf("\n");

        for(i = 0; i < row ; i++){
            printf("%d |",i);
            for(j = 0; j < col; j++){
                printf("%c",array[i][j]);
            }
            printf("\n");
        }
    }
    /*Ceck the treasure code format  and assign a location randomly.*/
    void TreasureFormatAndLocation(char **array,struct Treasure *treasure,unsigned int row,unsigned int col,unsigned int treasureNumber){
        int inputCheck;
        int treasureCount = 0;
        int i;
      
            while(treasureCount < treasureNumber){
                printf("Enter treasure #%d code (e.g. T001): ",treasureCount+1);/*prompt user treasure code format and the code number of their input.*/
                
                inputCheck = scanf("%s",treasure[treasureCount].treasureCode);
                if(inputCheck == EOF){
                    free(treasure);
                    freeMemory(&array,row); 
                    exit(ctrD);
                }
                /*checking the treasure code*/
                if( inputCheck == 1 && treasure[treasureCount].treasureCode[0] == 'T' && 
                    strlen(treasure[treasureCount].treasureCode) == 4 && 
                    isdigit(treasure[treasureCount].treasureCode[1]) &&
                    isdigit(treasure[treasureCount].treasureCode[2]) &&
                    isdigit(treasure[treasureCount].treasureCode[3])){
                    int Exist = 0;
                    for(i = 0; i < treasureCount;i++){
                        if(strcmp(treasure[i].treasureCode, treasure[treasureCount].treasureCode) == 0){/*compare the treasure if it is already exsit.*/
                            Exist = 1;
                            break;/*break "for" loop.*/
                        }
                    }

                    if(Exist){
                        printf("The treasure code are already exist...\n");
                        continue;/*skip the remaining code and start the next iteration of loop.*/
                    }
                    treasure[treasureCount].treasureRow =  rand()%(row);/*set x coordinate randomly*/
                    treasure[treasureCount].treasureCol =  rand()%(col);/*set y coordinate randomly*/
                    treasureCount++;              
                }else{/*bad input branch*/
                    printf("The Treasure code must be started at T and followed 3 digits \n");
                    while(getchar() != '\n');
                }
                                
            }
    }
    /*dig function*/
    void dig(char **array,unsigned int treasureNumber,struct Treasure *treasure,int cheat,unsigned int row,unsigned col,int *foundCount){
        
        int continueLoop = 1;
        int found = 0;
        do{
            int checkX;
            int checkY;
            int x = 0;
            int y = 0;
            
            if(cheat == FALSE ){/*Normal mode entry point*/
                printf("Where would you like to dig?\n");
                printf("X = ");
                checkX = scanf("%d",&x);
                if ( checkX == EOF){
                    freeMemory(&array,row);
                    free(treasure);
                    exit(ctrD);
                }
                while(getchar() != '\n');
                printf("Y = ");
                checkY = scanf("%d",&y);
                if ( checkY == EOF){
                    free(treasure);
                    freeMemory(&array,row);
                    exit(ctrD);
                }
                while(getchar() != '\n');

                /*Good input check branch */
                if( checkX == 1 && checkY == 1 && x < row && y < col ){
                    int i;
                    if(array[x][y] == '$'){/* Condition 1: check treasure if it already have been dug.*/
                        printf("The treasure was already dug from that place\n");
                        found = 1;/* setting a variable to mark this spot*/
                        continueLoop = 0;/*break while loop*/
                    }else if(array[x][y] == 'x'){/* Condition 2: check the spot if it already have been dug*/
                        printf("The place was already dug\n");
                        found = 1;/* setting a variable to mark this spot*/
                        continueLoop = 0;/*break while loop*/
                    }else{                  
                        for(i = 0; i < treasureNumber; i++ ){/*if the above two conditions passed, and there is a treasure on the designated spot, print '$' on it.*/
                            if( treasure[i].treasureRow == x && treasure[i].treasureCol == y){/*compare the treasure coordinate with user's input*/
                                printf("Congratulations! You found a treasure (code: %s)\n",treasure[i].treasureCode);
                                array[x][y] = '$';
                                (*foundCount)++;/*increament the value of 'foundCount',so that it will drive the program to exit successfully*/
                                found = 1;/* setting a variable to mark this spot*/
                                break; /*break this loop*/                          
                            }
                        }
                    }

                    if(found != 1){ /*if it passed the above condition, print a 'x' on designated spot */                          
                        array[x][y] = 'x';
                        printf("You found nothing there..\n");
                        continueLoop = 0;
                    }

                    if(*foundCount == treasureNumber ){/*If found all treasure,program exit successfully*/
                        printf("Congratulations! You found all treasures..\n");
                        free(treasure);
                        freeMemory(&array,row);
                        exit(EXIT_SUCCESS);
                    }
                /*bad input check branch */
                }else{/* If the type of value of x and y is not as same as the program expected*/
                    printf("invalid input\n");
                    while(getchar() != '\n');
                }
            }else{/*cheat mode entry point*/
                int i;
                for(i = 0; i < treasureNumber; i++ ){
                        if(array[treasure[i].treasureRow][treasure[i].treasureCol] == '$'){/*if the spot already have been found, do not change the charactor '$'!*/
                            continue;/*skip the remaining code of this iteration*/
                        }else{
                            array[treasure[i].treasureRow][treasure[i].treasureCol] = '!';/*if the spot are not found in previouse dug, print a '!' on the spot*/
                            continueLoop = 0;
                        }
                }
            }
        }while(continueLoop);   
    }

    int main(){

        unsigned int treasureNumber;
        int numberCheck,cheat;
        int foundCount = 0;/*Count the treasure have been found*/
        int loopControl = 1;/*menu loop control variable*/
        struct Treasure *treasure = NULL;/*initiate a treasure structure pointer*/

        char **array = NULL;/*Initiate 2D array.*/
        unsigned int col,row,quitTreasure,option,checkOption;
        unsigned int checkCol;
        unsigned int checkRow;

        srand(time(0));  

        printf("Enter map width: ");       
        while( (checkCol = scanf("%u",&col)) != 1 || col < 2 || col > 32){
            if ( checkCol == EOF ){
                freeMemory(&array,row);
                exit(ctrD);/*exit status 3*/
            }
            printf("(!) Not a number, or out of range (2..32), try again.\n");
            while(getchar() != '\n');
            printf("Enter map width: ");
        }

        printf("Enter map height: ");        
        while((checkRow = scanf("%u",&row)) != 1 || row < 2 || row > 32){
            if ( checkRow == EOF ){
                freeMemory(&array,row);/*free array memeory*/
                exit(ctrD);/*exit status 3*/
            }
            printf("(!) Not a number, or out of range (1..32), try again.\n");
            while(getchar() != '\n');
            printf("Enter map height: ");
        }

        /*prompt the user memory allocation failed*/
        if(allocateCharArray(&array,col,row) == FALSE){
            printf("failed to allocate memory");
            while(getchar() != '\n');
            exit(LOM);/*lack of memory for allocation. Exit status 4.*/
        }

        do{/* while loop to continue asking user to input a valid number of value*/
            printf("Enter number of treasures to add: ");
            numberCheck = scanf("%u",&treasureNumber);/*check the if the number of treasure is valid*/

            if(numberCheck == EOF){
                free(treasure);/*free treasure memeory*/
                freeMemory(&array,row);/*free array memeory*/
                exit(ctrD);/*exit status 3*/
            }
      
            quitTreasure = TRUE;/*control variable*/
            if(numberCheck == 1 && treasureNumber <= (row * col)/ 4 && treasureNumber >= 1){
                treasure = (struct Treasure *)malloc(treasureNumber * sizeof(struct Treasure));/*Dynamically allcate treature memory*/
                TreasureFormatAndLocation(array,treasure,row,col,treasureNumber);/*initiate treasure.*/            
            }else{
                printf("Please input a integer and The treasure number should not exceed maximum limits which is 1/4 of total area of the map.");
                while(getchar() != '\n');
                quitTreasure = FALSE;
            }
        }while(quitTreasure);/*Treasure number loop ending point*/

        do{/*Menu loop starting point*/           
            printf("1 - Dig at a spot  | 2 - Exit Game      | 3 - Cheat! \n");
            checkOption = scanf("%u", &option);

            if(checkOption == EOF){/*quit point*/
                while(getchar() != '\n');
                free(treasure);/*free treasure memory*/
                freeMemory(&array,row);/*free array memeory*/
                exit(ctrD);
            }

            switch(option){
                case 1:/*normal mode*/
                    printMap(array,col,row);
                    cheat = FALSE;
                    dig(array,treasureNumber,treasure,cheat,row,col,&foundCount);
                    break;
                case 2:/*exit point*/
                    free(treasure);/*free treasure memory*/
                    freeMemory(&array,row);/*free array memeory*/
                    exit(EXIT_SUCCESS);
                    break;
                case 3:/*cheating mode*/
                    cheat = TRUE;
                    printf("Cheat mode already enabled\n");
                    dig(array,treasureNumber,treasure,cheat,row,col,&foundCount);
                    printf("1 - Dig at a spot  | 2 - Exit Game      | 3 - Cheat! \n");
                    printf("cheat -> ");
                    checkOption = scanf("%u", &option);

                    if(checkOption == EOF){
                        free(treasure);/*free treasure memory*/
                        freeMemory(&array,row);/*free array memeory*/
                        exit(ctrD);
                    }
                    if(option == 1){
                        printMap(array,col,row);
                        while(getchar() != '\n');
                        free(treasure);/*free treasure memory*/
                        freeMemory(&array,row);/*free array memeory*/
                        exit(EXIT_SUCCESS);
                    }else{
                        while(getchar() != '\n');
                        free(treasure);
                        freeMemory(&array,row);/*free treasure memory*/
                        exit(EXIT_SUCCESS);/*free array memeory*/
                    }
            }
        }while(loopControl);/*Menu loop ending point*/

        free(treasure);
        freeMemory(&array,row);
        exit(EXIT_SUCCESS);

    }
