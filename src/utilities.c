#include <c64/types.h>
#include <conio.h>
#include <petscii.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "utilities.h"

char tolower(char ch) { return ch - 31; }

void strlower(char *str)
{
    byte i = 0;
    while (str[i] != '\0')
    {
        str[i] = tolower(str[i]);
    }
}

word intlen(word num)
{
    word count = 0;
    while (num != 0)
    {
        num /= 10;
        count++;
    }
    return count;
}

void promptForInput(const char *prompt, char *userInput, byte length)
{
    char lastChar = prompt[strlen(prompt) - 1];
#if DEBUG == 1
    printf("[DEBUG]: '%C'\n", lastChar);
#endif
    if (lastChar != ' ')
        printf("%S\n", prompt);
    else
        printf("%S", prompt);

    byte i = 0;
    while (i < length)
    {
        char inputChar = getchar();
        if (inputChar != '\n')
        {
            userInput[i] = inputChar;
            i++;
        }
        else
        {
            break;
        }
    }
#if DEBUG == 1
    putch('\n');
    printf("%d", i);
#endif

    print_newline();

    userInput[i] = '\0';
}

void print_newline(void) { printf("\n"); }

int min(int a, int b)
{
    if (a < b)
    {
        return a;
    }
    else
    {
        return b;
    }
}

void substr(byte start, byte length, const char *str, char *sub_str)
{
    byte i = start;
    byte j = 0;
    // if (strlen(sub_str)< min(strlen(str), length))
    // {
    //     printf("error! substr too short");
    //     exit(1);
    // }
    while (i < length && str[i] != '\0' && sub_str[j] != '\0')
    {
        sub_str[j] = str[i];
        i++;
        j++;
    }
    sub_str[j] = '\0';
}

/**
 * xtouint
 * Take a hex string and convert it to an int  (max 4 hex digits).
 * The string must only contain digits and valid hex characters.
 *
 * Source: https://stackoverflow.com/a/57112610
 */
uint xtouint(const char *str)
{
    uint res = 0;
    char c;
    byte i = 0;

    while ((str[i] != '\0'))
    {
        c = str[i];
        if (c > 0x5a || c > 0x7a)
        {
            c = tolower(c);
        }
        char v = (c & 0xF) + (c >> 6) | ((c >> 3) & 0x8);
        res = (res << 4) | (uint)v;
        i++;
    }

    return res;
}

bool char_test(char expr, Test_Type test)
{
    switch (test)
    {
    case IS_BOOL:
    {
        if (expr != 0)
        {
            return true;
        }
        else
        {
            return false;
        }
        break;
    }
    case IS_CHARS:
    {
        iocharmap(IOCHM_PETSCII_2);
        bool retVal = false;
        if (expr >= 'a' && expr <= 'z')
        {
            retVal = true;
        }
        else
        {
            retVal = false;
        }

        iocharmap(IOCHM_PETSCII_1);
        return retVal;
        break;
    }
    case IS_DIGIT:
    {
        if (expr >= '0' && expr <= '9')
        {
            return true;
        }
        else
        {
            return false;
        }
        break;
    }
    case IS_PRINTABLE:
    {
        char chr = expr;
        bool test1 = ((chr >= 0x20) && (chr <= 0x7f));
        bool test2 = ((chr >= 0xa0) && (chr <= 0xff));
        if (test1 || test2)
        {
            return true;
        }
        else
        {
            return false;
        }
        break;
    }
    case IS_HEX:
    {
        iocharmap(IOCHM_PETSCII_2);
        bool retVal = false;
        if (char_test(expr, IS_DIGIT) || (expr >= 'a' && expr <= 'f'))
        {
            retVal = true;
        }
        else
        {
            retVal = false;
        }
        iocharmap(IOCHM_PETSCII_1);
        return retVal;
        break;
    }
    }
}

bool string_test(char *expr, Test_Type test)
{
    switch (test)
    {
    case IS_BOOL:
    {
        if (strcmp(expr, "false") || strcmp(expr, "true"))
        {
            return true;
        }
        else
        {
            return false;
        }
        break;
    }
    case IS_CHARS:
    {
        iocharmap(IOCHM_PETSCII_2);
        bool retVal = false;
        for (byte i = 0; expr[i] != '\0'; i++)
        {
            if (expr[i] >= 'a' && expr[i] <= 'z')
            {
                retVal = true;
            }
            else
            {
                retVal = false;
            }
        }
        iocharmap(IOCHM_PETSCII_1);
        return retVal;
        break;
    }
    case IS_DIGIT:
    {
        for (byte i = 0; expr[i] != '\0'; i++)
        {
            if (expr[i] >= '0' && expr[i] <= '9')
            {
                return true;
            }
            else
            {
                return false;
            }
        }
        break;
    }
    case IS_PRINTABLE:
    {
        for (byte i = 0; expr[i] != '0'; i++)
        {
            char chr = expr[i];
            bool test1 = ((chr >= 0x20) && (chr <= 0x7f));
            bool test2 = ((chr >= 0xa0) && (chr <= 0xff));
            if (test1 || test2)
            {
                return true;
            }
            else
            {
                return false;
            }
        }
        break;
    }
    case IS_HEX:
    {
        iocharmap(IOCHM_PETSCII_2);
        bool retVal = false;
        for (byte i = 0; expr[i] != '\0'; i++)
        {
            if (string_test((char *)expr[i], IS_DIGIT) ||
                (expr[i] >= 'a' || expr[i] <= 'f'))
            {
                retVal = true;
            }
            else
            {
                retVal = false;
            }
        }
        iocharmap(IOCHM_PETSCII_1);
        return retVal;
        break;
    }
    }
}

inline char peek(word address) { return *(volatile char *)address; }

inline void poke(word address, char value)
{
    *(volatile char *)address = value;
}
