#include <stdio.h>

/**
 * The bug is that the program is trying to add character it has seen to
 * a bitset and output them to the terminal once the user hits EOF.
 * Unfortunearely for us, this implementation is not correct and will print
 * dubious looking characters to the terminal when it's supposed to print
 * exactly what the user types in, in set form.
 * */

int main()
{
    unsigned long bitset = 0;
    char currchar;
    int ascii = 255;
    while ((currchar = getc(stdin)) != EOF)
    {
        //Adds that char to the bitset
        bitset = bitset | currchar;
    }
    //Prints out all the chars from ascii seen
    printf("Chars Seen: [");
    for (int i = 0; i < ascii; i++)
    {
        if (bitset & 1)
        {
            if (i != ascii - 1)
            {
                printf("%c,", i);
            }
            else
            {
                printf("%c]\n", i);
            }
        }
        bitset >>= 1;
    }
    return 0;
}

/**
 * (1) peel through the code to see whether the bitset was implemented
 * correctly. Is there anything weird about the bit operators? what about
 * the method of addition?
 * 
 * (2) the issue is that we are directly "anding" the character onto the
 * bitset when we find it. NOT the number with a one at that index in the
 * bitset.
 * 
 * (3) to fix, modify the bitset = bitset | currchar to instead find the
 * number in binary which is associated with having a 1 in the character
 * ascii value place. This could be done with a for loop and iterating
 * over the int 1 with moving points the character value amount of times.
 * */