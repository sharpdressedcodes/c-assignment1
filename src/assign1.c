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

    int i = 0;
    int option = 0;
    char *menu = null;
    bool abort = false;

    if (!allocateString(&menu, STRING_MAX_LARGE))
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

        /* NUM_OPTION_STATS + 1 to count the exit option. */
        if (getIntegerFromStdIn(&option, MAX_OPTION_INPUT, menu, BASE1, NUM_OPTION_STATS + 1, true, false)) {
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

    freeString(&menu);

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

    if (!allocateString(&message, STRING_MAX_MEDIUM) ||
        !allocateString(&fibMax, STRING_MAX_MEDIUM)){
        freeStrings(2, &message, &fibMax);
        return;
    }

    sprintf(fibMax, "%d", MAX_OPTION_FIBONACCI);
    sprintf(message, "Enter a positive integer (%d-%d): ",
        MIN_OPTION_FIBONACCI,
        MAX_OPTION_FIBONACCI
    );

    if (getIntegerFromStdIn(&limit, strlen(fibMax), message, MIN_OPTION_FIBONACCI, MAX_OPTION_FIBONACCI, false, true)) {

        printf("Fibonacci sequence for %d terms:\n", limit);

        for (i = 0; i < limit; i++) {

            int fibonacci = i <= FIBONACCI_NUM2 ? i : num1 + num2;

            if (i > FIBONACCI_NUM2) {
                num1 = num2;
                num2 = fibonacci;
            }

            sum += fibonacci;
            printf(i == limit ? "%-8d" : "%-8d ", fibonacci);

        }

        average = (float) sum / i;

        printf("\nSum: %d\n", sum);
        printf("Average: %.2f\n", average);

        optionStats[eFibonacciSeries]++;

    }

    freeStrings(2, &message, &fibMax);

}

/*
 * Function phoneNumbers() A function that translates an alphabetic phone number into numeric form.This is menu option number 2
 */
void phoneNumbers(int *optionStats) {

    int i = 0 ;
    char *input = null;
    char *output = null;
    char *message = null;
    keypad_t *ptr, keypad[] = {
        {2, "ABC"},
        {3, "DEF"},
        {4, "GHI"},
        {5, "JKL"},
        {6, "MNO"},
        {7, "PQRS"}, /* added Q */
        {8, "TUV"},
        {9, "WXYZ"}, /* added W */
        {MAX_KEYPAD, null}
    };

    if (!allocateString(&input, STRING_MAX_MEDIUM) ||
        !allocateString(&output, STRING_MAX_MEDIUM) ||
        !allocateString(&message, STRING_MAX_MEDIUM)){
        freeStrings(3, &input, &output, &message);
        return;
    }

    sprintf(message, "Enter phone number (max %d characters): ", STRING_MAX_MEDIUM);

    if (getStringFromStdIn(&input, STRING_MAX_MEDIUM, message, STRING_MIN_NONE, true) && strlen(input) > 0){

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

        optionStats[ePhoneNumberConversion]++;

    }

    freeStrings(3, &input, &output, &message);

}

/*
 Function firstLastStrings(). This function that finds the "first" and "last" words in a series of words.
 After the user enters the words, the function will determine which words would come first and last if the
 words were listed in dictionary order. The function must stop accepting input when the user enters a blank line,
 eg. just presses enter. Assume that no word is more than 20 letters long. An interactive session with the function might look like this:
 This is menu option number 3 */

void firstLastStrings(int *optionStats) {

    int bufferCount = 0;
    int bufferPower = START_POWER;
    char *input = null;
    char *message = null;
    char *dashed = createDashes("Finding strings");
    char *buffer[STRING_MAX_LARGE];
    bool passed = false;

    if (!allocateString(&input, STRING_MAX_SMALL) ||
        !allocateString(&message, STRING_MAX_MEDIUM)){
        freeStrings(3, &input, &message, &dashed);
        return;
    }

    printf("%s\n", dashed);
    sprintf(message, "Enter word (%d-%d characters, %c to finish): ", STRING_MIN, STRING_MAX_SMALL, FIRST_LAST_FINISH_CHAR);

    while (!passed){

        if (!getStringFromStdIn(&input, STRING_MAX_SMALL, message, STRING_MIN_NONE, true)){

            /*if (strlen(input) == STRING_MIN_NONE){
                freeStrings(3, &input, &message, &dashed);
                freeStringArray(buffer, bufferCount);
                return;
            }*/

        } else {

            if (strlen(input) == STRING_MIN_NONE){
                freeStrings(3, &input, &message, &dashed);
                freeStringArray(buffer, bufferCount);
                return;
            }

            else if (strlen(input) == STRING_MIN && tolower(input[0]) == FIRST_LAST_FINISH_CHAR){

                if (bufferCount < MIN_OPTION_WORD_SERIES){

                    fprintf(stderr, "You must enter at least %d words\n", MIN_OPTION_WORD_SERIES);

                } else {

                    qsort(buffer, bufferCount, sizeof(char*), wordSeriesSortCallback);

                    printf(
                        "Smallest Word: %s\nLargest Word %s\n",
                        buffer[0],
                        buffer[bufferCount - 1]
                    );

                    optionStats[eFirstLastStrings]++;

                    freeStrings(3, &input, &message, &dashed);
                    freeStringArray(buffer, bufferCount);

                    passed = true;

                }

            } else {

                buffer[bufferCount] = null;

                if (!allocateString(&buffer[bufferCount], strlen(input) + 1)){
                    freeStrings(3, &input, &message, &dashed);
                    freeStringArray(buffer, bufferCount);
                    return;
                }

                strcpy(buffer[bufferCount], input);

                if (bufferCount >= STRING_MAX_LARGE * bufferPower){

                    if (!allocateString(&buffer[bufferCount], STRING_MAX_LARGE * ++bufferPower)){
                        freeStrings(3, &input, &message, &dashed);
                        freeStringArray(buffer, bufferCount);
                        return;
                    }

                }

                memset(input, 0, sizeof(char) * STRING_MAX_SMALL);
                bufferCount++;

            }

        }

    }

}

/*
 * Function substrings() Many search engines (such as Google), implement "stopping" so that
 * commonly occurring query words are ignored for the purposes of ranking query results.
 * In this option, you will need to prompt the user for a string of 1-20 characters.
 * You will need to output the string with all words of length 1-3 characters "stopped".
 This is menu option number 4
 */

void wordStopping(int *optionStats) {

    char *chr = null;
    char *input = null;
    char *message = null;
    char *buffer = null;
    char delim[] = {WORD_SEPARATOR, '\0'};
    int i = 0;

    if (!allocateString(&input, STRING_MAX_SMALL + 1) ||
        !allocateString(&buffer, STRING_MAX_SMALL + 1) ||
        !allocateString(&message, STRING_MAX_MEDIUM + 1)){
        freeStrings(3, &input, &buffer, &message);
        return;
    }

    sprintf(message, "Enter a string (%d-%d characters): ", STRING_MIN, STRING_MAX_SMALL);

    do {
        if (i++ == 0)
            memset(input, 0, sizeof(char) * STRING_MAX_SMALL + 1);
    } while (!getStringFromStdIn(&input, STRING_MAX_SMALL, message, STRING_MIN_NONE, true));

    if (strlen(input) == 0){
        freeStrings(3, &input, &buffer, &message);
        return;
    }

    chr = strtok(input, delim);

    if (chr == null){

        strcpy(buffer, input);

    } else {

        while (chr != null){

            if (strlen(chr) > MIN_OPTION_WORD_STOPPER){

                if (strlen(buffer) == 0){

                    strcpy(buffer, chr);

                } else {

                    strcat(buffer, delim);
                    strcat(buffer, chr);

                }

            }

            chr = strtok(null, delim);

        }

    }

    if (strlen(buffer) == 0)
        puts("All words have been stopped.");
    else
        printf("\nStopped string: %s\n", buffer);

    optionStats[eWordStopping]++;


    /*while (!getStringFromStdIn(&input, STRING_MAX_SMALL, message, true)){

        if (tolower(input[0]) == QUIT_CHAR){
            freeStrings(3, &input, &buffer, &message);
            return;
        }

        chr = strtok(input, delim);

        if (chr == null){

            strcpy(buffer, input);

        } else {

            while (chr != null){

                if (strlen(chr) > MIN_OPTION_WORD_STOPPER){

                    if (strlen(buffer) == 0){

                        strcpy(buffer, chr);

                    } else {

                        strcat(buffer, delim);
                        strcat(buffer, chr);

                    }

                }

                chr = strtok(null, delim);

            }

        }

        printf("\nStopped string: %s\n", buffer);
        optionStats[eWordStopping]++;

    }*/

    /*if (getStringFromStdIn(&input, STRING_MAX_SMALL, message, false)){

        chr = strtok(input, delim);

        if (chr == null){

            strcpy(buffer, input);

        } else {

            while (chr != null){

                if (strlen(chr) > MIN_OPTION_WORD_STOPPER){

                    if (strlen(buffer) == 0){

                        strcpy(buffer, chr);

                    } else {

                        strcat(buffer, delim);
                        strcat(buffer, chr);

                    }

                }

                chr = strtok(null, delim);

            }

        }

        printf("\nStopped string: %s\n", buffer);
        optionStats[eWordStopping]++;

    }*/

    freeStrings(3, &input, &buffer, &message);

}

/* Function rookAndTheBishop() A rook can only move either horizontally or vertically. 
 A bishop can only move diagonally.
 * menu option 5.
 */
void rookAndTheBishop(int *optionStats) {

    int i = 0;
    int j = 0;
    int row = 0;
    int column = 0;
    char chr = null;
    char *piece = null;
    char *message = null;
    char board[CHESS_ROW_MAX + 1][CHESS_COLUMN_MAX + EXTRA_SPACES] = {{0}};
    bool passed = false;

    if (!allocateString(&piece, MAX_OPTION_INPUT + 1) ||
        !allocateString(&message, STRING_MAX_MEDIUM)){
        freeStrings(2, &piece, &message);
        return;
    }

    sprintf(message, "Enter Piece type (%c/%c): ", eChessRook, eChessBishop);

    while (!passed){

        if (piece[0] != '\0')
            memset(piece, 0, MAX_OPTION_INPUT + 1);

        if (getStringFromStdIn(&piece, MAX_OPTION_INPUT, message, STRING_MIN_NONE, true)){

            if (strlen(piece) == 0){
                freeStrings(2, &piece, &message);
                return;
            }

            chr = toupper(piece[0]);

            if (!isValidChessPiece(chr))
                fputs("Invalid piece. Try again.\n", stderr);
            else
                passed = true;

        }

    }

    passed = false;
    memset(message, 0, STRING_MAX_MEDIUM);
    sprintf(message, "Row (%d..%d): ", CHESS_ROW_MIN, CHESS_ROW_MAX - 1);

    while (!passed){

        if (getIntegerFromStdIn(&row, MAX_OPTION_INPUT, message, CHESS_ROW_MIN, CHESS_ROW_MAX - 1, true, true)){

            if (row == CHESS_ROW_MIN - 1){
                freeStrings(2, &piece, &message);
                return;
            }

            passed = true;
        }

    }

    passed = false;
    memset(message, 0, STRING_MAX_MEDIUM);
    sprintf(message, "Column (%d..%d): ", CHESS_COLUMN_MIN, CHESS_COLUMN_MAX - 1);

    while (!passed){

        if (getIntegerFromStdIn(&column, MAX_OPTION_INPUT, message, CHESS_COLUMN_MIN, CHESS_COLUMN_MAX - 1, true, true)){

            if (column == CHESS_COLUMN_MIN - 1){
                freeStrings(2, &piece, &message);
                return;
            }

            passed = true;
        }

    }

    for (i = CHESS_ROW_MIN; i < CHESS_ROW_MAX; i++){
        memset(board[i], CHESS_SQUARE_DEFAULT, sizeof(char) * CHESS_COLUMN_MAX);
        board[i][CHESS_COLUMN_MAX] = '\n';
    }

    switch (chr){

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
            memset(board[row], CHESS_SQUARE_MOVABLE, sizeof(char) * CHESS_COLUMN_MAX);
            /* vertical */
            for (i = CHESS_ROW_MIN; i < CHESS_ROW_MAX; i++)
                board[i][column] = CHESS_SQUARE_MOVABLE;

            break;
    }

    board[row][column] = chr;

    for (i = CHESS_ROW_MIN; i < CHESS_ROW_MAX; i++)
        fputs(board[i], stdout);

    optionStats[eRookAndBishop]++;

    freeStrings(2, &piece, &message);

}

/* See requirement #7  "Session summary" of the assignment specs.
 * Function sessionSummary() reports the program usage.
 */
void sessionSummary(int *optionStats) {

    char *title = "Session summary";
    char *option = "Option";
    char *count = "Count";
    char *dashed = createDashes(title);
    char *spaces = null;
    char *optionDashes = null;
    char *countDashes = null;
    int i = 0;
    int spaceLength = strlen(title) - strlen(option) - strlen(count);

    if (!allocateString(&spaces, spaceLength + 1) ||
        !allocateString(&optionDashes, strlen(option) + 1) ||
        !allocateString(&countDashes, strlen(count) + 1)){
        freeStrings(4, &spaces, &optionDashes, &countDashes, &dashed);
        return;
    }

    memset(spaces, SPACE_CHAR, spaceLength);
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

    for (; i < trackedMethodMax; i++)
        printf("%6d%s%5d\n", BASE1 + i, spaces, optionStats[i]);

    freeStrings(4, &spaces, &optionDashes, &countDashes, &dashed);

}

/*
 * Function readRestOfLine() is used for buffer clearing. Source:
 */

void readRestOfLine() {

    int c;

    /* Read until the end of the line or end-of-file. */
    /*while ((c = fgetc(stdin)) != '\n' && c != EOF)
        ;*/

    int count = 0;
    while ((c = fgetc(stdin)) != '\n' && c != EOF)
        printf("%d consumed %c\n", count++, c);

    /* Clear the error and end-of-file flags. */
    clearerr(stdin);

}

bool getIntegerFromStdIn(int *result, int length, const char *message, int min, int max, bool showError, bool allowEmpty){

    int i = 0;
    char *s = null;
    char *s2 = null;
    char *errorMessage = null;
    bool passed = false;

    if (!allocateString(&s, length + EXTRA_SPACES) ||
        !allocateString(&errorMessage, STRING_MAX_MEDIUM)){
        freeStrings(2, &s, &errorMessage);
        return false;
    }

    sprintf(errorMessage, "%s %d %s %d. %s",
        "You must enter a number between",
        min,
        "and",
        max,
        "Try again.\n"
    );

    while (!passed) {

        fputs(message, stdout);
        fgets(s, length + EXTRA_SPACES, stdin);

        if (strlen(s) == 1 && s[0] == '\n' && allowEmpty){
            *result = min - 1;
            freeStrings(2, &s, &errorMessage);
            break;
        }

        if (s[strlen(s) - 1] != '\n') {

            fputs(errorMessage, stderr);
            readRestOfLine();

        } else {

            s[strlen(s) - 1] = '\0';
            i = (int) strtol(s, &s2, BASE10);

            if (strcmp(s2, "") != 0 || i < min || i > max) {

                if (showError){

                    fputs(errorMessage, stderr);

                } else {

                    *result = 0;
                    /*passed = true;*/

                    freeStrings(2, &s, &errorMessage);
                    return false;

                }

            } else {

                *result = i;
                passed = true;

                freeStrings(2, &s, &errorMessage);

            }

        }

    }

    return true;

}

bool getStringFromStdIn(char **result, int length, const char *message, int min, bool showError){

    char *s = null;
    char *errorMessage = null;
    bool passed = false;

    if (!allocateString(&s, length + EXTRA_SPACES) ||
        !allocateString(&errorMessage, STRING_MAX_MEDIUM)){
        freeStrings(2, &s, &errorMessage);
        return false;
    }

    if (showError)
        sprintf(errorMessage, "Invalid entry! Try again.\n");

    while (!passed) {

        size_t len;

        fputs(message, stdout);
        fgets(s, length + EXTRA_SPACES, stdin);

        len = strlen(s);

        if (s[len - 1] != '\n')
            readRestOfLine();

        if (len < EXTRA_SPACES || s[len - 1] != '\n') {

            if (len < EXTRA_SPACES && min == STRING_MIN_NONE)
                /*break;*/
                passed = true;

            else if (showError)
                fputs(errorMessage, stderr);

        } else {

            s[len - 1] = '\0';
            strcpy(*result, s);
            passed = true;

        }

    }

    freeStrings(2, &s, &errorMessage);

    return passed;

    /*while (!passed) {

        size_t len;

        fputs(message, stdout);
        fgets(s, length + EXTRA_SPACES, stdin);

        len = strlen(s);

        if (len < EXTRA_SPACES || s[len - 1] != '\n') {

            if (s[len - 1] != '\n')
                readRestOfLine();

            if (showError){

                fputs(errorMessage, stderr);

            } else {

                strcpy(*result, "\0");
                freeStrings(2, &s, &errorMessage);

                return false;

            }

        } else {

            s[len - 1] = '\0';
            strcpy(*result, s);
            passed = true;

            freeStrings(2, &s, &errorMessage);

        }

    }

    return true;*/

}

bool allocateString(char **str, int size){

    bool result = false;
    size_t newSize = sizeof(char) * size;
    size_t oldSize = *str == null ? 0 : sizeof(char) * strlen(*str);

    if (newSize > 0){

        *str = realloc(*str, newSize);

        if (*str == null){

            fputs(ERROR_MEMORY, stderr);

        } else {

            memset(*str + oldSize, 0, newSize - oldSize);
            result = true;

        }

    }

    return result;

}

void freeString(char **str){

    if (*str != null){

        free(*str);
        *str = null;

    }

}

void freeStringArray(char **arr, int length){

    int i = 0;

    while (i < length)
        freeString(&arr[i++]);

}

void freeStrings(int length, ...){

    int i = 0;
    va_list ap;

    va_start(ap, length);

    for (i = 0; i < length; i++)
        freeString(va_arg(ap, char**));

    va_end(ap);

}

int wordSeriesSortCallback(const void *a, const void *b){

    const char **ptr1 = (const char **)a;
    const char **ptr2 = (const char **)b;

    return strcasecmp(*ptr1, *ptr2);

}

char *createDashes(const char *str){

    int len = strlen(str);
    int max = (len << 1) + DASH_EXTRA_SPACES; /* including 2 \n's and \0*/
    char *dashes = null;

    if (allocateString(&dashes, max)){

        sprintf(dashes, "%s\n", str);
        memset(dashes + (sizeof(char) * strlen(dashes)), DASH_CHAR, len);
        strcat(dashes, "\n");

    }

    return dashes;

}

bool isValidChessPiece(char c){

    return c == eChessRook || c == eChessBishop;

}
