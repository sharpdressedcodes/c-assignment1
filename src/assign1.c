/****************************************************************************
* COSC2138/CPT 220 - Programming Principles 2A
* Study Period 1  2014 Assignment #1 - Different Applications
* Full Name        : EDIT HERE
* Student Number   : EDIT HERE
* Start up code provided by the C-TEACH team
****************************************************************************/

#include "assign1.h"

/* This source file contains important functions to be developed and
 * used by various menu options, as indicated. Note that every
 * function has as its first parameter the optionsStats array, which
 * will be appropriately updated for later reporting of menu option 6.
 * You may ignore this parameter and its relevance to each function
 * until you develop the sessionSummary() function.
 */

int main(void)
{
   int optionStats[NUM_OPTION_STATS];

   /* Delete this comment and insert your code here. */

   return EXIT_SUCCESS;
}

/* Function fibonacciNumbers
* This function prompts the user for a positive integer N. The first N 
* integers of the Fibonacci sequence are printed in a simple tabular format. 
* Additionally, the sum and average of these numbers are printed.
 This function will be used in menu option 1.
*/
void fibonacciNumbers(int *optionStats)
{
}

/*
* Function phoneNumbers() A function that translates an alphabetic phone number into numeric form.This is menu option number 2
*/
void phoneNumbers(int *optionStats)
{
  
}

/*
Function firstLastStrings(). This function that finds the "first" and "last" words in a series of words. After the user enters the words, the function will determine which words would come first and last if the words were listed in dictionary order. The function must stop accepting input when the user enters a blank line, eg. just presses enter. Assume that no word is more than 20 letters long. An interactive session with the function might look like this:
This is menu option number 3 */

void firstLastStrings(int *optionStats)
{
}

/*
* Function substrings() Many search engines (such as Google), implement "stopping" so that commonly occurring query words are ignored for the purposes of ranking query results. In this option, you will need to prompt the user for a string of 1-20 characters. You will need to output the string with all words of length 1-3 characters "stopped".
This is menu option number 4 
*/

void wordStopping(int *optionStats)
{
  
}

/* Function rookAndTheBishop() A rook can only move either horizontally or vertically. 
A bishop can only move diagonally.
 * menu option 5.
 */
void rookAndTheBishop(int *optionStats)
{
}


/* See requirement #7  "Session summary" of the assignment specs.
 * Function sessionSummary() reports the program usage.
 */
void sessionSummary(int *optionStats)
{
}

/*
* Function readRestOfLine() is used for buffer clearing. Source: 
*/

void readRestOfLine()
{
   int c;

   /* Read until the end of the line or end-of-file. */   
   while ((c = fgetc(stdin)) != '\n' && c != EOF)
      ;

   /* Clear the error and end-of-file flags. */
   clearerr(stdin);
}





