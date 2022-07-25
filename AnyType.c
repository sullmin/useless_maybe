#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

/*
** BUILD WITH:
** gcc -Wall -Wextra AnyType.c && ./a.out
*/

enum ANY_TYPE {
    NONE = 0,
    INT,
    DOUBLE,
    BOOL,
    VAR_CHAR_16
    // ...
};

/*
** THE LIGHTEST SOLUTION
** any_malloc_t have fixed size + malloc size
**
** WARNING CAN BE FAILED DURING INITIALISATION (malloc)
*/
typedef struct any_malloc_s {
    enum ANY_TYPE type;
    void *value;
} any_malloc_t;

/*
** THE EASIEST SOLUTION
** THE MOST READABLE
** ALL any_t SIZE IS DEFINE BY THE BIGGEST TYPE
** IN THIS CASE char[16]
** EVEN IF INT IS STOCKED THE SIZE OF THE BIGGEST OBJECT IS CLAIM
*/
typedef struct any_s {
    enum ANY_TYPE type;
    union {
        void *var_none;
        int var_int;
        double var_double;
        bool var_bool;
        char var_char_16[16];
    } value;
} any_t;

static any_t getVarChar16Any()
{
    any_t space = {0};

    space.type = VAR_CHAR_16;
    memmove(&(space.value), "Hello world !!!", 16);
    return space;
}

static any_malloc_t getVarChar16AnyMalloc()
{
    char *space = malloc(sizeof(char) * 16);

    if (!space)
        exit(-1);
    memmove(space, "Hello world !!!", 16);
    return (any_malloc_t) {VAR_CHAR_16, space};
}

static void displayAny(any_t *src)
{
    switch (src->type)
    {
    case NONE: printf("%p\n", src->value.var_none); break;
    case INT: printf("%i\n", src->value.var_int); break;
    case BOOL: printf("%s\n", (src->value.var_bool) ? "true" : "false"); break;
    case DOUBLE: printf("%f\n", src->value.var_double); break;
    case VAR_CHAR_16: printf("%s\n", (char *) src->value.var_char_16); break;
    default: printf("Unknown type"); break;
    }
}

static void displayAnyMalloc(any_malloc_t *src)
{
    switch (src->type)
    {
    case NONE: printf("%p\n", src->value); break;
    case INT: printf("%i\n", *((int *) src->value)); break;
    case BOOL: printf("%s\n", (*((bool *) src->value)) ? "true" : "false"); break;
    case DOUBLE: printf("%f\n", *((double *) src->value)); break;
    case VAR_CHAR_16: printf("%s\n", (char *) src->value); break;
    default: printf("Unknown type"); break;
    }
}

int main()
{
    any_malloc_t solution_1 = getVarChar16AnyMalloc();
    any_t solution_2 = getVarChar16Any();

    // any_t: 4, any_malloc_t: 16
    printf("any_t: %li, any_malloc_t: %li\n", sizeof(any_t), sizeof(any_malloc_t));

    displayAnyMalloc(&solution_1);
    displayAny(&solution_2);

    free(solution_1.value);
}