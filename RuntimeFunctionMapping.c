#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <sys/mman.h>

/*
** BUILD WITH:
** gcc -Wall -Wextra RuntimeFunctionMapping.c && ./a.out
*/

/*
** FUNCTION X86 ASM DEFINITION
** TO FOUND FUNCTION HEXA CODE -> gcc -c yourfile.c && objdump -D -Mintel yourfile.o
**
** BUILD ASM
** nasm -f elf64 -o assembly.o assembly.asm && ld -o assembly assembly.o && ./assembly
** https://gist.github.com/yellowbyte/d91da3c3b0bc3ee6d1d1ac5327b1b4b2
*/

// OTHER USEFULL LINK
// https://defuse.ca/online-x86-assembler.htm#disassembly
// https://godbolt.org/

// RETURN 42 FUNCTION
// int (*mappedFunction) () = memoryMapping;
// const char runtimeFunction[] = { 0x55, 0x48, 0x89, 0xE5, 0xB8, 0x2A, 0x00, 0x00, 0x00, 0x5D, 0xC3 };

// STRLEN
// int (*mappedFunction) (char *) = memoryMapping;
// const char runtimeFunction[] = {
//     0x55,
//     0x48, 0x89, 0xe5,
//     0x48, 0x89, 0x7d, 0xe8,
//     0xc7, 0x45, 0xfc, 0x00, 0x00, 0x00, 0x00,
//     0xeb, 0x04,
//     0x83, 0x45, 0xfc, 0x01,
//     0x8b, 0x45, 0xfc,
//     0x48, 0x63, 0xd0,
//     0x48, 0x8b, 0x45, 0xe8,
//     0x48, 0x01, 0xd0,
//     0x0f, 0xb6, 0x00,
//     0x84, 0xc0,
//     0x75, 0xe8,
//     0x8b, 0x45, 0xfc,
//     0x5d,
//     0xc3,
// };

// SYSCALL WRITE
// int (*mappedFunction) ()
// const char runtimeFunction[] = {
//     0x55,                                       // push   rbp
//     0x48, 0x89, 0xe5,                           // mov    rbp,rsp
//     0xc7, 0x45, 0xfb, 0x57, 0x54, 0x46, 0x0a,   // mov    DWORD PTR [rbp-0x5],0xa465457
//     0xc6, 0x45, 0xff, 0x00,                     // mov    BYTE PTR [rbp-0x1],0x0
//     0x48, 0xc7, 0xc0, 0x01, 0x00, 0x00, 0x00,   // mov    rax,0x1
//     0x48, 0xc7, 0xc7, 0x01, 0x00, 0x00, 0x00,   // mov    rdi,0x1
//     0x48, 0x8d, 0x75, 0xfb,                     // lea    rsi,[rbp-0x5]
//     0x48, 0xc7, 0xc2, 0x05, 0x00, 0x00, 0x00,   // mov    rdx,0x5
//     0x0f, 0x05,                                 // syscall
//     0x5d,                                       // pop    rbp
//     0xc3,                                       // ret
// };

// EXECVE LS
// int (*mappedFunction) ()
const char runtimeFunction[] = {
    0x55,                                       // push   rbp
    0x48, 0x89, 0xe5,                           // mov    rbp,rsp
    0x48, 0xb8, 0x2f, 0x62, 0x69, 0x6e, 0x2f,   // movabs rax,0x736c2f6e69622f
    0x6c, 0x73, 0x00,
    0x48, 0x89, 0x45, 0xf0,                     // mov    QWORD PTR [rbp-0x10],rax
    0x48, 0xb8, 0x50, 0x57, 0x44, 0x3d, 0x2f,   // movabs rax,0x6d6f682f3d445750
    0x68, 0x6f, 0x6d,
    0x48, 0x89, 0x45, 0xe1,                     // mov    QWORD PTR [rbp-0x1f],rax
    0xc7, 0x45, 0xe9, 0x65, 0x2f, 0x63, 0x6d,   // mov    DWORD PTR [rbp-0x17],0x6d632f65
    0x66, 0xc7, 0x45, 0xed, 0x6f, 0x69,         // mov    WORD PTR [rbp-0x13],0x696f
    0xc6, 0x45, 0xef, 0x00,                     // mov    BYTE PTR [rbp-0x11],0x0
    0x48, 0x8d, 0x45, 0xe1,                     // lea    rax,[rbp-0x1f]
    0x48, 0x89, 0x45, 0xd0,                     // mov    QWORD PTR [rbp-0x30],rax
    0x48, 0xc7, 0x45, 0xd8, 0x00, 0x00, 0x00,   // mov    QWORD PTR [rbp-0x28],0x0
    0x00,
    0x48, 0x8d, 0x45, 0xd0,                     // lea    rax,[rbp-0x30]
    0x48, 0x89, 0x45, 0xf8,                     // mov    QWORD PTR [rbp-0x8],rax
    0x48, 0xc7, 0xc0, 0x3b, 0x00, 0x00, 0x00,   // mov    rax,0x3b
    0x48, 0x8d, 0x7d, 0xf0,                     // lea    rdi,[rbp-0x10]
    0x48, 0x8b, 0x75, 0xf8,                     // mov    rsi,QWORD PTR [rbp-0x8]
    0x48, 0x8b, 0x55, 0xf8,                     // mov    rdx,QWORD PTR [rbp-0x8]
    0x0f, 0x05,                                 // syscall
    0xc3,                                       // ret
};

int main()
{
    /*
    ** SIZE OF THE FUNCTION IN THE MEMORY
    ** sizeof(runtimeFunction) != sizeof(const char)
    */

    size_t functionSize = sizeof(runtimeFunction);

    /*
    ** EXECUTABLE MEMORY SPACE
    */
    void *memoryMapping = mmap(NULL, functionSize, PROT_EXEC | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);

    if (memoryMapping == MAP_FAILED)
        return -1;

    /*
    ** SET FUNCTION IN ALLOCATED SPACE
    */
    memmove(memoryMapping, runtimeFunction, functionSize);

    /*
    ** CAST TO FUNCTION PROTOTYPE
    */
    int (*mappedFunction) () = memoryMapping;

    /*
    ** EXECUTION OF MAPPED FUNCTION
    */
    size_t executionResult = mappedFunction();

    /*
    ** DISPLAY OUTPUT
    */
    printf("execution result -> %li\n", executionResult);

    /*
    ** SPACE ALLOCATION FREE
    */
    if (munmap(memoryMapping, functionSize))
        return -1;

    /*
    ** FUNCTION IS NOW TOTALLY UNAVAILABLE
    */
    return 0;
}