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
#include "delay.h" //delay program execution

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

#define DELAY_MICROSEC 1000

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
		int column =   i;
		//print each number in the list visually
		for(int j = 0; j < amountToPrint; j++){
			setCursor(HEIGHT-1-j,column);
			put(NUMBER_CHAR);
		}
	}
	
}

/**
function: printChange
description: this function will print a change to the list as
	it is being sorted. instead of clearing the screen it will
	only change the bits that are actually affected
@param index the index that changed
@param new the new value
@precondition IMPORTANT - must print change before actually making the change
	in the programs list
*/
static void printChange(int index, unsigned char new){
	unsigned char old = list[index];
	//if the new number is smaller, some must be erased from display
	for(int i = new; i < old; i++){
		setCursor(HEIGHT-1-i,index);
		put(CLEAR_CHAR);
	}

	//if the new number is bigger, new chars must be printed
	for(int i = old; i < new; i++){
		setCursor(HEIGHT-1-i,index);
		put(NUMBER_CHAR);
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
		unsigned char element = list[i];
		int insert = i-1;
		while(insert>=0 && list[insert] > element){
		
			//print the shift before actually shifting
			printChange(insert+1,list[insert]);
	
			//shift elements over
			list[insert+1]=list[insert];
			insert--;
		
			//delay program execution so user can actually see changes
			delay(DELAY_MICROSEC);
		}
		//print the insertion before making the change
		printChange(insert+1,element);

		//insert element in correct place
		list[insert+1]=element;
	}
}

/**
function: selection
description: this function utilizes the selection sort algorithm to sort
	the programs list. in other words it scans the entire unsorted
	section of the list, looks for the smallest, then puts it at the
	end of the the sorted part of the list.
*/
static void selection(){
	//cycle through all elements
	for( int i = 0; i < SIZE;i++){
		unsigned char smallest = list[i];
		int smallestIndex = i;
		//find the smallest
		for(int j = i+1; j < SIZE;j++){
			if(list[j]<smallest){
				smallest=list[j];
				smallestIndex=j;
			}

			//delay execution so user can actually see changes
			delay(DELAY_MICROSEC);
		}

		//only swap if it found a smaller element
		if(smallestIndex!=i){
			//print the changes to list
			printChange(smallestIndex,list[i]);
			printChange(i,smallest);
			
			//swap current and smallest
			list[smallestIndex]=list[i];
			list[i]=smallest;
		}
	}
}

/**
function: bubble
description: this function utilizes the bubble sort algorithm
	to sort the programs list of elements. this means it cycles through
	the list, swapping bigger elements with adjacent smaller elements
	until the list is sorted.
*/
static void bubble(){
	int n = SIZE;
	//while sorted section of array hasnt reached beginning yet
	while(n>0){
		//the index of where sorted section begins
		int m = 0;
		for(int i = 1; i < n; i++){
			if(list[i-1] > list[i]){
				unsigned char current = list[i-1];
				
				//print the swap before actually swapping
				printChange(i-1,list[i]);
				printChange(i,current);
				
				//swap the two elements
				list[i-1]=list[i];
				list[i]=current;
				m=i;
			}
		}
		n=m;//grow sorted section of list
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
		}else if(strcmp(BUBBLE,argv[1])==0){
			bubble();
		}
		setCursor(HEIGHT,0);//set cursor below border
	}else{
		usage();
	}
	return EXIT_SUCCESS;
}
