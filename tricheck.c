#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ARGS 2
#define M_PI 3.14159265358979323846
#define ERROR_MARGIN 0.0000001

void printHelp()
{
    printf("Usage: ./tricheck [ARG(S)]\n\n");
    printf("Without arguments, reads 6 integers between [0,1000000]\n");
    printf("from stdin, and interprets them into a triangle with vertices\n");
    printf("(x1,y1), (x2,y2), (x3,y3) where the order of the input integers\n");
    printf("fill in these coordinates sequentially.\n\n");
    printf("Arguments:\n");
    printf("--help\t prints this help page\n\n");
}

//Returns an array with the distance between the two points as the first value
//and returns the slope between the two points as the second value
double *distanceSlope(long x1, long y1, long x2, long y2)
{
    double *ret = malloc(2 * sizeof(double));
    double dist = sqrt(pow((double)(x1 - x2), 2.0) + pow((double)(y1 - y2), 2.0));
    double slope = -1;
    if (x1 != x2)
    {
        slope = (double)(y1 - y2) / (double)(x1 - x2);
    }
    ret[0] = dist;
    ret[1] = slope;
    return ret;
}

int main(int argc, char *argv[])
{
    if (argc > MAX_ARGS)
    {
        printf("ERROR: Please input fewer arguments.\n");
        printf("See ./tricheck --help for more help.\n");
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
            printf("See ./tricheck --help for more help.\n");
            return -1;
        }
    }

    long coords[6];

    printf("Which triangle would you like indentified?\n");
    printf("Please input 6 integers seperated by spaces:\n");
    if (scanf("%li %li %li %li %li %li", &coords[0], &coords[1], &coords[2], &coords[3], &coords[4], &coords[5]) != 6)
    {
        printf("ERROR: Please input six valid integers.\n");
        printf("See ./tricheck --help for more help.\n");
        return -1;
    }

    double *onetwoDistSlop = distanceSlope(coords[0], coords[1], coords[2], coords[3]);
    double *onethreeDistSlop = distanceSlope(coords[0], coords[1], coords[4], coords[5]);
    double *twothreeDistSlop = distanceSlope(coords[2], coords[3], coords[4], coords[5]);

    //If the first two coordinates are the same
    if (fabs(onetwoDistSlop[0]) <= ERROR_MARGIN)
    {
        printf("ERROR: Specified coordinates 1 and 2 are the same. Not a triangle.\n");
        printf("See ./tricheck --help for more help.\n");
        free(onetwoDistSlop);
        free(onethreeDistSlop);
        free(twothreeDistSlop);
        return -1;
    }
    //If the first and last coordinates are the same
    if (fabs(onethreeDistSlop[0]) <= ERROR_MARGIN)
    {
        printf("ERROR: Specified coordinates 1 and 3 are the same. Not a triangle.\n");
        printf("See ./tricheck --help for more help.\n");
        free(onetwoDistSlop);
        free(onethreeDistSlop);
        free(twothreeDistSlop);
        return -1;
    }
    //If the second and last coordinates are the same
    if (fabs(twothreeDistSlop[0]) <= ERROR_MARGIN)
    {
        printf("ERROR: Specified coordinates 2 and 3 are the same. Not a triangle.\n");
        printf("See ./tricheck --help for more help.\n");
        free(onetwoDistSlop);
        free(onethreeDistSlop);
        free(twothreeDistSlop);
        return -1;
    }

    //If the slope between the first coordinate and the second is the same as the slope
    // between the second and third coordinate, then the points are all on the same line
    if (fabs(onetwoDistSlop[1] - twothreeDistSlop[1]) <= ERROR_MARGIN)
    {
        printf("ERROR: Specified coordinates all lie on the same line. Not a triangle.\n");
        printf("See ./tricheck --help for more help.\n");
        free(onetwoDistSlop);
        free(onethreeDistSlop);
        free(twothreeDistSlop);
        return -1;
    }

    if (fabs(onetwoDistSlop[0] - onethreeDistSlop[0]) <= ERROR_MARGIN && fabs(onethreeDistSlop[0] - twothreeDistSlop[0]) <= ERROR_MARGIN)
    {
        printf("Your triangle is Equilateral.\n");
    }
    else if (fabs(onetwoDistSlop[0] - onethreeDistSlop[0]) > ERROR_MARGIN && fabs(onethreeDistSlop[0] - twothreeDistSlop[0]) > ERROR_MARGIN && fabs(onetwoDistSlop[0] - twothreeDistSlop[0]) > ERROR_MARGIN)
    {
        printf("Your triangle is Scalene.\n");
    }
    else
    {
        printf("Your traingle is Isosceles.\n");
    }

    double angles[3];

    //Uses the law of cosines. For side lengths a, b, and c: arccos(a^2 - b^2 - c^2 / -2bc) = angle between b and c
    angles[0] = acos((pow(twothreeDistSlop[0], 2.0) - pow(onethreeDistSlop[0], 2.0) - pow(onetwoDistSlop[0], 2.0)) / (-2 * onethreeDistSlop[0] * onetwoDistSlop[0]));
    angles[1] = acos((pow(onethreeDistSlop[0], 2.0) - pow(twothreeDistSlop[0], 2.0) - pow(onetwoDistSlop[0], 2.0)) / (-2 * twothreeDistSlop[0] * onetwoDistSlop[0]));
    angles[2] = acos((pow(onetwoDistSlop[0], 2.0) - pow(twothreeDistSlop[0], 2.0) - pow(onethreeDistSlop[0], 2.0)) / (-2 * twothreeDistSlop[0] * onethreeDistSlop[0]));

    double maxAng = -1;
    for (int i = 0; i < 3; i++)
    {
        if (angles[i] > maxAng)
        {
            maxAng = angles[i];
        }
    }

    if (fabs(maxAng - (M_PI / 2.0)) <= ERROR_MARGIN)
    {
        printf("Your triangle is Right.\n");
    }
    else if (maxAng - (M_PI / 2.0) > ERROR_MARGIN)
    {
        printf("Your triangle is Obtuse.\n");
    }
    else
    {
        printf("Your triangle is Acute.\n");
    }

    free(onetwoDistSlop);
    free(onethreeDistSlop);
    free(twothreeDistSlop);
    return 0;
}