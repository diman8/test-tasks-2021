#include <iostream>
#include "Source.h"

void print_as_binary(int input)
{
    const int bit_size = sizeof(int) * 8;
    for (int i = bit_size - 1; i >= 0; i--)
    {
        const bool bit_value = (input >> i) & 1u;
        std::cout << (bit_value ? "1" : "0");
    }
    std::cout << "\n";
}

void print_as_binary_2(int input)
{
    puts(int_to_string_binary(input));
}

const char* int_to_string_binary(int input)
{
    const int bit_size = sizeof(int) * 8;
    static char temp_str[bit_size];
    for (int i = 0; i < bit_size; i++)
    {
        const bool bit_value = (input >> i) & 1u;
        temp_str[bit_size - i - 1] = bit_value ? *"1" : *"0";
    }
    return temp_str;
}
