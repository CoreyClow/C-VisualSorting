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





/**
function: usage
description: prints the correct way to run this program
*/
static void usage(){
	printf("Usage: ./visual_sorting <which-sort>\n"\
		"<which-sort>:\t"\
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
		if(strcmp(INSERTION,argv[1])==0){
			printf("worked\n");
		}
	}else{
		usage();
	}
	return EXIT_SUCCESS;
}
