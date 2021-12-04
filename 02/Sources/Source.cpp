#include <iostream>
#include "Source.h"

void RemoveDups(char* str)
{
    if (!str)
        return;

    char* last_unique_letter_ptr = str;

    for (int i = 1; str[i] != '\0'; i++)
    {
        if (str[i] == *last_unique_letter_ptr)
            continue;

        *(++last_unique_letter_ptr) = str[i];
    }

    if (*(last_unique_letter_ptr++) != '\0')
    {
        *(last_unique_letter_ptr++) = '\0';
    }
}
