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
#include <math.h>//ceil
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
//must be malloced before being used
static unsigned char *list;

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
	delay(DELAY_MICROSEC);
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
			delay(DELAY_MICROSEC);//delay because of comparison
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
function:parent
description: finds the parent in a binary tree array of a given index
@param index the child index
@returns the parent index
*/
static int parent(int index){
	return (int) floor(((float)(index-1))/2.0);
}

/**
function: leftChild
description: returns the left child index of a given index in a binary tree
@param index the index to find left child of
@returns the index of the left child
*/
static int leftChild(int index){
	return (2*index)+1;
}

/**
function: siftDown
description: this function reorganizes a heap after
	a number has been removed from a valid heap and replaced
	with the rightmost member of the heap
@param start the starting index in the program list of the heap
@param end the ending index of the heap in the program list
*/
static void siftDown(int start,int end){
	int currentIndex = start;
	while(leftChild(currentIndex) <= end){
		int leftIndex = leftChild(currentIndex);
		int swapIndex = currentIndex;
		//left child biggest
		if(list[swapIndex]<list[leftIndex]){
			swapIndex= leftIndex;
		}
		//right child biggest
		if(leftIndex+1<=end && list[swapIndex] < list[leftIndex+1]){
			swapIndex = leftIndex+1;
		}
		//parent biggest
		if(swapIndex == currentIndex){
			break;
		}else{
			unsigned char parent =list[currentIndex];
			
			//print the change before it happens
			printChange(currentIndex,list[swapIndex]);
			printChange(swapIndex,parent);

			//swap
			list[currentIndex] = list[swapIndex];
			list[swapIndex] = parent;
	
			//move down the heap
			currentIndex = swapIndex;
		}
	}
}

/**
function: heapify
description: this function reorganizes a heap after an
        element has been added to a valid heap beforehand
@param size the size of the heap in the program list
*/
static void heapify(int size){
        int currentIndex = parent(size-1);//parent of last node
        while(currentIndex >=0){//stop when reach head of heap
                //sift the currentIndex element to proper place
                siftDown(currentIndex,size-1);
                currentIndex--;
        }
}	

/**
function: heap
description: this function utilizes the heap sort algorithm
	to sort the programs list of elements. in other words it removes
	one element from the list at a time and constructs a heap,afterwards
	removing from the heap and placing in the sorted section
*/
static void heap(){
	//build the heap
	heapify(SIZE);
	int endIndex = SIZE-1;
	while(endIndex >0){//stop once you reach the head
		unsigned char head = list[0];
		
		//print the change before it happens
		printChange(0,list[endIndex]);
		printChange(endIndex,head);

		//swap
		list[0]=list[endIndex];
		list[endIndex]=head;

		endIndex--;
		
		//restore the heap
		siftDown(0,endIndex);
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
function: setup
description: this funcion sets up necessary things before beginning
	the sort such as populating the list, clearing the screen, etc.
*/
static void setup(){
	clear();
	//setup the memory in heap
	list = malloc(sizeof(unsigned char)*SIZE);
	populateList();
	printList();
}


/**
function: cleanup
description: this function does the necessary cleanup before exiting the
	program such as freeing any dynamic memory if there is any,
	setting the cursor to below the border etc.
*/
static void cleanup(){
	free(list);
	setCursor(HEIGHT,0);//cursor below display
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
		if(strcmp(INSERTION,argv[1])==0){
			setup();
			insertion();
			cleanup();
		}else if(strcmp(SELECTION,argv[1])==0){
			setup();
			selection();
			cleanup();
		}else if(strcmp(BUBBLE,argv[1])==0){
			setup();
			bubble();
			cleanup();
		}else if(strcmp(HEAP,argv[1])==0){
			setup();
			heap();
			cleanup();
		}else{//argument doesnt match any sorts
			usage();
		}
	}else{
		usage();
	}
	return EXIT_SUCCESS;
}
