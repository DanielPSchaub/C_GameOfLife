/*Daniel Schaub, Sp 2018
*Conway's Game of Life
*Will read in a binary file,
*Construct an 80x40 array to hold 8bits per,
*& Simulate the Game of Life */
//used Dr. Finlayson's bit.c code for test_bit, set_bit, clear_bit functions

#include <stdio.h>
#include <stdlib.h> //for atoi, args to main

#define BIN_SIZE 400
#define COLS 80
#define ROWS 40

//tests bit, and returns 1 if bit = 1, or 0 if not
int test_bit(unsigned char value, int bit_number);

//determines location from 1D array to 2D array AND then returns char to fill board
char isAlive(unsigned char test[], int row, int col);

//essentially Constructor for the 2-D array from the 1-D, then prints it
void populateScreen(unsigned char test[], char screen[][ROWS]);

//Drives the logic, takes the current screen and applies Game Of Life to nextScreen
void populateNextScreen(char screen[][ROWS], char nextScreen[][ROWS]);

//prints out the current screen
void printScreen(char screen[][ROWS]);

//really only for debugging purposes, skips the 2-D array step
//void printTest(unsigned char test[]);

int main(int argc, char** argv)
{
    if(argc != 3){
        printf("Incorrect number of arguments - Exiting\n");
        return 1;
    }
    
    int NUM_GENERATIONS = atoi(argv[2]);

    //Binary File Read-in
    unsigned char test[BIN_SIZE];
    FILE* binFile = fopen(argv[1], "r");
    fread(test, sizeof(unsigned char), BIN_SIZE, binFile);
    fclose(binFile);

    /*
    //Testing Data Retrieval
    isAlive(test,0,19);
    isAlive(test, 0, 20);//should say 1
    isAlive(test,0,23);
    */

    char screen[COLS][ROWS], nextScreen[COLS][ROWS];
    
    //printTest(test); more debugging
    populateScreen(test, screen);

    //print out first time, before the 100 runs
    //printScreen(screen);
    //printf("\n\n");

    //my brililiant plan - this will cut down on needing to physically swap arrays, instead relying on the arguments passed to save effort
    //BUG: only works properly for even number of generations
    int i, j, k;
    for(i = 0; i< NUM_GENERATIONS/2; i++){
        populateNextScreen(screen, nextScreen);
        populateNextScreen(nextScreen, screen);
    }
    printScreen(screen);

    return 0;
}//end main
    
int test_bit(unsigned char value, int bit_number){
    return (value >> bit_number) & 1;
}

char isAlive(unsigned char test[], int row, int col){
    int howManyBits = row*COLS + col;
    int cellNum = howManyBits/8;
    int bitNum = howManyBits%8;
    int bitShift = 7 - bitNum;

    //printf("howManyBits: %d\ncellNum: %d\nbitNum: %d\nbitShift: %d\n",howManyBits,cellNum,bitNum, bitShift);

    //now for bit operations
    int boo = test_bit(test[cellNum], bitShift);
    //printf("after test_bit: %d\n", boo);

    if( boo == 1)
        return 'O';
    else
        return ' ';
}

void populateScreen(unsigned char test[], char screen[][ROWS]){
    int i, j;
    for( j = 0; j < ROWS; j++){
        for( i = 0; i < COLS; i++){
            screen[i][j] = isAlive(test, j, i);
        }
    }
}

//from 2-D array to 2-D array
//when setting the bit - manually change 'char'
void populateNextScreen(char screen[][ROWS], char nextScreen[][ROWS])
{
    int x, y;
    
    /*find number of neighbors
        North neighbor = [x][y-1]   NorthEast = [x+1][y-1]
        South neighbor = [x][y+1]   NorthWest = [x-1][y-1]
        East  neighbor = [x+1][y]   SouthEast = [x+1][y+1]
        West  neighbor = [x-1][y]   SouthWest = [x-1][y+1]
    */
    int neighborCounter;
    for( y = 0; y < ROWS; y++){
        for( x = 0; x < COLS; x++){        
            neighborCounter = 0;

            if(y != 0) //check North
                if( screen[x][y-1] == 'O')
                    neighborCounter++;
            
            if(y != ROWS-1) //check South
                if( screen[x][y+1] == 'O')
                    neighborCounter++;
            
            if(x != 0) //check West
                if( screen[x-1][y] == 'O')
                    neighborCounter++;
            
            if(x != COLS-1) //check East
                if( screen[x+1][y] == 'O')
                    neighborCounter++; 
            
            if(y != 0 && x != 0) //check NorthWest
                if( screen[x-1][y-1] == 'O')
                    neighborCounter++;
            
            if(y != 0 && x != COLS-1) //check NorthEast
                if( screen[x+1][y-1] == 'O')
                    neighborCounter++;
            
            if(y != ROWS-1 && x != 0) //check SouthWest
                if( screen[x-1][y+1] == 'O')
                    neighborCounter++;

            if(y != ROWS-1 && x != COLS-1) //check SouthEast
                if( screen[x+1][y+1] == 'O')
                    neighborCounter++;
        
            //if cell alive, RULES 123 
//DEBUG printf("screen[%d][%d]: %c, neighboorCounter: %d\n", x, y, screen[x][y], neighborCounter);
            if( screen[x][y] == 'O' && neighborCounter >= 2 && neighborCounter <= 3 )
                nextScreen[x][y] = 'O';
            else
                nextScreen[x][y] = ' ';
            
            //if cell dead, RULES 45
            if( screen[x][y] == ' ' && neighborCounter == 3)
                nextScreen[x][y] = 'O';
            if( screen[x][y] == ' ' && neighborCounter != 3)
                nextScreen[x][y] = ' ';
        //DEBUG printf("screen[x][y]: %c", screen[x][y]);
        //DEBUG printf("neighborCounter: %d", neighborCounter);        
        //DEBUG printf("nextScreen: %c\n", nextScreen[x][y]);
        }
    }
//DEBUG printScreen(nextScreen);
}

void printScreen(char screen[][ROWS]){
    int i, j;
    for( j = 0; j < ROWS; j++){
        for( i = 0; i < COLS; i++){
            printf("%c", screen[i][j]);
        }
        printf("\n");
    }
}

/*void printTest(unsigned char test[])
{
    int i, j;
    for(j = 0; j < ROWS; j++){
        for(i = 0; i < COLS; i++){
            printf("%c", isAlive(test, j, i));
        }
        printf("\n");
    }
}*/
