/****************************************************************************
* COSC2138 / CPT220- Assignment #1
* Programming Principles 2A/Programming Techniques
* Author           : Greg KappatosGreg Kappatos
* Student Number   : s3460969
* Start up code provided by the C-Teach team
****************************************************************************/

/* Header files. */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Custom Header files. */
#include <strings.h>
#include <ctype.h>

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

/* Custom Constants + Definitions. */
typedef enum {
    eFibonacciSeries = 0,
    ePhoneNumberConversion = 1,
    eFirstLastStrings = 2,
    eWordStopping = 3,
    eRookAndBishop = 4,
    trackedMethodMax = 5
    /*,
    eSessionSummary = 5*/
} trackedMethod;

typedef enum {
    FALSE = 0,
    TRUE = 1
} BOOLEAN;

typedef struct {
    int digit;
    const char *code;
} keypad_t;

typedef BOOLEAN bool;

#define false FALSE
#define true TRUE
#define null NULL

/* used when using 1 based index instead of usual 0 based */
#define BASE1 1
#define BASE10 10

#define START_POWER 1

#define MAX_KEYPAD 10

#define STRING_MAX_SMALL 20
#define STRING_MAX_MEDIUM 256
#define STRING_MAX_LARGE 1024

#define ERROR_MEMORY "Error: memory allocation failed.\n"
#define MIN_OPTION_FIBONACCI 1
#define MAX_OPTION_FIBONACCI 40
#define FIBONACCI_NUM1 0
#define FIBONACCI_NUM2 1

#define WORD_SEPARATOR ' '
#define MIN_OPTION_WORD_SERIES 3
#define MIN_OPTION_WORD_STOPPER 3
/* string\nstring\n\0 */
#define DASH_EXTRA_SPACES 3

/* Function prototypes. */
void fibonacciNumbers(int *);
void phoneNumbers(int *);
void firstLastStrings(int *);
void wordStopping(int *);
void rookAndTheBishop(int *);

void sessionSummary(int *optionStats);
void readRestOfLine();

/* Custom function prototypes. */
bool getIntegerFromStdIn(int *result, int length, const char *message, int min, int max, bool showError);
bool getStringFromStdIn(char **result, int length, const char *message, bool showError);
bool allocateMemory(char **memory, int size);
void freeMemory(char **memory);
int wordSeriesSortCallback(const void *a, const void *b);
char *createDashes(const char *str);
