#include <stdio.h>

/*
** BUILD WITH:
** gcc -Wall -Wextra EasyFlagsGestion.c && ./a.out
*/

/*
** DEFINE ALL YOUR FLAGS IN ENUM
** DEFAULT FLAGS AS THE VALUE 0
** OTHER FLAGS MUST HAVE POWER 2 VALUES
*/
enum FLAG_LIST {
    DEFAULT = 0x00, // b 000000
    VALUE_1 = 0x01, // b 000001
    VALUE_2 = 0x02, // b 000010
    VALUE_3 = 0x04, // b 000100
    VALUE_4 = 0x08, // b 001000
    VALUE_5 = 0x10, // b 010000
    VALUE_6 = 0x20, // b 100000
};

static int generateFlags()
{
    int flag = DEFAULT;

    /*
    ** TO ADDING OR REMOVE VALUE IN FLAG YOU MUST USE XOR
    **
    ** ADD VALUE
    ** b 000000 XOR b 000001 XOR b 000100 XOR b 100000
    ** b 100101
    **
    ** REMOVE VALUE
    ** b 100101 XOR b 000001
    ** b 100100
    */
    return flag ^ VALUE_1 ^ VALUE_3 ^ VALUE_6;
}

static void checkMatchingFlag(int source, int toCompare, char *match, char *failed)
{
    /*
    ** TO VERIFY IF VALUE IS CONTAIN IN FLAG YOU MUST USE AND
    ** IF FLAG & VALUE != 0 VALUE IS CONTAIN IN FLAG
    ** ELSE VALUE IS NOT CONTAIN
    ** BE CAREFULE IF YOUR VALUE IS 0, IT'S NOT WORK AND MUST BE CHECK MANUALLY
    */
    char *toDisplay = (source & toCompare) ? match : failed;

    printf("%s\n", toDisplay);
}

int main()
{
    int pairFlag = VALUE_2 ^ VALUE_4 ^ VALUE_6;
    int impairFlag = VALUE_1 ^ VALUE_3 ^ VALUE_5;
    int noMatchFlag = VALUE_2 ^ VALUE_4 ^ VALUE_5;
    int flag = generateFlags();

    checkMatchingFlag(flag, pairFlag, "Flag contain pair FLAG_LIST.", "Flag don't contain pair FLAG_LIST.");
    checkMatchingFlag(flag, impairFlag, "Flag contain impair FLAG_LIST.", "Flag don't contain impair FLAG_LIST.");
    checkMatchingFlag(flag, noMatchFlag, "Flag match someting.", "Flag match nothing.");

    /*
    ** REMOVE FLAG AFTER DECLARATION
    */
    flag ^= VALUE_6;
    checkMatchingFlag(flag, pairFlag, "Flag contain pair FLAG_LIST.", "Flag don't contain pair FLAG_LIST.");

    /*
    ** ADDING FLAG AFTER DECLARATION
    */
    flag ^= VALUE_4;
    checkMatchingFlag(flag, noMatchFlag, "Flag match someting.", "Flag match nothing.");

    /*
    ** CHECK ONCE FLAG
    */
    checkMatchingFlag(flag, VALUE_1, "Flag match VALUE_1.", "Flag don't match VALUE_1.");
    checkMatchingFlag(flag, VALUE_2, "Flag match VALUE_2.", "Flag don't match VALUE_2.");
    checkMatchingFlag(flag, VALUE_3, "Flag match VALUE_3.", "Flag don't match VALUE_3.");
    checkMatchingFlag(flag, VALUE_4, "Flag match VALUE_4.", "Flag don't match VALUE_4.");
    checkMatchingFlag(flag, VALUE_5, "Flag match VALUE_5.", "Flag don't match VALUE_5.");
    checkMatchingFlag(flag, VALUE_6, "Flag match VALUE_6.", "Flag don't match VALUE_6.");

    /*
    ** WARNING
    ** DEFAULT FLAG CAN'T BE TESTED AS OTHER FLAG BECAUSE HIS VALUE IS 0
    */
    if (!flag)
        printf("Flag is default value.\n");
    else
        printf("Flag is not default value.\n");
    return 0;
}