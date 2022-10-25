#include <stdio.h>
#include <stdbool.h>

/*
** BUILD WITH:
** gcc -Wall -Wextra Auto.c && ./a.out
*/

/*
** SOURCE -> https://www.youtube.com/watch?v=ghjFIRXjg7U
** I'M NOT THE FOUNDER OF THIS MACRO, I HEARD ABOUT IT IN THIS 42's TALK.
*/

/*
** typeof IS A MACRO WHO INJECT THE TYPE OF THE VARIABLE WHICH IS IN PARAMETER
** USING IT WE ARE ABLE TO MAKE ANOTHER MACRO WHO WORK AS C++ std::auto
** name IS THE VARIABLE NAME
** value IS THE VALUE THAT WILL BE ATTRIBUTE TO THE VARIABLE
**
** AUTO(integer, 42); -> typeof(42) integer = 42; -> int integer = 42;
*/

#define AUTO(name, value) typeof(value) name = value;

int main()
{
    AUTO(boolean, true);
    AUTO(integer, 42);
    AUTO(var_char, "what!!!");

    printf("%s\n", (boolean) ? "true" : "false");
    printf("%i\n", integer);
    printf("%s\n", var_char);
}