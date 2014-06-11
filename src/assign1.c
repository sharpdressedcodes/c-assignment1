/****************************************************************************
 * COSC2138/CPT 220 - Programming Principles 2A
 * Study Period 1  2014 Assignment #1 - Different Applications
 * Full Name        : Greg Kappatos
 * Student Number   : s3460969
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

int main(void) {

    int optionStats[NUM_OPTION_STATS];

    char *menu = NULL;
    int i = 0, option = 0;
    bool passed = FALSE, abort = FALSE;

    if (!allocateMemory(&menu, STRING_MAX))
        return EXIT_FAILURE;

    for (i = 0; i < NUM_OPTION_STATS; i++)
        optionStats[0] = 0;

    sprintf(menu, "%s%s%s%s%s%s%s%s%s",
        "\nMain Menu:\n",
        "1) Fibonacci Numbers\n",
        "2) Translating Phone Numbers\n",
        "3) First and Last Strings\n",
        "4) Word Stopping\n",
        "5) Rook and Bishop\n",
        "6) Session Summary\n",
        "7) Exit\n\n",
        "Select your option: "
    );

    while (!abort) {

        passed = getIntegerFromStdIn(&option, MAX_OPTION_INPUT, menu, 1, NUM_OPTION_STATS + 1);

        if (passed) {

            if (option <= NUM_OPTION_STATS)
                optionStats[option]++;

            switch (option) {

                case 1:
                    fibonacciNumbers(optionStats);
                    break;

                case 2:
                    phoneNumbers(optionStats);
                    break;

                case 3:
                    firstLastStrings(optionStats);
                    break;

                case 4:
                    wordStopping(optionStats);
                    break;

                case 5:
                    rookAndTheBishop(optionStats);
                    break;

                case 6:
                    sessionSummary(optionStats);
                    break;

                case 7:
                    abort = TRUE;
                    break;

            }

        }

    }

    /*free(menu);*/
    freeMemory(&menu);

    return EXIT_SUCCESS;

}

bool getIntegerFromStdIn(int *result, int length, const char *message, int min,
        int max) {

    int i = 0;
    char *s = NULL, *errorMessage = NULL, *s2 = NULL;
    bool passed = FALSE;

    if (!allocateMemory(&s, length + EXTRA_SPACES) ||
        !allocateMemory(&errorMessage, STRING_MAX_SMALL))
        return FALSE;

    sprintf(errorMessage, "%s %d %s %d. %s",
        "You must enter a number between",
        min,
        "and",
        max,
        "Try again."
    );

    do {

        puts(message);
        fgets(s, length + EXTRA_SPACES, stdin);

        if (s[strlen(s) - 1] != '\n') {

            fputs(errorMessage, stderr);
            readRestOfLine();

        } else {

            s[strlen(s) - 1] = '\0';
            i = (int) strtol(s, &s2, 10);

            if (strcmp(s2, "") != 0 || i < min || i > max) {

                fputs(errorMessage, stderr);
                /* readRestOfLine ? */

            } else {

                freeMemory(&s);
                freeMemory(&errorMessage);
                *result = i;
                passed = TRUE;

            }

        }

    } while (!passed);

    return TRUE;

}

bool allocateMemory(char **memory, int size){

    *memory = NULL;

    if (size > 0)
        *memory = malloc(sizeof(char) * size);

    if (*memory == NULL){
        fputs(ERROR_MEMORY, stderr);
        return FALSE;
    } else {
        return TRUE;
    }

}

void freeMemory(char **memory){

    if (*memory != NULL){
        free(*memory);
        *memory = NULL;
    }

}

/* Function fibonacciNumbers
 * This function prompts the user for a positive integer N. The first N
 * integers of the Fibonacci sequence are printed in a simple tabular format.
 * Additionally, the sum and average of these numbers are printed.
 This function will be used in menu option 1.
 */
void fibonacciNumbers(int *optionStats) {

    int i = 0;
    int limit = 0;
    int num1 = FIBONACCI_NUM1;
    int num2 = FIBONACCI_NUM2;
    int sum = 0;
    float average = 0;
    char *message = NULL;
    char *fibMax = NULL;

    if (!allocateMemory(&message, STRING_MAX_SMALL) ||
        !allocateMemory(&fibMax, STRING_MAX_SMALL)){
        optionStats[1]--;
        return;
    }

    sprintf(fibMax, "%d", MAX_OPTION_FIBONACCI);
    sprintf(message, "Enter a positive integer (%d-%d): ",
        MIN_OPTION_FIBONACCI,
        MAX_OPTION_FIBONACCI
    );

    if (getIntegerFromStdIn(&limit, strlen(fibMax), message, MIN_OPTION_FIBONACCI, MAX_OPTION_FIBONACCI)) {

        printf("Fibonacci sequence for %d terms:\n", limit);

        for (i = 0; i < limit; i++) {

            int fibonacci = i < 2 ? i : num1 + num2;

            if (i > 1) {
                num1 = num2;
                num2 = fibonacci;
            }

            sum += fibonacci;
            printf(i == limit ? "%-8d" : "%-8d ", fibonacci);

        }

        average = (float) sum / i;

        printf("\nSum: %d\n", sum);
        printf("Average: %.2f\n", average);

    }

    freeMemory(&message);
    freeMemory(&fibMax);

}

/*
 * Function phoneNumbers() A function that translates an alphabetic phone number into numeric form.This is menu option number 2
 */
void phoneNumbers(int *optionStats) {

    const keypad_t keypad[] = {
        {2, "ABC"},
        {3, "DEF"},
        {4, "GHI"},
        {5, "JKL"},
        {6, "MNO"},
        {7, "PQRS"},
        {8, "TUV"},
        {9, "XYZ"},
        {MAX_KEYPAD, NULL}
    };

    /*
     * example input/outputs:
     *
     * CALLATT / 2255288
     * 1-800-COL-LECT / 1-800-265-5328
     *
     * search for A-Z, anything else stays as it is.
     * */

    keypad_t *ptr;
    /* char *input, *output */

    for (ptr = keypad; ptr->digit != MAX_KEYPAD; ++ptr){
        int i = 0;
        for (; i < strlen(ptr->code); i++){
            /*if (strcmp(iterator->code[i], ))*/
        }
    }
}

/*
 Function firstLastStrings(). This function that finds the "first" and "last" words in a series of words. After the user enters the words, the function will determine which words would come first and last if the words were listed in dictionary order. The function must stop accepting input when the user enters a blank line, eg. just presses enter. Assume that no word is more than 20 letters long. An interactive session with the function might look like this:
 This is menu option number 3 */

void firstLastStrings(int *optionStats) {

}

/*
 * Function substrings() Many search engines (such as Google), implement "stopping" so that commonly occurring query words are ignored for the purposes of ranking query results. In this option, you will need to prompt the user for a string of 1-20 characters. You will need to output the string with all words of length 1-3 characters "stopped".
 This is menu option number 4
 */

void wordStopping(int *optionStats) {

}

/* Function rookAndTheBishop() A rook can only move either horizontally or vertically. 
 A bishop can only move diagonally.
 * menu option 5.
 */
void rookAndTheBishop(int *optionStats) {

}

/* See requirement #7  "Session summary" of the assignment specs.
 * Function sessionSummary() reports the program usage.
 */
void sessionSummary(int *optionStats) {

}

/*
 * Function readRestOfLine() is used for buffer clearing. Source:
 */

void readRestOfLine() {

    int c;

    /* Read until the end of the line or end-of-file. */
    while ((c = fgetc(stdin)) != '\n' && c != EOF)
        ;

    /* Clear the error and end-of-file flags. */
    clearerr(stdin);

}

