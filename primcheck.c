#include <stdio.h>
#include <math.h>
#include <string.h>
#include <time.h>

#define MAX_ARGS 3

void printhelp()
{
    printf("Usage: ./primcheck [ARG(S)] [FILE]\n");
    printf("Takes in a integer to check for primality.\n");
    printf("Uses a C computation by default (slow).\n\n");
    printf("ARGUMENTS:\n");
    printf("\t--help\tPrints the help page.\n");
    printf("\t--asm\tUses an x86 assembly method to compute (fast).\n");
    printf("\t--test\tAlso outputs whether the result of the C code and x86 assembly is the same.\n\n");
    printf("Takes in an optional file as input which looks for the first int in the file.\n");
}

void print_yes(long long prime)
{
    printf("\n%lli is a prime number!\n", prime);
}

void print_no(long long non_prime)
{
    printf("\n%lli is not a prime number...\n", non_prime);
}

int prime_checker_asm(long long check);

int prime_checker_c(long long check)
{
    //Two and three are both prime. If check > 1, then it must be one of them.
    if (check <= 3)
    {
        if (check > 1)
        {
            return 1;
        }
        else
        {
            return 0;
        }
    }
    //If check is neither divisible by 2 or 3 then it must either be prime or
    //Divisible by some number greater, the first of which available being 5.
    if (!(check % 2) || !(check % 3))
    {
        return 0;
    }
    //Now our iteration starts at 6*1 - 1 = 5. Read more about this at:
    //https://en.wikipedia.org/wiki/Primality_test
    long long iter = 5;
    while (pow(iter, 2) <= check)
    {
        //If the current iter, i.e. 6k - 1 or 6k + 1 divides check then it's not prime.
        if (!(check % iter) || !(check % (iter + 2)))
        {
            return 0;
        }
        //Go up by another 6
        iter = iter + 6;
    }
    return 1;
}

int main(int argc, char *argv[])
{

    if (argc > MAX_ARGS)
    {
        printf("ERROR: Please input fewer arguments.\n");
        printf("See ./primcheck --help for more information.\n");
        return -1;
    }

    //Checks the arguments
    int asem = 0;
    int test = 0;
    char *filename = NULL;
    if (argc > 1)
    {
        //We have a second argument
        if (strlen(argv[1]) > 1)
        {
            if (argv[1][0] == '-' && argv[1][1] == '-')
            {
                if (!(strcmp(argv[1], "--help")))
                {
                    printhelp();
                    return 0;
                }
                else if (!(strcmp(argv[1], "--asm")))
                {
                    asem = 1;
                }
                else if (!(strcmp(argv[1], "--test")))
                {
                    test = 1;
                }
                else
                {
                    printf("ERROR: Unrecognized argument.\n");
                    printf("See ./primcheck --help for more information.\n");
                    return -1;
                }
                if (argc > 2)
                {
                    filename = argv[2];
                }
            }
            else
            {
                filename = argv[1];
            }
        }
        else
        {
            filename = argv[1];
        }
    }

    long long cand;
    FILE *fr = stdin;
    if (filename)
    {
        fr = fopen(filename, "r");
        if (!fr)
        {
            printf("ERROR: Could not read file.\n");
            printf("See ./primcheck --help for more information.\n");
            return -1;
        }
        printf("Which integer would you like to check for primality?:  ");
        if (fscanf(fr, "%lli", &cand) != 1)
        {
            printf("ERROR: Please make sure your file contains at least one integer.\n");
            printf("See ./primcheck --help for more information.\n");
            return -1;
        }
    }
    else
    {
        printf("Which integer would you like to check for primality?:  ");
        if (scanf("%lli", &cand) != 1)
        {
            printf("ERROR: Please input an integer.\n");
            printf("See ./primcheck --help for more information.\n");
            return -1;
        }
    }
    printf("\nInteger Accepted! Computing...\n");

    if (!asem)
    {
        if (prime_checker_c(cand))
        {
            print_yes(cand);
        }
        else
        {
            print_no(cand);
        }
    }
    else
    {
        if (prime_checker_asm(cand))
        {
            print_yes(cand);
        }
        else
        {
            print_no(cand);
        }
    }
    if (test)
    {
        if (prime_checker_c(cand) != prime_checker_c(cand))
        {
            printf("ERROR: Inconsistency between C checker and ASM checker.\n");
            return -1;
        }
        else
        {
            printf("No inconsistency between C checker and ASM checker.\n");
        }
    }
    fclose(fr);
    return 0;
}