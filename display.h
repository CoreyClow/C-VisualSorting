/**
set of functions to enable display overlaying
@author Corey Clow
*/

#ifndef DISPLAY_H
#define DISPLAY_H

#define BORDER_CHARACTER '#'

/**
clears the command prompt completely
*/
void clear();

/**
places a character to the current cursor location

@param c the character to print
*/
void put(char c);

/**
sets the cursor to the specified row and column
row and col are 0 based

@param row the row to set cursor to
@param col the col to set cursor to
*/
void setCursor(int row, int col);

/**
clears a given section of the command prompt only
by overwriting with a space
*/
void clearWithin(int row, int col, int width, int height);

/**
function: printBorder
description: prints a border symbolizing the edge of the viewing screen
*/
void printBorder(int row, int col, int width, int height);

/**
clears a single spot on the command prompt
*/
void clearSpot(int row, int col);

#endif
