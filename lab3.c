/*Student Name： Huijun Bu
  Student Number: 041121881
  Course Name: CST8234_302 C Language
  Lab Section: 302
  Lab Number: Lab 3
  Professor: Shavit Lupo
  Description: This program is to allow user create a rectangle table,and fill the 
  field with the value designated by user. 
  Due Date: 25, Feb, 2024
  Submission Date: 25, Feb, 2024*/
#include<stdio.h>
#include<stdlib.h>
#include<limits.h>
#define ctrD 3
#define TRUE 0
#define FALSE 1
/** set a enumeration structure to avoid use magic numbers to make the decision of operation on seting row, col and replace.*/
    enum rowOrColumeOperation{
        setRow,
        setCol,
        setColandRow,
        setReplace
    };
/** Set the helper function to free memory*/
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

/**Receiveing a char array address, and col,row as parameter*/
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
            return FALSE;
        }
        /*set all colume to '.'*/
        for(j = 0; j < col;j++){
            (*array)[i][j] ='.';
        }
    }
    return TRUE;
}

/*Helper method: print out the array*/
void printArray(char **array,unsigned int row,unsigned int col){
    int i,j;
    for(i = 0; i < row ; i++){
        for(j = 0; j < col; j++){
            printf("%c",array[i][j]);
        }
        printf("\n");
    }
}

/*recieving a array that include char pointers, row , col and Control variable rowOrColume 
as parameter.*/
int fillRowOrCol(char **array,unsigned int row,unsigned int col,enum rowOrColumeOperation rowOrColume){
    int i,j;
    char fill;
    unsigned int chooseRow;
    unsigned int chooseCol;
    unsigned int quitFill;
    unsigned int quitRow;
    unsigned int quitCol;
    unsigned int quitReplace;
    unsigned int quitSearchValue;

    if(rowOrColume == setRow){/*choose set row*/
        printf("Enter char: ");
        quitFill = scanf(" %c",&fill);
         if ( quitFill == EOF ){
           freeMemory(&array,row);
        }
        while(getchar() != '\n');

        printf("Enter row: ");
        quitRow = scanf(" %u",&chooseRow);
        if ( quitRow == EOF ){
           freeMemory(&array,row);
        }

        if(chooseRow-1 < row && quitRow == FALSE){
            for( i = 0; i < col; i++){
            array[chooseRow-1][i] = fill;
            }
        }else {
                printf("Index out of boundary or invalid input\n");
                while(getchar() != '\n');
                return FALSE; 
        }
    }else if (rowOrColume == setCol){/*choose set colume.*/
            printf("Enter char: ");
            quitFill = scanf(" %c",&fill);
            if ( quitFill == EOF){
                freeMemory(&array,row);
            }
            while(getchar() != '\n');
            printf("Enter colume: ");
            quitCol = scanf(" %u",&chooseCol);

            if ( quitCol == EOF ){
                freeMemory(&array,row);
            }

            if(chooseCol-1 < col && quitCol == FALSE){
                for( i = 0; i < row; i++){
                array[i][chooseCol-1] = fill;
                }
            }else {
                printf("Index out of boundary or invalid input\n");
                while(getchar() != '\n');
                return FALSE; 
            }
    }else if(rowOrColume == setColandRow){
            printf("Enter char: ");
            quitFill = scanf(" %c",&fill);
            if ( quitFill == EOF ){
                freeMemory(&array,row);
            }
            while(getchar() != '\n');
            printf("Enter colume: ");
            quitCol = scanf(" %u",&chooseCol);
            if ( quitCol == EOF ){
                freeMemory(&array,row);
            }
            printf("Enter row: ");
            quitRow = scanf(" %u",&chooseRow);
            if ( quitRow == EOF ){
                freeMemory(&array,row);
            }
            if(chooseCol-1 < col && chooseRow-1 < row && quitCol == FALSE && quitRow == FALSE){              
                array[chooseRow-1][chooseCol-1] = fill;
            }else {
                printf("Index out of boundary or invalid input \n");
                while(getchar() != '\n');
                return FALSE; 
            }

    }else if(rowOrColume == setReplace){
            char replace;
            char searchValue;
            int replaceCount = 0;

            printf("Enter char to replace: ");
            quitSearchValue = scanf(" %c",&searchValue);
            if ( quitSearchValue == EOF ){
                freeMemory(&array,row);
            }
            while(getchar() != '\n');
            printf("Enter new char: ");
            quitReplace = scanf(" %c",&replace);
            if ( quitReplace == EOF ){
                freeMemory(&array,row);
            }
            while(getchar() != '\n');

            for(i = 0; i < row ;i++){
                for(j = 0; j < col; j++){
                    if(array[i][j] == searchValue){
                        array[i][j] = replace;
                        replaceCount++;
                    }
                }
            }
                printf("\nReplaced %d times \n",replaceCount);
           
    }

    return TRUE;
    
}


int main(){

    char **array = NULL;/*Initiate 2D array.*/
    unsigned int col,row,option;
    enum rowOrColumeOperation rowOrColume;/*set row or colume*/
    int quitPoint = 1;
    unsigned int checkCol;
    unsigned int checkRow;
    unsigned int checkOption = 0;/*handle invalid input: scanf can read */
    
        printf("Enter rectangle width: ");
        
        while( (checkCol = scanf("%u",&col)) != 1 || col >= UINT_MAX){
            if ( checkCol == EOF ){
                freeMemory(&array,row);
            }
            printf("(!) Not a number, or out of range (1..%u), try again.\n",UINT_MAX);
            while(getchar() != '\n');
            printf("Enter rectangle width: ");

        }

        printf("Enter rectangle height: ");
        
        while((checkRow = scanf("%u",&row)) != 1 || row >= UINT_MAX){
            if ( checkRow == EOF ){
                freeMemory(&array,row);
            }
            printf("(!) Not a number, or out of range (1..%u), try again.\n",UINT_MAX);
            while(getchar() != '\n');
            printf("Enter rectangle height: ");

        }
        /*prompt the user memory allocation failed*/
        if(allocateCharArray(&array,col,row) == FALSE){
            printf("failed to allocate memory");
            while(getchar() != '\n');
            return FALSE;
        }

        do{          
            printf("1 - Fill Row     | 2 - Fill Column  | 3 - Set Char\n");     
            printf("4 - Replace Char | 5 - Exit \n");    
            checkOption = scanf(" %u",&option);
            
            if(checkOption == EOF){
                freeMemory(&array,row);
            }
            
            switch(option){
                case 1:
                    rowOrColume = setRow;
                    fillRowOrCol(array,row,col,rowOrColume);/*control variable: set value of designated row*/
                    printArray(array,row,col);
                    break;
                case 2:
                    rowOrColume = setCol;/*control variable: set value of designated colume*/
                    fillRowOrCol(array,row,col,rowOrColume);
                    printArray(array,row,col);
                    break;
                case 3:
                    rowOrColume = setColandRow;/*control variable: set value on designaged colume and row.*/
                    fillRowOrCol(array,row,col,rowOrColume);
                    printArray(array,row,col);
                    break;
                case 4:
                    rowOrColume = setReplace;/*control variable: repalce value on designaged element value in array*/
                    fillRowOrCol(array,row,col,rowOrColume);
                    printArray(array,row,col);
                    break;
                case 5:
                    quitPoint = 0;
                    break;
                default:
                    printf("invalid input....\n");
                    while(getchar() != '\n');
            }
           
        }while(quitPoint);

    freeMemory(&array,row);
    return EXIT_SUCCESS;
}
