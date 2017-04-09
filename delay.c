/**
the function definition for delaying program execution
@author Corey Clow
*/
#include "delay.h"

void delay(unsigned int microsec){
	//multiple by 1000 because it expects microseconds not milli
	clock_t goal = (microsec) + clock();
	while (goal > clock());
}
