#include <stdio.h>
#include <stddef.h>

/*
** BUILD WITH:
** gcc -Wall -Wextra ContainerOf.c && ./a.out
*/

/*
** Linux Karnel DEFINITION of container_of
*/
#define container_of(ptr, type, member) ({                      \
        const typeof( ((type *)0)->member ) *__mptr = (ptr);    \
        (type *)( (char *)__mptr - offsetof(type,member) );})

/*
** typeof IS A MACRO WHO INJECT THE TYPE OF THE VARIABLE WHICH IS IN PARAMETER
** offsetof IS A MACRO WHO RETURN THE OFFSET OF MEMBER IN STRUCT
**             +-------+
**   parent -> |       |
**             |       |
**    <offset> |       |
**             |       |
**      ptr -> |       |
**             |       |
**             |       |
**             +-------+
** __mptr IS THE VALUE OF ptr BUT TYPED
** offsetof(type,member) RETURN THE NUMBER OF BYTES BETWEEN type START AND member
** SO WITH THE __mptr WE SUBTRACT THIS offset TO FIND WHICH CONTAINS IT
*/

typedef struct child_s {
    int useless;
} child_t;

typedef struct parent_s {
    int useless1;
    child_t child;
    int useless2;
} parent_t;

int main()
{
    parent_t parent = {
        0x42,
        (child_t) { 0x42 },
        0x42
    };
    const parent_t *source = container_of(&parent.child, parent_t, child);

    printf("parent: %p - container_of: %p\n", &parent, source);
}