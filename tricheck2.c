#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAX_ARGS 2
#define ERROR_MARGIN 0.0000001

void printHelp()
{
    printf("Usage: ./tricheck2 [ARG(S)]\n\n");
    printf("Without arguments, reads 6 integers between [0,1000000]\n");
    printf("from stdin, and interprets them into a triangle with vertices\n");
    printf("(x1,y1), (x2,y2), (x3,y3) where the order of the input integers\n");
    printf("fill in these coordinates sequentially.\n\n");
    printf("Arguments:\n");
    printf("--help\t prints this help page\n\n");
}

int main(int argc, char *argv[])
{
    if (argc > MAX_ARGS)
    {
        printf("ERROR: Please input fewer arguments.\n");
        printf("See ./tricheck2 --help for more help.\n");
        return -1;
    }

    if (argc > 1)
    {
        if (strcmp(argv[1], "--help\n"))
        {
            printHelp();
            return -1;
        }
        else
        {
            printf("ERROR: Unrecognized argument.\n");
            printf("See ./tricheck2 --help for more help.\n");
            return -1;
        }
    }

    long coords[6];

    printf("Which triangle would you like indentified?\n");
    printf("Please input 6 integers seperated by spaces:\n");
    if (scanf("%li %li %li %li %li %li", &coords[0], &coords[1], &coords[2], &coords[3], &coords[4], &coords[5]) != 6)
    {
        printf("ERROR: Please input six valid integers.\n");
        printf("See ./tricheck2 --help for more help.\n");
        return -1;
    }

    double sideLengths[3];

    sideLengths[0] = sqrt(pow((double)(coords[0] - coords[2]), 2.0) + pow((double)(coords[1] - coords[3]), 2.0));
    sideLengths[1] = sqrt(pow((double)(coords[0] - coords[4]), 2.0) + pow((double)(coords[1] - coords[5]), 2.0));
    sideLengths[2] = sqrt(pow((double)(coords[2] - coords[4]), 2.0) + pow((double)(coords[3] - coords[5]), 2.0));

    double semiPerim = 0;

    for (int i = 0; i < 3; i++)
    {
        if (fabs(sideLengths[i]) <= ERROR_MARGIN)
        {
            printf("ERROR: Not a triangle.\n");
            printf("Please see ./tricheck2 --help for more help.\n");
            return -1;
        }
        semiPerim += sideLengths[i];
    }

    semiPerim = semiPerim / 2.0;

    double area = sqrtf(semiPerim * (semiPerim - sideLengths[0]) * (semiPerim - sideLengths[1]) * (semiPerim - sideLengths[2]));

    if (fabs(area) <= ERROR_MARGIN)
    {
        printf("ERROR: Not a triangle.\n");
        printf("Please see ./tricheck2 --help for more help.\n");
        return -1;
    }

    if (fabs(sideLengths[0] - sideLengths[1]) <= ERROR_MARGIN && fabs(sideLengths[1] - sideLengths[2]) <= ERROR_MARGIN)
    {
        printf("Your triangle is Equilateral.\n");
    }
    else if (fabs(sideLengths[0] - sideLengths[1]) > ERROR_MARGIN && fabs(sideLengths[1] - sideLengths[2]) > ERROR_MARGIN && fabs(sideLengths[0] - sideLengths[2]) > ERROR_MARGIN)
    {
        printf("Your traingle is Scalene.\n");
    }
    else
    {
        printf("Your triangle is Isosceles.\n");
    }

    int longSideIndex = 0;
    int shortSides[2];
    shortSides[0] = 1;
    shortSides[1] = 2;

    for (int i = 1; i < 3; i++)
    {
        if (sideLengths[i] > sideLengths[longSideIndex])
        {
            for (int j = 0; j < 2; j++)
            {
                if (shortSides[j] == i)
                {
                    shortSides[j] = longSideIndex;
                    break;
                }
            }
            longSideIndex = i;
        }
    }

    if (fabs(powf(sideLengths[longSideIndex], 2.0) - (powf(sideLengths[shortSides[0]], 2.0) + powf(sideLengths[shortSides[1]], 2.0))) <= ERROR_MARGIN)
    {
        printf("Your triangle is Right.\n");
    }
    else if (powf(sideLengths[longSideIndex], 2.0) - (powf(sideLengths[shortSides[0]], 2.0) + powf(sideLengths[shortSides[1]], 2.0)) >= ERROR_MARGIN)
    {
        printf("Your traingle is Obtuse.\n");
    }
    else
    {
        printf("Your triangle is Acute.\n");
    }

    return 0;
}
