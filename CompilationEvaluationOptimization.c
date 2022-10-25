#include <stdio.h>

/*
** BUILD WITH:
** gcc -Wall -Wextra CompilationEvaluationOptimization.c && ./a.out
*/

/*
** SOURCE INTERNET.. I DON'T REMEMBER WHERE
*/

#define COMPILER_PROCESSING_LENGTH(src) sizeof(src) / sizeof(src[0])
#define GET_VAR_NAME(x) #x
#define GET_VAR_CONTENT(x) GET_VAR_NAME(x)

/*
** JUST FOR SAMPLE
*/

#define VALUE 0x42

typedef struct sample_s
{
    int value;
} sample_t;


int main()
{
    /*
    ** SAMPLE_LIST IS NOT a vla.
    ** vla IS A RUNTIME SIZED ARRAY
    ** SAMPLE_LIST SIZE IS KNOWN AT COMPILATION
    */
    const sample_t SAMPLE_LIST[] = {
        (sample_t) { VALUE },
        (sample_t) { VALUE },
        (sample_t) { VALUE },
        (sample_t) { VALUE },
        (sample_t) { VALUE },
        (sample_t) { 0x00 }
    };

    /*
    ** THE CLASSIC SOLUTION TO DETERMINE SAMPLE_LIST LENGTH IS TO ITERATE
    ** BUT WE KNOWN SAMPLE_LIST SIZE AND WE KNOWN SAMPLE_LIST MEMBER SIZE
    ** THUS WE ARE ABLE TO DETERMINE SAMPLE_LIST LENGTH IN COMPILATION
    ** SO WE ARE LESS WORK DURING RUNTIME
    */
    size_t size = 0;
    for (size = 0; SAMPLE_LIST[size].value; size++);

    // CLASSIC
    printf("KEY - %s of size %li conatain 0x%X\n", GET_VAR_NAME(SAMPLE_LIST), size, VALUE);

    /*
    ** IT'S ALSO POSSIBLE TO INJECT INFORMATION DIRECTLY IN STRING
    ** THUS, IT'S UNECESSARY TO CALL COMPLEXE PRINTF
    */

    // OPTIMIZED
    printf("KEY - " GET_VAR_NAME(SAMPLE_LIST) " of size %li conatain " GET_VAR_CONTENT(VALUE) "\n", COMPILER_PROCESSING_LENGTH(SAMPLE_LIST));

    /*
    ** I ENCOURAGE YOU, TO CHECK THE DIFFERENCE BETWEEN THESE TWO STRINGS IN THE BINARY
    ** strings a.out | grep KEY
    */

    /*
    ** THE DIFFERENCE OF LENGTH IS DUE TO THE FACT THAT COMPILER_PROCESSING_LENGTH COUNT THE LAST MEMBER (sample_t) { 0x00 }
    ** AND THE RUNTIME FUNCTION NONE
    */
}

/*
** TO OPTIMIZED YOUR RUNTIME EXECUTION,DO AS MUCH WORK AS POSSIBLE WHEN COMPILING
** WHEN THIS WORK IS DOWN YOU CAN ADD COMPILATION FLAGS
** IN LAST YOU CAN EXPLICITLY DESCRIBE HOT AND COLD FUNCTION / LIKELY AND UNLIKELY BRANCH
*/