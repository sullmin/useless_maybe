#include <stdio.h>
#include <stdbool.h>

/*
** BUILD WITH:
** gcc -Wall -Wextra CleanGlobalVariable.c && ./a.out
*/

/*
** CREATE EDITABLE GLOBAL VARIABLE
** WITHOUT GENARATE GLOBAL VARIABLE
** val          -> value that will set in constante
** mustBeSet    -> if true constant will take val value else nothing change
** return       -> always return current constant value
*/
static int constantManager(int val, bool mustBeSet)
{
    static int constant = 0;

    if (mustBeSet)
        constant = val;
    return constant;
}

int main()
{
    // THIS IS SCOPE
    // {
    // }
    {
        printf("%i\n", constantManager(0, false));
    }
    {
        printf("%i\n", constantManager(42, true));
    }
    {
        printf("%i\n", constantManager(84, false));
    }
    {
        printf("%i\n", constantManager(0, true));
    }
}