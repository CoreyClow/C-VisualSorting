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

#define SIZE (WIDTH)
#define MAX (HEIGHT)

#define CLEAR_CHAR ' '
#define NUMBER_CHAR '@'

//the array of numbers to be sorted in the display
static unsigned char list[SIZE];

/**
function: printList
description: this function prints the list visually within the display
*/
static void printList(){
	/*
	printf("\n[");
	for(int i = 0; i < SIZE; i++){
		printf("%d, ",list[i]);
	}
	printf("]\n");
	*/
	
	clear();
	//cycle through the list
	for(int i = 0; i < SIZE;i++){
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
function: insertion
description: this function is used to sort the programs list using insertion-sort
	meaning it cycles through the list, grabs the first unsorted element,
	and inserts it into the correct place in the sorted part of the list
*/
static void insertion(){
	//cycle through all elements
	for(int i = 1; i < SIZE; i++){
		int element = list[i];
		int insert = i-1;
		while(insert>=0 && list[insert] > element){
			//shift elements over
			list[insert+1]=list[insert];
			insert--;
		}
		//insert element in correct place
		list[insert+1]=element;

		//print the list after change
		printList();	
	}
}

static void selection(){
	//cycle through all elements
	for( int i = 0; i < SIZE;i++){
		int smallest = list[i];
		int smallestIndex = i;
		//find the smallest
		for(int j = i+1; j < SIZE;j++){
			if(list[j]<smallest){
				smallest=list[j];
				smallestIndex=j;
			}
		}
		//swap current and smallest
		list[smallestIndex]=list[i];
		list[i]=smallest;
		
		//print the list after change
		printList();
	}
}

/**
function: populate
description: this function populates the programs list with random
	numbers to be sorted in the display
*/
static void populateList(){
	
	for(int i = 0; i < SIZE;i++){
		//max the num can be is within the height of the display
		unsigned char num = rand()%(MAX+1);
		list[i]=num;
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
		populateList();
		printList();
		if(strcmp(INSERTION,argv[1])==0){
			insertion();	
		}else if(strcmp(SELECTION,argv[1])==0){
			selection();
		}
		setCursor(HEIGHT,0);//set cursor below border
	}else{
		usage();
	}
	return EXIT_SUCCESS;
}
