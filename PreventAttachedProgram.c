#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdbool.h>
#include <sys/ptrace.h>

/*
** BUILD WITH:
** gcc -Wall -Wextra PreventAttachedProgram.c && ./a.out
*/

static bool prevent_attach()
{
    /*
    ** ptrace function attach the current process to other one
    ** the process can controle the one who is attach
    **
    ** ptrace is used by debbuger to analized our program during runtime
    **
    ** in our case we attach our self to prevent other process to attach ourself
    */
    return ptrace(PT_TRACE_ME) != -1;
}

int main()
{
    if (!prevent_attach())
        return 84;
    printf("oui\n");
    /*
    ** PTRACE can't be detach because
    ** the program must be stopped before it
    */
    return 0;
}