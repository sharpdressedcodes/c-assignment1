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
#include <stdarg.h>
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
#define TRUE 1
#define FALSE 0


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

/*typedef enum {
    FALSE = 0,
    TRUE = 1
} BOOLEAN;*/
typedef enum {
    false = FALSE,
    true = TRUE
} BOOLEAN;

typedef struct {
    int digit;
    const char *code;
} keypad_t;

/*typedef unsigned int UINT;
typedef unsigned char UCHAR;*/
typedef BOOLEAN bool;
/*typedef UINT uint;
typedef UCHAR uchar;*/

/*
#define false FALSE
#define true TRUE
*/
#define null NULL

/* used when using 1 based index instead of usual 0 based */
#define BASE1 1
#define BASE10 10

#define START_POWER 1

#define MAX_KEYPAD 10

#define STRING_MIN_NONE 0
#define STRING_MIN 1
#define STRING_MAX_SMALL 20
#define STRING_MAX_MEDIUM 256
#define STRING_MAX_LARGE 1024

#define SPACE_CHAR ' '
#define DASH_CHAR '-'

#define ERROR_MEMORY "Error: memory allocation failed.\n"
#define MIN_OPTION_FIBONACCI 1
#define MAX_OPTION_FIBONACCI 40
#define FIBONACCI_NUM1 0
#define FIBONACCI_NUM2 1

#define WORD_SEPARATOR SPACE_CHAR
#define MIN_OPTION_WORD_SERIES 3
#define MIN_OPTION_WORD_STOPPER 3
/* string\nstring\n\0 */
#define DASH_EXTRA_SPACES 3

#define CHESS_MAX 8
#define CHESS_ROW_MIN 0
#define CHESS_COLUMN_MIN 0
#define CHESS_ROW_MAX CHESS_MAX
#define CHESS_COLUMN_MAX CHESS_MAX
#define CHESS_SQUARE_DEFAULT '.'
#define CHESS_SQUARE_MOVABLE '+'

#define FIRST_LAST_FINISH_CHAR 'q'


typedef enum {
    eChessRook = 'R',
    eChessBishop = 'B'
} chessPiece;

/* Function prototypes. */
void fibonacciNumbers(int *);
void phoneNumbers(int *);
void firstLastStrings(int *);
void wordStopping(int *);
void rookAndTheBishop(int *);

void sessionSummary(int *optionStats);
void readRestOfLine();

/* Custom function prototypes. */
bool getIntegerFromStdIn(int *result, int length, const char *message, int min, int max, bool showError, bool allowEmpty);
bool getStringFromStdIn(char **result, int length, const char *message, int min, bool showError);
bool allocateString(char **str, int size);
void freeString(char **str);
void freeStringArray(char **arr, int length);
void freeStrings(int length, ...);
int wordSeriesSortCallback(const void *a, const void *b);
char *createDashes(const char *str);
bool isValidChessPiece(char c);
