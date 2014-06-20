/****************************************************************************
* COSC2138 / CPT220- Assignment #1
* Programming Principles 2A/Programming Techniques
* Author           : Greg Kappatos
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

/* This is used to compensate for the extra character spaces taken up by the
 *  '\n' and '\0' when user is asked for input through fgets(). */
#define EXTRA_SPACES 2

/* Specifies the maximum input length a user can enter for the options menu. */
#define MAX_OPTION_INPUT 1

/* Boolean constants. */
#define TRUE 1
#define FALSE 0


/* Custom Constants + Definitions. */

/* BOOLEAN enumeration. */
typedef enum {
    false = FALSE,
    true = TRUE
} BOOLEAN;

/* This is here to make life easier. */
typedef BOOLEAN bool;

/* This structure defines the main menu options. */
typedef struct {

    /* index is the number shown to the user.
     * The user will select this number. */
    int index;

    /* str is the menu title shown to the user.
     * This is also used when retrieving an
     * element from the array. */
    const char* str;

    /* Track statistics for this method?
     * This is used in Session Summary. */
    bool tracked;

    /* This pointer points to the method that should be invoked when the user
     * selects this menu option. This effectively removes the need for a
     * switch statement (which I did previously have).
     * The int* parameter is for incrementing optionStats on tracked
     * methods, otherwise it is the abort parameter for exiting the app. */
    void (*method)(int*);

} menuoption_t;

/* This structure defines a phone keypad. */
typedef struct {

    /* The actual number. */
    int digit;

    /* The characters that are linked to the number. */
    const char *code;
} keypad_t;

/* This enumeration defines the different chess pieces allowed. */
typedef enum {
    eChessBishop = 'B',
    eChessRook = 'R'
} chessPiece;

/* This enumeration defines the different actions performed
 * when dealing with the optionStats array. */
typedef enum {
    eOptionStatReset = 0,
    eOptionStatIncrement = 1,
    eOptionStatDecrement = 2
} optionStatAction;


/* Size of extra space for terminating strings with '\0' */
#define EXTRA_SPACE 1

/* This is here to make life easier. */
#define null NULL


/* This is used when using 1 based index instead of usual 0 based */
#define BASE1 1

/* Normal human number system is decimal which is base 10. This is used
 * when converting with strtol() */
#define BASE10 10


/* The starting power for the dynamic buffer. This is used in
 * firstLastStrings(). The user should be able to keep adding
 * words until their memory runs out. */
#define START_POWER 1


/* This is used as a limit when looping through the keypad structures.
 * There are only 9 keys with letters on them. */
#define MAX_KEYPAD 10

/* Menu starts at 1 and not 0 */
#define MIN_MENU_OPTION BASE1

/* + 2 = uncounted exit option (1) + max (1) */
#define MAX_MENU_OPTION NUM_OPTION_STATS + 2


/* This specifies that there is no string minimum. */
#define STRING_MIN_NONE 0

/* This specifies that there is a string minimum. */
#define STRING_MIN 1

/* STRING_MAX's used for buffer allocation and validation. */
#define STRING_MAX_TINY 11
#define STRING_MAX_SMALL 20
#define STRING_MAX_MEDIUM 256
#define STRING_MAX_LARGE 1024

#define SPACE_CHAR ' '
#define DASH_CHAR '-'


/* Message shown to user when memory allocation fails (out of memory?). */
#define ERROR_MEMORY "Error: memory allocation failed.\n"


/* Fibonacci constants.
 * The user can get the fibonacci series for numbers in the range of 1..40. */
#define MIN_OPTION_FIBONACCI 1
#define MAX_OPTION_FIBONACCI 40
#define FIBONACCI_NUM1 0
#define FIBONACCI_NUM2 1


/* This is used in wordStopping() to break up the sentence into words. */
#define WORD_SEPARATOR SPACE_CHAR

/* Specifies the maximum number of characters required for a word
 * to be "stopped". */
#define MIN_OPTION_WORD_SERIES 3

/* Specifies the minimum number of words required for processing
 * in firstLastStrings() */
#define MIN_OPTION_WORD_STOPPER 3

/* Used when creating dashes in output.
 * 3 = string\nstring\n\0
 * \n\n\0 */
#define DASH_EXTRA_SPACES 3


/* Maximum number of rows/columns */
#define CHESS_MAX 8

/* Row index is base 0. */
#define CHESS_ROW_MIN 0

/* Column index is base 0. */
#define CHESS_COLUMN_MIN 0

#define CHESS_ROW_MAX CHESS_MAX
#define CHESS_COLUMN_MAX CHESS_MAX

/* This is a square that cannot be moved to by the player. */
#define CHESS_SQUARE_DEFAULT '.'

/* This is a square that can be moved to by the player. */
#define CHESS_SQUARE_MOVABLE '+'


/* Specifies which character is used to complete firstLastStrings(). */
#define FIRST_LAST_FINISH_CHAR 'q'


/* Menu Option Titles. */
#define MENU_TITLE_FIBONACCI "Fibonacci Numbers"
#define MENU_TITLE_PHONENUMBERS "Translate Phone Numbers"
#define MENU_TITLE_FIRSTLASTSTRINGS "First and Last Strings"
#define MENU_TITLE_WORDSTOPPING "Word Stopping"
#define MENU_TITLE_ROOKANDBISHOP "Rook and Bishop"
#define MENU_TITLE_SESSIONSUMMARY "Session Summary"
#define MENU_TITLE_EXIT "Exit"


/* Function prototypes. */
void fibonacciNumbers(int *);
void phoneNumbers(int *);
void firstLastStrings(int *);
void wordStopping(int *);
void rookAndTheBishop(int *);

void sessionSummary(int *optionStats);
void readRestOfLine();

/* Custom function prototypes. */
bool getIntegerFromStdIn(int *result, int length, const char *message,
        int min, int max, bool showError, bool allowEmpty);
bool getStringFromStdIn(char **result, int length, const char *message,
        int min, bool showError);
bool allocateString(char **str, int size);
void freeString(char **str);
void freeStringArray(char **arr, int length);
void freeStrings(int length, ...);
int wordSeriesSortCallback(const void *a, const void *b);
char *createDashes(const char *str);
void plotChessPieces(char piece, int row, int column,
        char board[][CHESS_COLUMN_MAX + 1]);
bool isValidChessPiece(char c);
void exitApplication(int *abort);
menuoption_t *getMenuOptions();
menuoption_t *getMenuOptionByIndex(int index);
menuoption_t *getMenuOptionByTitle(char *title);
void performOptionStatAction(int *optionStats, optionStatAction action,
        char *title);
