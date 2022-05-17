#include <stdbool.h>
#include <c64/types.h>
#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <petscii.h>
#include <string.h>
#include <math.h>

int main()
{
    iocharmap(IOCHM_PETSCII_1);
    char hex[17];
    unsigned int decimal = 0, base = 1;
    int i = 0, value, length;
    /* Get hexadecimal value from user */
    printf("enter hexadecimal number: ");
    scanf("%17S",hex);

    //fgets(hex,ARRAY_SIZE,stdin);

    length = strlen(hex);
    sscanf(hex, "%X", &decimal);
    printf("\nHexadecimal number = %S\n", hex);
    printf("Decimal number = %U\n", decimal);
    getch();
    return 0;
}
