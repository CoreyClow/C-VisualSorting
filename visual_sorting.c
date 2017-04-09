/**
program: visual sorting
description: this program utilizes command line overlaying
	to display the visual sorting of an array of random numbers
	as the sorting occurs to compare sorts such as bubble sort,
	insertion sort, selection sort, merge sort, heap sort, quick sort,
	etc.
@author Corey Clow cmc4533@rit.edu
date: April 9th 2017
*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "display.h"//overlay printing

#define INSERTION "insertion"
#define SELECTION "selection"
#define BUBBLE "bubble"
#define MERGE "merge"
#define QUICK "quick"
#define HEAP "heap"

//dimensions of the display
#define WIDTH 140
#define HEIGHT 30

#define BORDER_CHAR '#'
#define CLEAR_CHAR ' '
#define NUMBER_CHAR '@'

//the array of numbers to be sorted in the display
static unsigned char list[WIDTH-2];

static void printList(){
	//cycle through the list
	for(int i = 0; i < WIDTH-2;i++){
		int amountToPrint = list[i];
		int column = 1 + i;
		//print each number in the list visually
		for(int j = 0; j < amountToPrint; j++){
			setCursor(HEIGHT-2-j,column);
			put(NUMBER_CHAR);
		}
	}
}

/**
function: populate
description: this function populates the programs list with random
	numbers to be sorted in the display
*/
static void populateList(){
	
	for(int i = 0; i < WIDTH-2;i++){
		//max the num can be is within the height of the display
		unsigned char num = rand()%(HEIGHT-1);
		list[i]=num;
	}
}

/**
function: border
description: this function prints the border of the display
*/
static void border(){
	for(int i = 0; i < WIDTH; i++){
		//top row
		setCursor(0,i);
		put(BORDER_CHAR);

		//bottom row
		setCursor(HEIGHT-1,i);
		put(BORDER_CHAR);
	}
	for(int j = 0; j < HEIGHT; j++){
		//left column
		setCursor(j,0);
		put(BORDER_CHAR);
		
		//right column
		setCursor(j,WIDTH-1);
		put(BORDER_CHAR);
	}
}

/**
function: usage
description: prints the correct way to run this program
*/
static void usage(){
	printf("Usage: ./visual_sorting [which-sort]\n"\
		"[which-sort]:\t"\
		INSERTION", "SELECTION", "BUBBLE", "MERGE\
		", "QUICK", "HEAP"\n");
}

/**
function: main
description: the main function, main entry way on start
@param argc the number of arguments
@param argv the arguments passed on start of this program
@returns 0 for successful run of program, any number otherwise
*/
int main(int argc, char **argv){
	if(argc==2){
		clear();
		border();
		populateList();
		printList();
		setCursor(HEIGHT,0);//reset cursor below border
		if(strcmp(INSERTION,argv[1])==0){
			
		}
	}else{
		usage();
	}
	return EXIT_SUCCESS;
}
