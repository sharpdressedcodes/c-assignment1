/****************************************************************************
 * COSC2138/CPT 220 - Programming Principles 2A
 * Study Period 2  2014 Assignment #1 - Different Applications
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
    /*int optionStats[trackedMethodMax] = {0};*/

    char *menu = null;
    int i = 0;
    int option = 0;
    bool passed = false;
    bool abort = false;

    if (!allocateMemory(&menu, STRING_MAX))
        return EXIT_FAILURE;

    for (i = 0; i < NUM_OPTION_STATS; i++)
        optionStats[i] = 0;

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

            /* change to if (option -1 < NUM_OPTION_STATS) if have to count session summary */
            if (option < NUM_OPTION_STATS)
                optionStats[option - 1]++;

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
                    abort = true;
                    break;

            }

        }

    }

    freeMemory(&menu);

    return EXIT_SUCCESS;

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
    char *message = null;
    char *fibMax = null;

    if (!allocateMemory(&message, STRING_MAX_SMALL) ||
        !allocateMemory(&fibMax, STRING_MAX_SMALL)){
        /*optionStats[eFibonacciSeries]--;*/
        return;
    }

    sprintf(fibMax, "%d", MAX_OPTION_FIBONACCI);
    sprintf(message, "Enter a positive integer (%d-%d): ",
        MIN_OPTION_FIBONACCI,
        MAX_OPTION_FIBONACCI
    );

    if (getIntegerFromStdInNS(&limit, strlen(fibMax), message, MIN_OPTION_FIBONACCI, MAX_OPTION_FIBONACCI, false)) {

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

    } else {

        optionStats[eFibonacciSeries]--;

    }

    freeMemory(&message);
    freeMemory(&fibMax);

}

/*
 * Function phoneNumbers() A function that translates an alphabetic phone number into numeric form.This is menu option number 2
 */
void phoneNumbers(int *optionStats) {

    int i = 0 ;
    char *input = null, *output = null;
    char *message = null;
    keypad_t *ptr, keypad[] = {
        {2, "ABC"},
        {3, "DEF"},
        {4, "GHI"},
        {5, "JKL"},
        {6, "MNO"},
        {7, "PQRS"},
        {8, "TUV"},
        {9, "XYZ"},
        {MAX_KEYPAD, null}
    };

    if (!allocateMemory(&input, STRING_MAX_SMALL) ||
        !allocateMemory(&output, STRING_MAX_SMALL) ||
        !allocateMemory(&message, STRING_MAX_SMALL)){
        /*optionStats[ePhoneNumberConversion]--;*/
        return;
    }

    sprintf(message, "Enter phone number (max %d characters): ", STRING_MAX_SMALL);

    if (getStringFromStdInNS(&input, STRING_MAX_SMALL, message, false)){

        for (i = 0; i < strlen(input); i++){

            if (isalpha(input[i])){

                for (ptr = keypad; ptr->digit != MAX_KEYPAD; ++ptr){
                    if (strchr(ptr->code, toupper(input[i])) != null){
                        output[i] = (char)(ptr->digit + '0');
                        break;
                    }
                }

            } else {

                output[i] = input[i];

            }

        }

        output[i] = '\0';
        printf("%s\n", output);

    } else {

        optionStats[ePhoneNumberConversion]--;

    }

    freeMemory(&input);
    freeMemory(&output);
    freeMemory(&message);

}

/*
 Function firstLastStrings(). This function that finds the "first" and "last" words in a series of words.
 After the user enters the words, the function will determine which words would come first and last if the
 words were listed in dictionary order. The function must stop accepting input when the user enters a blank line,
 eg. just presses enter. Assume that no word is more than 20 letters long. An interactive session with the function might look like this:
 This is menu option number 3 */

void firstLastStrings(int *optionStats) {

    int i = 0;
    int bufferCount = 0;
    int bufferPower = 1;
    char *input = null;
    char *message = null;
    char *first = null;
    char *last = null;
    char *dashed = null;
    char *buffer[STRING_MAX];

    if (!allocateMemory(&input, STRING_MAX_TINY) ||
        !allocateMemory(&message, STRING_MAX_SMALL) ||
        !allocateMemory(&first, STRING_MAX_TINY) ||
        !allocateMemory(&last, STRING_MAX_TINY)){
        /*optionStats[2]--;*/
        return;
    }

    dashed = createDashes("Finding strings");
    printf("%s\n", dashed);
    sprintf(message, "Enter word (max %d characters, enter to quit): ", STRING_MAX_TINY);

    while (getStringFromStdInNS(&input, STRING_MAX_TINY, message, false) && strlen(input) > 0){

        buffer[bufferCount] = null;

        if (!allocateMemory(&buffer[bufferCount], strlen(input) + 1)){
            /*optionStats[eFirstLastStrings]--;*/
            return;
        }

        strcpy(buffer[bufferCount], input);

        if (bufferCount >= STRING_MAX * bufferPower){
            bufferPower++;
            if (!allocateMemory(&buffer[bufferCount], STRING_MAX * bufferPower)){
                /*optionStats[eFirstLastStrings]--;*/
                return;
            }
        }

        freeMemory(&input);
        allocateMemory(&input, STRING_MAX_TINY);

        bufferCount++;

    }

    if (bufferCount < MIN_OPTION_WORD_SERIES){
        /*fprintf(stderr, "You must enter at least %d words. Try again.\n", MIN_OPTION_WORD_SERIES);*/
        optionStats[eFirstLastStrings]--;
        return;
    }

    qsort(buffer, bufferCount, sizeof(char*), wordSeriesSortCallback);

    strcpy(first, buffer[0]);
    strcpy(last, buffer[bufferCount - 1]);

    printf("Smallest word: %s\n", first);
    printf("Largest word: %s\n", last);

    freeMemory(&input);
    freeMemory(&message);
    freeMemory(&first);
    freeMemory(&last);
    freeMemory(&dashed);

    for (i = 0; i < bufferCount; i++)
        freeMemory(&buffer[i]);

}

/*
 * Function substrings() Many search engines (such as Google), implement "stopping" so that commonly occurring query words are ignored for the purposes of ranking query results. In this option, you will need to prompt the user for a string of 1-20 characters. You will need to output the string with all words of length 1-3 characters "stopped".
 This is menu option number 4
 */

void wordStopping(int *optionStats) {

    /*if (getStringFromStdIn(&input, STRING_MAX_TINY, message)){

            char *chr = strchr(input, WORD_SEPARATOR);

            if (chr == null){

                fputs("You must enter at least 2 words. Try again.\n", stderr);

            } else {

                int i, pos = chr - input + 1;

                for (i = 0; i < pos; i++)
                    first[i] = input[i];

                chr = strrchr(input, WORD_SEPARATOR);
                pos = chr - input + 1;

                for (i = pos; i < strlen(input); i++)
                    last[i] = input[i];



            }

        }*/

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

    int i = 0;
    char *dashed = null;
    char *title1 = null;
    char *title2 = null;

    if (!allocateMemory(&dashed, STRING_MAX_SMALL) ||
        !allocateMemory(&title1, STRING_MAX_SMALL) ||
        !allocateMemory(&title2, STRING_MAX_SMALL)){
        return;
    }

    dashed = createDashes("Session summary");
    printf("%sOption     Count\n------     -----\n", dashed);

    /* remove -1 from loop check is have to print session summary count */
    for (; i < trackedMethodMax; i++)
        printf("%6d     %5d\n", i + 1, optionStats[i]);

    freeMemory(&dashed);
    freeMemory(&title1);
    freeMemory(&title2);

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

bool getIntegerFromStdInNS(int *result, int length, const char *message, int min, int max, bool showError){

    int i = 0;
    char *s = null;
    char *s2 = null;
    char *errorMessage = null;
    bool passed = false;

    if (!allocateMemory(&s, length + EXTRA_SPACES) ||
        !allocateMemory(&errorMessage, STRING_MAX_SMALL))
        return false;

   /* if (showError)*/
        sprintf(errorMessage, "%s %d %s %d. %s",
            "You must enter a number between",
            min,
            "and",
            max,
            "Try again.\n"
        );

    do {

        fputs(message, stdout);
        fgets(s, length + EXTRA_SPACES, stdin);

        if (s[strlen(s) - 1] != '\n') {

            fputs(errorMessage, stderr);
            readRestOfLine();

        } else {

            s[strlen(s) - 1] = '\0';
            i = (int) strtol(s, &s2, 10);

            if (strcmp(s2, "") != 0 || i < min || i > max) {

                if (showError){

                    fputs(errorMessage, stderr);
                    /* readRestOfLine ? */

                } else {

                    *result = 0;
                    /*passed = true;*/

                    freeMemory(&s);
                    freeMemory(&errorMessage);
                    return false;

                }

            } else {

                *result = i;
                passed = true;

                freeMemory(&s);
                freeMemory(&errorMessage);

            }

        }

    } while (!passed);

    return true;

}

bool getIntegerFromStdIn(int *result, int length, const char *message, int min, int max) {

    return getIntegerFromStdInNS(result, length, message, min, max, true);

}

bool getStringFromStdInNS(char **result, int length, const char *message, bool showError){

    char *s = null;
    char *errorMessage = null;
    bool passed = false;

    if (!allocateMemory(&s, length + EXTRA_SPACES) ||
        !allocateMemory(&errorMessage, STRING_MAX_SMALL))
        return false;

    if (showError)
        sprintf(errorMessage, "Invalid entry! Try again.\n");

    while (!passed) {

        size_t len;

        fputs(message, stdout);
        fgets(s, length + EXTRA_SPACES, stdin);

        len = strlen(s);

        if (len < EXTRA_SPACES || s[len - 1] != '\n') {

            if (showError){
                fputs(errorMessage, stderr);
                /*readRestOfLine();*/
            } else {

                strcpy(*result, "\0");
                /*passed = true;*/

                freeMemory(&s);
                freeMemory(&errorMessage);

                return false;

            }

        } else {

            s[len - 1] = '\0';
            strcpy(*result, s);
            passed = true;

            freeMemory(&s);
            freeMemory(&errorMessage);

        }

    }

    return true;

}

bool getStringFromStdIn(char **result, int length, const char *message){

    return getStringFromStdInNS(result, length, message, true);

}

bool allocateMemory(char **memory, int size){

    if (size > 0)
        *memory = realloc(*memory, sizeof(char) * size);

    if (*memory == null){
        fputs(ERROR_MEMORY, stderr);
        return false;
    } else {
        return true;
    }

}

void freeMemory(char **memory){

    if (*memory != null){
        free(*memory);
        *memory = null;
    }

}

int wordSeriesSortCallback(const void *a, const void *b){

    const char **ptr1 = (const char **)a;
    const char **ptr2 = (const char **)b;

    return strcasecmp(*ptr1, *ptr2);

}

char *createDashes(const char *str){

    int i = 0;
    int len = strlen(str);
    int max = (len << 1) + 2; /* including 2 \n's*/
    char *dashes = null;

    if (allocateMemory(&dashes, max + 1)){
        sprintf(dashes, "%s\n", str);
        for (i = len + 1; i < max - 1; i++)
            dashes[i] = '-';
        dashes[i++] = '\n';
        dashes[i] = '\0';
    }

    return dashes;

}

/*int getArrayIndex(char *array[], int length, char *search){

    int pos = 0;
    int start = 0;
    int finish = length - 1;
    int comparison = 0;

    while (start <= finish){

        pos = (start + finish) >> 1;
        comparison = strcmp(array[pos], search);

        if (comparison == 0)
            return pos;
        else if (comparison < 0)
            start = pos + 1;
        else
            finish = pos - 1;

    }

    return -1;

}*/
