/****************************************************************************
* COSC2138 / CPT220- Assignment #1
* Programming Principles 2A/Programming Techniques
* Author           : <insert name here>
* Student Number   : <insert student number here>
* Start up code provided by the C-Teach team
****************************************************************************/

/* Header files. */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Constants. */
#define NUM_OPTION_STATS 6

/* This is used to compensate for the extra character spaces taken up by the '\n' and '\0' when user is asked for input through fgets(). */
#define EXTRA_SPACES 2

/* Specifies the maximum input length a user can enter for the options
   menu. */
#define MAX_OPTION_INPUT 1

/* Boolean constants. */
/*
#define TRUE 1
#define FALSE 0
*/

typedef enum {
    FALSE = 0,
    TRUE = 1
} BOOLEAN;

typedef BOOLEAN bool;

typedef struct keypad_t {
    int digit;
    const char *code;
} keypad_t;

#define MAX_KEYPAD 10

#define STRING_MAX_SMALL 256
#define STRING_MAX 1024

#define ERROR_MEMORY "Error: memory allocation failed.\0"
#define MIN_OPTION_FIBONACCI 1
#define MAX_OPTION_FIBONACCI 40
#define FIBONACCI_NUM1 0
#define FIBONACCI_NUM2 1

/* Function prototypes. */
void fibonacciNumbers(int *);
void phoneNumbers(int *);
void firstLastStrings(int *);
void wordStopping(int *);
void rookAndTheBishop(int *);

void sessionSummary(int *optionStats);
void readRestOfLine();

bool getIntegerFromStdIn(int *result, int length, const char *message, int min, int max);
bool allocateMemory(char **memory, int size);
void freeMemory(char **memory);
