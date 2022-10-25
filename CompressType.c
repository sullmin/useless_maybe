#include <stdio.h>
#include <stdbool.h>

/*
** BUILD WITH:
** gcc -Wall -Wextra CompressType.c && ./a.out
*/

/*
** ENUM SAMPLE
** MAX VALUE 0x4 -> CAN BE SAVE IN 3 BITS
*/
enum FLAG {
    DEFAULT = 0x00,     // b 000
    SAMPLE_1 = 0x01,    // b 001
    SAMPLE_2 = 0x02,    // b 010
    SAMPLE_3 = 0x04,    // b 100
};

/*
** CLASSIC STRUCT DEFINITION
** sample_1         -> 4 BYTES
** sample_2         -> 4 BYTES
** sample_3         -> 1 BYTES
** sample_4         -> 1 BYTES
** memory_padding   -> 2 BYTES
** TOTAL            -> 12 BYTES
*/
typedef struct sample_s {
    enum FLAG sample_1;
    enum FLAG sample_2;
    bool sample_3;
    bool sample_4;
} sample_t;

/*
** CUSTOM STRUCT DEFINITION
** sample_1         -> 3 BITS
** sample_2         -> 3 BITS
** sample_3         -> 1 BITS
** sample_4         -> 1 BITS
** memory_padding   -> 0 BYTE
** TOTAL            -> 1 BYTE
*/
typedef struct compress_sample_s {
    enum FLAG sample_1 : 3;                     // 3 BECAUSE THE BIGGEST ENUM VALUE IS b 100, THUS 3 BITS
    enum FLAG sample_2 : 3;                     // 3 BECAUSE THE BIGGEST ENUM VALUE IS b 100, THUS 3 BITS
    bool sample_3 : 1;                          // 1 BECAUSE BOOLEAN IS 0 OR ONE, THUS 1 BITS
    bool sample_4 : 1;                          // 1 BECAUSE BOOLEAN IS 0 OR ONE, THUS 1 BITS
} __attribute__((packed)) compress_sample_t;    // __attribute__((packed)) IS INTERPRATED BY GCC AND REMOVE MEMORY PADDING

/*
** VERIFY IF DATA IS LOOSE BETWEEN THESE 2 STRUCT
*/
static void areEqual(sample_t raw, compress_sample_t compress)
{
    if (raw.sample_1 != compress.sample_1)
        printf("sample_1 are not equal. %i != %i\n", raw.sample_1, compress.sample_1);
    else
        printf("sample_1 are equal.\n");
    if (raw.sample_2 != compress.sample_2)
        printf("sample_2 are not equal. %i != %i\n", raw.sample_2, compress.sample_2);
    else
        printf("sample_2 are equal.\n");
    if (raw.sample_3 != compress.sample_3)
        printf("sample_3 are not equal. %i != %i\n", raw.sample_3, compress.sample_3);
    else
        printf("sample_3 are equal.\n");
    if (raw.sample_4 != compress.sample_4)
        printf("sample_4 are not equal. %i != %i\n", raw.sample_4, compress.sample_4);
    else
        printf("sample_4 are equal.\n");
}

int main()
{
    sample_t raw = {SAMPLE_1, SAMPLE_3, true, false};
    compress_sample_t compress = {SAMPLE_1, SAMPLE_3, true, false};

    // OUPUT -> "raw: 12, compress: 1"
    printf("raw: %li, compress: %li, int: %li\n", sizeof(sample_t), sizeof(compress_sample_t), sizeof(int));
    areEqual(raw, compress);

    bool correct = *((bool *) &compress);
    printf("Compressed struct as bool (%i).\n", correct);

    compress_sample_t noDataLoose = *((compress_sample_t *) &correct);
    areEqual(raw, noDataLoose);

    /*
    ** THIS CODE GENERATE VALGRIND ERROR DUE TO INVALID READ SIZE
    ** BOOL (1 BYTE) -> STRUCT (12 BYTES)
    */
    // bool incorrect = *((bool *) &raw);
    // printf("Raw struct as bool (%i).\n", incorrect);
    // sample_t dataLoose = *((sample_t *) &incorrect);
    // areEqual(dataLoose, noDataLoose);
}

/*
** WARNING
**
** THIS STRUCT TIPS MUST BE USE WHEN YOU MAKE COMPUTER FRAME, TO OPTIMIZE YOUR TRANSMITION SIZE
** BUT BE CAREFUL IF YOU USE IT, IN OTHER CONTEXT BECAUSE IT'S CAN DEGREADED YOUR PERFORMANCE DUE TO UNALIGNED MEMORY
**
** OLD ARCHITECTURE OR SOME ARM ARCHITECTURE CAN THROW EXCEPTION
**
** VERY GOOD CONTENT ->
** https://research.nccgroup.com/2019/10/30/padding-the-struct-how-a-compiler-optimization-can-disclose-stack-memory/#:~:text=In%20their%20eternal%20quest%20for,aligned%20and%20is%20therefore%20faster.
*/