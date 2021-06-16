#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#include "trilib.h"

int diffTest(int coords[])
{
    int tri_1 = tricheck1(coords);
    int tri_2 = tricheck2(coords);
    if (tri_1 != tri_2)
    {
        printf("tricheck1: %d, tricheck2: %d\n", tri_1, tri_2);
        return 1;
    }
    return 0;
}

int main()
{
    int sumErrors = 0;
    int currError = 0;
    int coords[6];

    srand(time(NULL));

    for (int i = 0; i < 1000000; i++)
    {
        coords[0] = rand() % 1000000 + 1;
        coords[1] = rand() % 1000000 + 1;
        coords[2] = rand() % 1000000 + 1;
        coords[3] = rand() % 1000000 + 1;
        coords[4] = rand() % 1000000 + 1;
        coords[5] = rand() % 1000000 + 1;
        currError = diffTest(coords);
        if (currError)
        {
            for (int j = 0; j < 6; j++)
            {
                printf("Coord %d: %d ", j, coords[j]);
            }
            printf("\n");
        }
        sumErrors += currError;
        currError = 0;
    }

    printf("Number of differences: %d\n", sumErrors);
    return 0;
}
