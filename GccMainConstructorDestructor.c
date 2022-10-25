#include <stdio.h>

/*
** BUILD WITH:
** gcc -Wall -Wextra GccMainConstructorDestructor.c && ./a.out
*/

__attribute__((constructor))
static void constructor() {
  printf("Execution -> %s\n", __PRETTY_FUNCTION__);
}

__attribute__((destructor))
static void destructor() {
  printf("Execution -> %s\n", __PRETTY_FUNCTION__);
}

int main()
{
    return printf("Execution -> %s\n", __PRETTY_FUNCTION__);
}