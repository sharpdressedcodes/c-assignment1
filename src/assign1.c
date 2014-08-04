/****************************************************************************
 * COSC2138/CPT 220 - Programming Principles 2A
 * Study Period 2  2014 Assignment #1 - Different Applications
 * Full Name        : Greg Kappatos
 * Student Number   :
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

/*
 * Requirement  1 - Main menu()
 */
int main(void) {

    int optionStats[NUM_OPTION_STATS];
    int option = 0;
    char menu[STRING_MAX_LARGE] = {0};
    bool abort = false;
    menuoption_t *ptr = null;
    menuoption_t *options = getMenuOptions();

    /* Stupid Eclipse won't show the console until after it has stopped.
     * See http://stackoverflow.com/questions/13035075/printf-not-printing-on-console */
    setvbuf (stdout, NULL, _IONBF, 0);

    /* Reset statistics. */
    statAction(optionStats, eOptionStatReset, null);

    /* ################################################################# */
    /* Menu creation. */

    /* Append title. */
    strcpy(menu, "\nMain Menu:\n");

    /* Iterate through menu option structures and append
     * index and title to menu string. */
    for (ptr = options; ptr->index != MAX_MENU_OPTION; ++ptr){

        /* Create a temp variable. This will be formatted
         * and passed to the menu. */
        char s[STRING_MAX_MEDIUM] = {0};

        /* Format the string. */
        sprintf(s, "%d) %s\n", ptr->index, ptr->str);

        /* Now append the formatted string to the menu. */
        strcat(menu, s);
    }

    /* Append the request. */
    strcat(menu, "\nSelect your option: ");

    /* ################################################################# */

    /* Main menu loop. Abort will be modified when user selects "Exit". */
    while (!abort) {

        /* Get the menu option from the user.
         * NUM_OPTION_STATS + 1 to count the exit option. */
        if (getIntegerFromStdIn(&option, MAX_OPTION_INPUT, menu,
                MIN_MENU_OPTION, NUM_OPTION_STATS + 1, true, false)) {

            /* Lookup the option by it's index */
            ptr = getMenuOptionByIndex(option);

            /* Call the function pointer. */
            ptr->method(strcmp(ptr->str,
                    MENU_TITLE_EXIT) == 0 ? (int*)&abort : optionStats);

        }

    }

    return EXIT_SUCCESS;

}

/* Function fibonacciNumbers
 * This function prompts the user for a positive integer N. The first N
 * integers of the Fibonacci sequence are printed in a simple tabular format.
 * Additionally, the sum and average of these numbers are printed.
 * This function will be used in menu option 1.
 *
 * Requirement  2 - Fibonacci Numbers
 */
void fibonacciNumbers(int *optionStats) {

    int i = 0;
    int limit = 0;
    int num1 = FIBONACCI_NUM1;
    int num2 = FIBONACCI_NUM2;
    int sum = 0;
    float average = 0;
    char message[STRING_MAX_MEDIUM] = {0};
    char fibMax[STRING_MAX_MEDIUM] = {0};

    /* Convert the max fibonacci number to a string. */
    sprintf(fibMax, "%d", MAX_OPTION_FIBONACCI);

    /* Create the formatted input request message. */
    sprintf(message, "Enter a positive integer (%d-%d): ",
        MIN_OPTION_FIBONACCI,
        MAX_OPTION_FIBONACCI
    );

    /* Ask the user for a limit. */
    if (getIntegerFromStdIn(&limit, strlen(fibMax), message,
            MIN_OPTION_FIBONACCI, MAX_OPTION_FIBONACCI, true, true)
            && limit >= MIN_OPTION_FIBONACCI) {

        /* Print formatted result title with limit. */
        printf("Fibonacci sequence for %d terms:\n", limit);

        /* Calculate fibonacci series, based on user limit. */
        for (i = 0; i < limit; i++) {

            /* If the current index is less than 1, leave it alone,
             * otherwise start adding the previous 2 numbers. */
            int fibonacci = i <= FIBONACCI_NUM2 ? i : num1 + num2;

            /* Start setting the numbers which will be used above,
             * only if the current index is greater than 1. */
            if (i > FIBONACCI_NUM2) {
                num1 = num2;
                num2 = fibonacci;
            }

            /* Add the number to the total sum. */
            sum += fibonacci;

            /* Print the result to the output stream.
             * If this is the last item in the loop,
             * don't append a space. */
            printf(i == limit ? "%-8d" : "%-8d ", fibonacci);

        }

        /*  Calculate average.*/
        average = (float) sum / i;

        /* Print the sum and average results. */
        printf("\nSum: %d\n", sum);
        printf("Average: %.2f\n", average);

        /* Increment the statistics. */
        statAction(optionStats, eOptionStatIncrement, MENU_TITLE_FIBONACCI);

    }

}

/*
 * Function phoneNumbers() A function that translates an alphabetic phone
 * number into numeric form. This is menu option number 2
 *
 * Requirement  3 - Translating Phone numbers
 */
void phoneNumbers(int *optionStats) {

    int i = 0 ;
    char input[STRING_MAX_TINY + EXTRA_SPACE] = {0};
    char output[STRING_MAX_TINY + EXTRA_SPACE] = {0};
    char message[STRING_MAX_MEDIUM] = {0};
    keypad_t *ptr = null;
    keypad_t *keypad = getKeypad();

    /* Create formatted input request message. */
    sprintf(message, "Enter phone number (max %d characters): ",
            STRING_MAX_TINY);

    /* Ask the user for a phone number. */
    if (getStringFromStdIn(input, STRING_MAX_TINY, message,
            STRING_MIN_NONE, true)
            && strlen(input) > 0){

        /* Iterate through input string character by character,
         * if the char isn't a letter, just append it to the result,
         * otherwise, lookup the appropriate letter and append
         * that to the result. */
        for (i = 0; i < strlen(input); i++){

            if (isalpha(input[i])){

                for (ptr = keypad; ptr->digit != MAX_KEYPAD; ++ptr){

                    /* Search for the letter in the keypad structures.
                     * Convert it to upper case because we are nice guys. */
                    if (strchr(ptr->code, toupper(input[i])) != null){
                        /* Append the letter to the output by converting the
                         * number to a char. This technique will only work
                         * with numbers less than 9. */
                        output[i] = (char)(ptr->digit + '0');
                        break;
                    }

                }

            } else {

                output[i] = input[i];

            }

        }

        /* Terminate the string. */
        output[i] = '\0';

        /* Print the result. */
        printf("%s\n", output);

        /* Increment the statistics. */
        statAction(optionStats, eOptionStatIncrement, MENU_TITLE_PHONENUMBERS);

    }

}

/*
 Function firstLastStrings(). This function that finds the "first" and "last"
 words in a series of words. After the user enters the words, the function will
 determine which words would come first and last if the words were listed in
 dictionary order. The function must stop accepting input when the user enters
 a blank line, eg. just presses enter. Assume that no word is more than 20
 letters long. An interactive session with the function might look like this:
 This is menu option number 3

 Requirement  4 - First and Last Strings
 */
void firstLastStrings(int *optionStats) {

    int bufferCount = 0;
    int bufferPower = START_POWER;
    char input[STRING_MAX_SMALL + EXTRA_SPACE] = {0};
    char message[STRING_MAX_MEDIUM] = {0};
    char *dashed = createDashes("Finding strings");
    char *buffer[STRING_MAX_LARGE];
    bool passed = false;

    printf("%s\n", dashed);
    sprintf(message, "Enter word (%d-%d characters, %c to finish): ",
        STRING_MIN,
        STRING_MAX_SMALL,
        FIRST_LAST_FINISH_CHAR
    );

    /* Keep asking the user for words, until they quit. */
    while (!passed){

        /* Ask the user for the word. */
        if (getStringFromStdIn(input, STRING_MAX_SMALL, message,
                STRING_MIN_NONE, true)){

            /* If the user didn't enter anything, cleanup and go home. */
            if (strlen(input) == STRING_MIN_NONE){
                freeString(&dashed);
                freeStringArray(buffer, bufferCount);
                return;
            }

            /* Did the user enter the QUIT character? */
            else if (strlen(input) == STRING_MIN &&
                    tolower(input[0]) == FIRST_LAST_FINISH_CHAR){

                /* Are there enough words in buffer to quit? */
                if (bufferCount < MIN_OPTION_WORD_SERIES){

                    fprintf(stderr, "You must enter at least %d words\n",
                            MIN_OPTION_WORD_SERIES);

                    /* Reset input. */
                    memset(input, 0, sizeof(char) * STRING_MAX_SMALL);

                /* User entered QUIT character, and there are enough
                 * words in the buffer. */
                } else {

                    /* Sort the words, in ascending order. */
                    qsort(buffer, bufferCount, sizeof(char*),
                            wordSeriesSortCallback);

                    /* Print first and last words from the sorted buffer. */
                    printf(
                        "Smallest Word: %s\nLargest Word %s\n",
                        buffer[0],
                        buffer[bufferCount - 1]
                    );

                    /* Increment the statistics. */
                    statAction(optionStats, eOptionStatIncrement,
                            MENU_TITLE_FIRSTLASTSTRINGS);

                    /* Cleanup. */
                    freeString(&dashed);
                    freeStringArray(buffer, bufferCount);

                    /* Set flag to exit loop. */
                    passed = true;

                }

            /* User has entered a word. */
            } else {

                buffer[bufferCount] = null;

                /* Try to allocate memory, cleanup if it fails. */
                if (!allocateString(&buffer[bufferCount], strlen(input) + EXTRA_SPACE)){
                    freeString(&dashed);
                    freeStringArray(buffer, bufferCount);
                    return;
                }

                /* Copy the word to the buffer. */
                strcpy(buffer[bufferCount], input);

                /* Resize buffer if required. */
                if (bufferCount >= STRING_MAX_LARGE * bufferPower){

                    /* Try to allocate memory, cleanup if it fails. */
                    if (!allocateString(&buffer[bufferCount],
                            STRING_MAX_LARGE * ++bufferPower)){
                        freeString(&dashed);
                        freeStringArray(buffer, bufferCount);
                        return;
                    }

                }

                /* Reset input. */
                memset(input, 0, sizeof(char) * STRING_MAX_SMALL);

                /* Increment buffer. */
                bufferCount++;

            }

        }

    }

}

/*
 * Function substrings() Many search engines (such as Google), implement
 * "stopping" so that commonly occurring query words are ignored for the
 * purposes of ranking query results. In this option, you will need to prompt
 * the user for a string of 1-20 characters.
 * You will need to output the string with all words of length 1-3 characters
 * "stopped".
 * This is menu option number 4
 *
 * Requirement  5 - Word Stopping
 */
void wordStopping(int *optionStats) {

    char *chr = null;
    char input[STRING_MAX_SMALL + EXTRA_SPACE] = {0};
    char buffer[STRING_MAX_SMALL + EXTRA_SPACE] = {0};
    char message[STRING_MAX_MEDIUM] = {0};
    char delim[] = {WORD_SEPARATOR, '\0'};
    int i = 0;

    sprintf(message, "Enter a string (%d-%d characters): ",
        STRING_MIN,
        STRING_MAX_SMALL
    );

    /* Keep asking the user for a valid sentence. */
    do {

        /* Reset the memory if we have already been here. */
        if (i++ > 0)
            memset(input, 0, sizeof(char) * STRING_MAX_SMALL);

    } while (!getStringFromStdIn(input, STRING_MAX_SMALL, message,
            STRING_MIN_NONE, true));

    /* User aborted. Exit. */
    if (strlen(input) == 0)
        return;

    /* Loop through the sentence, splitting it into words
     * with the delim (space) and append valid words to the output. */
    chr = strtok(input, delim);

    /* No spaces? Just append the whole input. */
    if (chr == null){

        strcpy(buffer, input);

    } else {

        /* Keep looping until no more spaces are found. */
        while (chr != null){

            /* Is this a valid word (has minimum required char length) ? */
            if (strlen(chr) > MIN_OPTION_WORD_STOPPER){

                /* Do we need to append a space? */
                if (strlen(buffer) == 0){

                    strcpy(buffer, chr);

                } else {

                    strcat(buffer, delim);
                    strcat(buffer, chr);

                }

            }

            /* Continue the loop (if possible). */
            chr = strtok(null, delim);

        }

    }

    /* Oh uh, we stripped all the words. */
    if (strlen(buffer) == 0)
        puts("All words have been stopped.");

    else
        printf("\nStopped string: %s\n", buffer);

    /* Increment statistics. */
    statAction(optionStats, eOptionStatIncrement, MENU_TITLE_WORDSTOPPING);

}

/* Function rookAndTheBishop() A rook can only move either horizontally or
 * vertically. A bishop can only move diagonally.
 * menu option 5.
 *
 * Requirement  6 - Rook and the Bishop
 */
void rookAndTheBishop(int *optionStats) {

    int i = 0;
    int row = 0;
    int column = 0;
    char chr = 0;
    char message[STRING_MAX_MEDIUM] = {0};
    char piece[MAX_OPTION_INPUT + EXTRA_SPACE] = {0};
    char board[CHESS_ROW_MAX][CHESS_COLUMN_MAX + EXTRA_SPACE] = {{0}};
    bool passed = false;

    sprintf(message, "Enter Piece type (%c/%c): ", eChessRook, eChessBishop);

    /* Keep asking the user for a valid chess piece. */
    while (!passed){

        /* Reset the piece to null if we have already been here. */
        if (piece[0] != '\0')
            memset(piece, 0, sizeof(char) * MAX_OPTION_INPUT);

        /* Ask the user for a character. */
        if (getStringFromStdIn(piece, MAX_OPTION_INPUT, message,
                STRING_MIN_NONE, true)){

            /* User aborted. Exit. */
            if (strlen(piece) == 0)
                return;

            /* Convert letter to upper case. */
            chr = toupper(piece[0]);

            /* Validate chess piece. */
            if (!isValidChessPiece(chr))
                fputs("Invalid piece. Try again.\n", stderr);
            else
                passed = true;

        }

    }

    /* Reset flag and message. */
    passed = false;
    memset(message, 0, STRING_MAX_MEDIUM);
    sprintf(message, "Row (%d..%d): ", CHESS_ROW_MIN, CHESS_ROW_MAX - 1);

    /* Keep asking the user for a valid row number. */
    while (!passed){

        /* Ask the user. */
        if (getIntegerFromStdIn(&row, MAX_OPTION_INPUT, message, CHESS_ROW_MIN,
                CHESS_ROW_MAX - 1, true, true)){

            /* User aborted, Exit. */
            if (row == CHESS_ROW_MIN - 1)
                return;

            passed = true;
        }

    }

    /* Reset flag and message. */
    passed = false;
    memset(message, 0, STRING_MAX_MEDIUM);
    sprintf(message, "Column (%d..%d): ",
        CHESS_COLUMN_MIN,
        CHESS_COLUMN_MAX - 1
    );

    /* Keep asking the user for a valid column number. */
    while (!passed){

        /* Ask the user. */
        if (getIntegerFromStdIn(&column, MAX_OPTION_INPUT, message,
                CHESS_COLUMN_MIN, CHESS_COLUMN_MAX - 1, true, true)){

            /* User aborted. Exit. */
            if (column == CHESS_COLUMN_MIN - 1)
                return;

            passed = true;
        }

    }

    /* Plot all pieces, according to chess piece, row and column. */
    plotChessPieces(chr, row, column, board);

    /* Print chess board, row by row. */
    for (i = CHESS_ROW_MIN; i < CHESS_ROW_MAX; i++)
        printf("%s\n", board[i]);

    /* Increment statistics. */
    statAction(optionStats, eOptionStatIncrement, MENU_TITLE_ROOKANDBISHOP);

}

/* See requirement #7  "Session summary" of the assignment specs.
 * Function sessionSummary() reports the program usage.
 *
 * Requirement  7 - Session Summary
 */
void sessionSummary(int *optionStats) {

    char *title = MENU_TITLE_SESSIONSUMMARY;
    char *option = "Option";
    char *count = "Count";
    char *dashed = createDashes(title);
    char spaces[STRING_MAX_MEDIUM] = {0};
    char optionDashes[STRING_MAX_SMALL] = {0};
    char countDashes[STRING_MAX_SMALL] = {0};
    menuoption_t *options = getMenuOptions();

    /* Set the spaces. */
    memset(spaces, SPACE_CHAR, strlen(title) - strlen(option) - strlen(count));

    /* Set the dashes, to be used for underlining. */
    memset(optionDashes, DASH_CHAR, strlen(option));
    memset(countDashes, DASH_CHAR, strlen(count));

    printf("%s%s%s%s\n%s%s%s\n",
        dashed,
        option,
        spaces,
        count,
        optionDashes,
        spaces,
        countDashes
    );

    /* Iterate through menu option structure array,
     * and if the menu's method is tracked, display it. */
    for (; options->index != MAX_MENU_OPTION; ++options)
        if (options->tracked)
            printf("%6d%s%5d\n",
                options->index,
                spaces,
                optionStats[options->index - MIN_MENU_OPTION]
            );

    /* Cleanup. */
    freeString(&dashed);

}

/*
 * Function readRestOfLine() is used for buffer clearing.
 * Source: Steven Burrows
 * URL: https://www.dlsweb.rmit.edu.au/set/Courses/Content/CSIT/oua/cpt220/c-function-examples/index.html
 */
void readRestOfLine() {

    int c;

    /* Read until the end of the line or end-of-file. */
    while ((c = fgetc(stdin)) != '\n' && c != EOF)
        ;

    /* Clear the error and end-of-file flags. */
    clearerr(stdin);

}

/* This function will get an integer value from the user.
 * Depending on the parameters set, it can also show an error message,
 * or totally ignore errors.
 *
 * This function is based on:
 * Source: Steven Burrows
 * URL: https://www.dlsweb.rmit.edu.au/set/Courses/Content/CSIT/oua/cpt220/c-function-examples/InputValidation/getInteger-advanced.c
 * */
bool getIntegerFromStdIn(int *result, const int length, const char *message,
        const int min, const int max, bool showError, bool allowEmpty){

    int i = 0;
    char errorMessage[STRING_MAX_MEDIUM] = {0};
    char *s = null;
    char *endPtr = null;
    bool passed = false;

    /* Try to allocate memory, exit if it fails. */
    if (!allocateString(&s, length + EXTRA_SPACES))
        return false;

    sprintf(errorMessage, "%s %d %s %d. %s",
        "You must enter a number between",
        min,
        "and",
        max,
        "Try again.\n"
    );

    /* Keep looping until the user enters the correct integer.
     * If allowEmpty is enabled, the user is allowed to break
     * the loop by entering nothing. */
    while (!passed) {

        /* Ask the user. */
        fputs(message, stdout);

        /* Grab the input. */
        fgets(s, length + EXTRA_SPACES, stdin);

        if (strlen(s) == 1 && s[0] == '\n' && allowEmpty){
            /* User entered nothing, in this case, set the result
             * to one below the minimum to signal this. (along with
             * the function returning true.) */
            *result = min - 1;

            /* Cleanup our mess. */
            freeString(&s);
            break;
        }

        /* The user entered something that is out of range.
         * Inform the user, and consume the rest of the string. */
        if (s[strlen(s) - 1] != '\n') {

            if (showError)
                fputs(errorMessage, stderr);

            readRestOfLine();

        } else {

            /* Terminate the string. */
            s[strlen(s) - 1] = '\0';

            /* Convert the string to a decimal based long. */
            i = (int) strtol(s, &endPtr, BASE10);

            /* Validate the number (if it is indeed a number). */
            if (strcmp(endPtr, "") != 0 || i < min || i > max) {

                /* Only inform the user if we are told to. */
                if (showError){

                    fputs(errorMessage, stderr);

                /* Fail silently. Signal the failure by returning false. */
                } else {

                    /* Set the result to one below the minimum. */
                    *result = min - 1;

                    /* Cleanup before returning the failure flag. */
                    freeString(&s);
                    return false;

                }

            /* The user entered a value that is within range. */
            } else {

                /* Set the result. */
                *result = i;

                /* Set the success flag. */
                passed = true;

                /* Cleanup. */
                freeString(&s);

            }

        }

    }

    /* Success flag. */
    return true;

}

/* This function will get a character array from the user.
 * Depending on the parameters set, it can also show an error message,
 * or totally ignore errors.
 *
 * This function is based on:
 * Source: Steven Burrows
 * URL: https://www.dlsweb.rmit.edu.au/set/Courses/Content/CSIT/oua/cpt220/c-function-examples/InputValidation/getString-advanced.c
 * */
bool getStringFromStdIn(char *result, int length, const char *message,
        int min, bool showError){

    char * s = null;
    char errorMessage[STRING_MAX_MEDIUM] = {0};
    bool passed = false;

    /* Try to allocate memory, exit if it fails. */
    if (!allocateString(&s, length + EXTRA_SPACES))
        return false;

    sprintf(errorMessage, "Invalid entry! Try again.\n");

    /* Keep looping until the user enters a string that is within specified
     * parameters. */
    while (!passed) {

        size_t len;

        /* Ask the user. */
        fputs(message, stdout);

        /* Grab the input. */
        fgets(s, length + EXTRA_SPACES, stdin);

        len = strlen(s);

        /* If the user entered a string that is too long,
         * just consume the rest of the string. */
        if (s[len - 1] != '\n')
            readRestOfLine();

        /* Did the user enter anything? Or did they enter a long string? */
        if (len < EXTRA_SPACES || s[len - 1] != '\n') {

            /* Are we allowed to not enter anything? Abort if so. */
            if (len < EXTRA_SPACES && min == STRING_MIN_NONE)
                passed = true;

            /* Inform the user that they screwed up. */
            else if (showError)
                fputs(errorMessage, stderr);

        /* The user entered a valid string. */
        } else {

            /* Terminate the string. */
            s[len - 1] = '\0';

            /* Copy the string to the result. */
            strcpy(result, s);

            /* Break the loop, and set the success flag. */
            passed = true;

        }

    }

    /* Cleanup. */
    freeString(&s);

    return passed;

}

/* This function is used for dynamic string allocation.
 * It will allocate the required memory, then set allocated bytes to null. */
bool allocateString(char **str, const int size){

    bool result = false;
    /* The required size. */
    const size_t newSize = sizeof(char) * size;
    /* The original size (if any). */
    const size_t oldSize = *str == null ? 0 : sizeof(char) * strlen(*str);

    /* Don't bother allocating 0 memory. */
    if (newSize > 0){

        /* Reallocate memory for the string. */
        *str = realloc(*str, newSize);

        /* Did we succeed? Inform the user if we failed. */
        if (*str == null){

            fputs(ERROR_MEMORY, stderr);

        /* Success. Set all new bytes to null and set the success flag. */
        } else {

            memset(*str + oldSize, 0, newSize - oldSize);
            result = true;

        }

    }

    return result;

}

/* This function is used to delete dynamic strings. */
void freeString(char **str){

    /* Test that we have a valid pointer. */
    if (*str != null){

        /* Free the memory, and set the pointer to null to be safe. */
        free(*str);
        *str = null;

    }

}

/* This function is used to delete an array of dynamic strings. */
void freeStringArray(char **arr, const int length){

    int i = 0;

    /* Loop until the end of the array has been reached. */
    while (i < length)
        /* Call the freeString() method which takes care of cleaning up.
         * Increment the index as well. */
        freeString(&arr[i++]);

}

/* This function is used as a helper function to delete an indefinite
 * number of dynamic strings. */
void freeStrings(const int length, ...){

    int i = 0;
    va_list ap;

    /* Initialise the argument list. */
    va_start(ap, length);

    /* Iterate through the arguments. */
    for (i = 0; i < length; i++)
        /* Call the freeString() method which takes care of cleaning up. */
        freeString(va_arg(ap, char**));

    /* Cleanup the argument list. */
    va_end(ap);

}

/* This callback function is used to sort (qsort()) the array of strings
 * in firstLastStrings(). The first and last strings are then
 * grabbed from the front and back of the result array. */
int wordSeriesSortCallback(const void *a, const void *b){

    const char **ptr1 = (const char **)a;
    const char **ptr2 = (const char **)b;

    /* Perform case insensitive comparison. */
    return strcasecmp(*ptr1, *ptr2);

}

/* This function is used to underline a string in the console. */
char *createDashes(const char *str){

    const int len = strlen(str);
    const int max = (len << 1) + DASH_EXTRA_SPACES; /* including 2 \n's and \0*/
    char *dashes = null;

    /* Did memory allocation succeed? */
    if (allocateString(&dashes, max)){

        /* Append the string. */
        sprintf(dashes, "%s\n", str);

        /* Append the dashes. */
        memset(dashes + (sizeof(char) * strlen(dashes)), DASH_CHAR, len);
        strcat(dashes, "\n");

    }

    return dashes;

}

/* This function plots all the appropriate chess pieces on the chess board. */
void plotChessPieces(const char piece, const int row, const int column,
        char board[][CHESS_COLUMN_MAX + EXTRA_SPACE]){

    int i = 0;
    int j = 0;

    for (i = CHESS_ROW_MIN; i < CHESS_ROW_MAX; i++)
        memset(board[i], CHESS_SQUARE_DEFAULT,
                sizeof(char) * CHESS_COLUMN_MAX);

    switch (piece){

        case eChessBishop:

            /* top left */
            i = row;
            j = column;
            while (--i >= CHESS_ROW_MIN && --j >= CHESS_COLUMN_MIN)
                board[i][j] = CHESS_SQUARE_MOVABLE;

            /* top right */
            i = row;
            j = column;
            while (--i >= CHESS_ROW_MIN && ++j < CHESS_COLUMN_MAX)
                board[i][j] = CHESS_SQUARE_MOVABLE;

            /* bottom left */
            i = row;
            j = column;
            while (++i < CHESS_ROW_MAX && --j >= CHESS_COLUMN_MIN)
                board[i][j] = CHESS_SQUARE_MOVABLE;

            /* bottom right */
            i = row;
            j = column;
            while (++i < CHESS_ROW_MAX && ++j < CHESS_COLUMN_MAX)
                board[i][j] = CHESS_SQUARE_MOVABLE;

            break;

        case eChessRook:

            /* horizontal */
            memset(board[row], CHESS_SQUARE_MOVABLE,
                    sizeof(char) * CHESS_COLUMN_MAX);

            /* vertical */
            for (i = CHESS_ROW_MIN; i < CHESS_ROW_MAX; i++)
                board[i][column] = CHESS_SQUARE_MOVABLE;

            break;
    }

    board[row][column] = piece;

}

/* This function checks if the chess piece corresponds to the chessPiece
 * enumeration values. */
bool isValidChessPiece(const char c){

    /* Chess piece validation. Test against chessPiece enumeration.*/
    return c == eChessRook || c == eChessBishop;

}

/* This function is used to break the main menu option loop by modifying
 * the abort parameter.
 *
 * Requirement  8 - Exit
 * */
void exitApplication(int *abort){

    /* Set the abort flag to true. This in turn will break the main menu loop. */
    *abort = true;

}

/* This function creates the keypad statically,
 * and keeps returning same keypad. I added Q myself since it was missing. */
keypad_t *getKeypad(){

    static keypad_t keypad[] = {
        {2, "ABC"},
        {3, "DEF"},
        {4, "GHI"},
        {5, "JKL"},
        {6, "MNO"},
        {7, "PQRS"}, /* added Q */
        {8, "TUV"},
        {9, "WXYZ"},
        {MAX_KEYPAD, null}
    };

    return keypad;

}

/* This function creates the menu statically, and keeps returning same menu */
menuoption_t *getMenuOptions(){

    static menuoption_t options[] = {
        {
            MIN_MENU_OPTION,
            MENU_TITLE_FIBONACCI,
            true,
            &fibonacciNumbers
        },
        {
            MIN_MENU_OPTION + 1,
            MENU_TITLE_PHONENUMBERS,
            true,
            &phoneNumbers
        },
        {
            MIN_MENU_OPTION + 2,
            MENU_TITLE_FIRSTLASTSTRINGS,
            true,
            &firstLastStrings
        },
        {
            MIN_MENU_OPTION + 3,
            MENU_TITLE_WORDSTOPPING,
            true,
            &wordStopping
        },
        {
            MIN_MENU_OPTION + 4,
            MENU_TITLE_ROOKANDBISHOP,
            true,
            &rookAndTheBishop
        },
        {
            MIN_MENU_OPTION + 5,
            MENU_TITLE_SESSIONSUMMARY,
            false,
            &sessionSummary
        },
        {
            MIN_MENU_OPTION + 6,
            MENU_TITLE_EXIT,
            false,
            &exitApplication
        },
        {MAX_MENU_OPTION, null, false, null}
    };

    return options;

}

/* This function is used to lookup a menu option by it's index. */
menuoption_t *getMenuOptionByIndex(const int index){

    menuoption_t *ptr = getMenuOptions();

    /* Iterate through the menu structure array and look for the index. */
    for (; ptr->index != MAX_MENU_OPTION; ++ptr)
        if (ptr->index == index)
            break;

    /* Return the address of the structure. */
    return &(*ptr);

}

/* This function is used to lookup a menu option by it's title. */
menuoption_t *getMenuOptionByTitle(const char *title){

    menuoption_t *ptr = getMenuOptions();

    /* Iterate through the menu structure array and look for the title. */
    for (; ptr->index != MAX_MENU_OPTION; ++ptr)
        /* Perform case sensitive comparison. */
        if (strcmp(ptr->str, title) == 0)
            break;

    /* Return the address of the structure. */
    return &(*ptr);

}

/* This function is used to modify the optionStat array. */
void statAction(int *optionStats, optionStatAction action, const char *title){

    int i = 0;

    /* Which action needs to be performed? */
    switch (action){

        case eOptionStatReset:

            /* Iterate through menu statistics and reset to zero. */
            for (i = 0; i < NUM_OPTION_STATS; i++)
                optionStats[i] = 0;

            break;

        case eOptionStatIncrement:

            /* Lookup the menu option structure by it's title then
             * increment the statistic by one. */
            optionStats[getMenuOptionByTitle(title)->index - MIN_MENU_OPTION]++;

            break;

        case eOptionStatDecrement:

            /* Lookup the menu option structure by it's title then
             * decrement the statistic by one. */
            optionStats[getMenuOptionByTitle(title)->index - MIN_MENU_OPTION]--;

            break;

    }

}
