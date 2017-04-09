/**
set of functions to allow command prompt overlaying

@author Corey Clow 

*/

#include <stdio.h>
#include "display.h"


void clear(){
	printf( "\033[2J" );
	fflush( stdout );

}

void put(char c){
        putchar( c );
        fflush( stdout );

}

void setCursor(int row, int col){
        printf( "\033[%d;%dH", row+1, col+1 );
}

void clearWithin(int row, int col, int width, int height){
	for(int i = row; i <row+ height;i++){
		for(int j = col; j < col+width; j++){
			setCursor(i,j);
			put(' ');
		}
	}
}


void printBorder(int row, int col, int width, int height){

        //top and bottom lines
	for(int i = col; i < col+width;i++){
                setCursor(row,i);
                put(BORDER_CHARACTER);
                setCursor(row+height-1,i);
                put(BORDER_CHARACTER);
        }
	//left and right lines
        for(int i = row; i < row+height; i++){
                setCursor(i,col);
                put(BORDER_CHARACTER);
                setCursor(i,col+width-1);
                put(BORDER_CHARACTER);
        }
}

void clearSpot(int row, int col){
	setCursor(row,col);
	put(' ');
}
