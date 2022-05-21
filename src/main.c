/* vi: set shiftwidth=4 tabstop=4 expandtab:
 * :indentSize=4:tabSize=4:noTabs=true:
 */
#include <c64/types.h>
#include <conio.h>
#include <petscii.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "utilities.h"

unsigned int maybe_jump_to(const char *param,
                           unsigned int current_mem_position);

unsigned int display_memory(unsigned int current_mem_position);

void print_instructions(void);

int main(void)
{
    // char instructions[330] = ". will move you to the next byte in\n"
    //                          "memory.\n\n, will move you to the\n"
    //                          "previous byte.\n\n"
    //                          "To jump to a specific byte,\ntype J\n"
    //                          "and type the byte number in hex or\n"
    //                          "decimal. If in hex, include a $.\n"
    //                          "Example:\n"
    //                          "    $0400  $20     ? J1056\n"
    //                          "    $0420  $20     ? J$0440\n"
    //                          "    $0440  $20     ?";

    // TODO: IMPLEMENT DISPLAY OF MEMORY
    iocharmap(IOCHM_PETSCII_1);
    unsigned int current_mem_position = 4096;
    print_instructions();
    byte input_size = 10;
    char *input = (char *)calloc((input_size), sizeof(char));
    while (input[0] != 'Q')
    {
        char promptText[6];
        sprintf(promptText, "$%X ", current_mem_position);
        printf("%X", display_memory(current_mem_position));
        promptForInput(promptText, input, input_size);
        switch (input[0])
        {
        case '.':
        {
            char pos[6];
            sprintf(pos, "%D", current_mem_position + 1);
            current_mem_position = maybe_jump_to(pos, current_mem_position);
            break;
        }
        case 'J':
        {
            char *param = (char *)calloc((input_size), sizeof(char));
            byte input_pos = 1;
            byte param_pos = 0;
            while (input[input_pos] != '\0')
            {
                param[param_pos] = input[input_pos];
                input_pos++;
                param_pos++;
            }
            param[param_pos] = '\0';
            current_mem_position = maybe_jump_to(param, current_mem_position);
        }
        }
    }
    return 0;
}

unsigned int maybe_jump_to(const char *param, unsigned int current_mem_position)
{
    unsigned int dec_param = 0;
    byte len_param;
    /* for stripping the '$' if needed */
    char *param_stripped;
#define DEBUG 0
#if DEBUG
    printf("%S\n", param);
#endif
    switch (param[0])
    {
    case '$':
    {
        len_param = strlen(param);
        /* we gotta strip off the '$' */
        param_stripped = calloc(strlen(param) + 1, sizeof(char));
        byte idx_param = 1;
        for (byte i; i < len_param + 1 && param[idx_param] != '\0'; i++)
        {
            param_stripped[i] = param[idx_param];
            idx_param++;
        }
        /* cool, now we have hex number (probably) */
        if (string_test(param_stripped, IS_HEX))
        {
#if DEBUG
            printf("Its valid hex...\n");
            printf("%S\n", param_stripped);
#endif
            /* Its valid hex! */
            // dec_param = xtouint(param_stripped);
            sscanf(param_stripped, "%X", &dec_param);
#if DEBUG
            printf("%U\n", dec_param);
#endif
        }
        else
        {
#if DEBUG
            printf("Its invalid hex :(\n");
#endif
            return current_mem_position;
        }
        /*exit(1);*/
        break;
    }
    default:
    {
        dec_param = atoi(param);
    }
    }
    if (!(dec_param >= 0 && dec_param <= 65535))
    {
        puts("error!");
        return current_mem_position;
    }
#if DEBUG
    printf("%U\n", dec_param);
#endif
    current_mem_position = dec_param;
    return current_mem_position;
}

unsigned int display_memory(unsigned int current_mem_position)
{
    return peek(current_mem_position);
}

void print_instructions(void)
{
    // TODO: WHY DOES THIS NOT PRINT???
    char instr[10][40] = {". will move you to the next byte in\n",
                          "memory.\n\n, will move you to the\n",
                          "previous byte.\n\n",
                          "To jump to a specific byte,\ntype J\n",
                          "and type the byte number in hex or\n",
                          "decimal. If in hex, include a $.\n",
                          "Example:\n",
                          "    $0400  $20     ? J1056\n",
                          "    $0420  $20     ? J$0440\n",
                          "    $0440  $20     ?"};
    for (byte i = 0; i < 10; i++)
    {
        printf("%S", instr[i]);
    }
}