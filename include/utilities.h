#ifndef UTILITIES
#define UTILITIES
#include <stdbool.h>
#include <c64/types.h>
#define DEBUG 0
//typedef enum { f, t } bool;

//typedef _Bool bool;
typedef unsigned int uint;
void print_newline(void);
typedef enum Test_Type_E
{
    IS_DIGIT,
    IS_CHARS,
    IS_PRINTABLE,
    IS_BOOL,
    IS_HEX
} Test_Type;

void promptForInput(const char *prompt, char *userInput, byte length);

void substr(byte start, byte length, const char *str, char *sub_str);

word intlen(word num);

bool string_test(char *expr, Test_Type test);

int min(int a, int b);

uint xtouint(const char *str);

void strlower(char *str);

char tolower(char ch);

inline char peek(word address);

inline void poke(word address, char value);
#endif /* UTILITIES */
