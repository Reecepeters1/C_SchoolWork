#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <float.h>

#define ERROR_MARGIN 0.0000001
#define M_PI 3.14159265358979323846

double *distanceSlope(long x1, long y1, long x2, long y2)
{
    double *ret = malloc(2 * sizeof(double));
    double dist = sqrt(pow((double)(x1 - x2), 2.0) + pow((double)(y1 - y2), 2.0));
    double slope = DBL_MAX;
    if (x1 != x2)
    {
        slope = (double)(y1 - y2) / (double)(x1 - x2);
    }
    ret[0] = dist;
    ret[1] = slope;
    return ret;
}

//This is the same as my app before, except it returns an int to represent the triangle using a bitset.
//int = 00...00_ _ _ _ _ _ where each underscore is indication of one of the properties of the triangle
//Equilateral: 6th slot, 1 or 0, x _ _ _ _ _
//Isosceles: 5th slot, 1 or 0,   _ x _ _ _ _
//Scalene: 4th slot, 1 or 0,     _ _ x _ _ _
//Acute: 3rd slot, 1 or 0,       _ _ _ x _ _
//Right: 2nd slot, 1 or 0,       _ _ _ _ x _
//Obtuse: 1st slot, 1 or 0,      _ _ _ _ _ x
int tricheck1(int coords[])
{

    int ret = 0;
    double *onetwoDistSlop = distanceSlope(coords[0], coords[1], coords[2], coords[3]);
    double *onethreeDistSlop = distanceSlope(coords[0], coords[1], coords[4], coords[5]);
    double *twothreeDistSlop = distanceSlope(coords[2], coords[3], coords[4], coords[5]);

    //If the first two coordinates are the same
    if (fabs(onetwoDistSlop[0]) <= ERROR_MARGIN)
    {
        free(onetwoDistSlop);
        free(onethreeDistSlop);
        free(twothreeDistSlop);
        return -1;
    }
    //If the first and last coordinates are the same
    if (fabs(onethreeDistSlop[0]) <= ERROR_MARGIN)
    {
        free(onetwoDistSlop);
        free(onethreeDistSlop);
        free(twothreeDistSlop);
        return -1;
    }
    //If the second and last coordinates are the same
    if (fabs(twothreeDistSlop[0]) <= ERROR_MARGIN)
    {
        free(onetwoDistSlop);
        free(onethreeDistSlop);
        free(twothreeDistSlop);
        return -1;
    }

    //If the slope between the first coordinate and the second is the same as the slope
    // between the second and third coordinate, then the points are all on the same line
    if (fabs(onetwoDistSlop[1] - twothreeDistSlop[1]) <= ERROR_MARGIN)
    {
        free(onetwoDistSlop);
        free(onethreeDistSlop);
        free(twothreeDistSlop);
        return -1;
    }

    if (fabs(onetwoDistSlop[0] - onethreeDistSlop[0]) <= ERROR_MARGIN && fabs(onethreeDistSlop[0] - twothreeDistSlop[0]) <= ERROR_MARGIN)
    {
        ret += 32;
    }
    else if (fabs(onetwoDistSlop[0] - onethreeDistSlop[0]) > ERROR_MARGIN && fabs(onethreeDistSlop[0] - twothreeDistSlop[0]) > ERROR_MARGIN && fabs(onetwoDistSlop[0] - twothreeDistSlop[0]) > ERROR_MARGIN)
    {
        ret += 8;
    }
    else
    {
        ret += 16;
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
        ret += 2;
    }
    else if (maxAng - (M_PI / 2.0) > ERROR_MARGIN)
    {
        ret += 1;
    }
    else
    {
        ret += 4;
    }

    free(onetwoDistSlop);
    free(onethreeDistSlop);
    free(twothreeDistSlop);
    return ret;
}

//This is the same as my app before, except it returns an int to represent the triangle using a bitset.
//int = 00...00_ _ _ _ _ _ where each underscore is indication of one of the properties of the triangle
//Equilateral: 6th slot, 1 or 0, x _ _ _ _ _
//Isosceles: 5th slot, 1 or 0,   _ x _ _ _ _
//Scalene: 4th slot, 1 or 0,     _ _ x _ _ _
//Acute: 3rd slot, 1 or 0,       _ _ _ x _ _
//Right: 2nd slot, 1 or 0,       _ _ _ _ x _
//Obtuse: 1st slot, 1 or 0,      _ _ _ _ _ x
int tricheck2(int coords[])
{
    int ret = 0;

    double sideLengths[3];

    sideLengths[0] = sqrt(pow((double)(coords[0] - coords[2]), 2.0) + pow((double)(coords[1] - coords[3]), 2.0));
    sideLengths[1] = sqrt(pow((double)(coords[0] - coords[4]), 2.0) + pow((double)(coords[1] - coords[5]), 2.0));
    sideLengths[2] = sqrt(pow((double)(coords[2] - coords[4]), 2.0) + pow((double)(coords[3] - coords[5]), 2.0));

    double semiPerim = 0;

    for (int i = 0; i < 3; i++)
    {
        if (fabs(sideLengths[i]) <= ERROR_MARGIN)
        {
            return -1;
        }
        semiPerim += sideLengths[i];
    }

    semiPerim = semiPerim / 2.0;

    double area = sqrtf(semiPerim * (semiPerim - sideLengths[0]) * (semiPerim - sideLengths[1]) * (semiPerim - sideLengths[2]));

    if (fabs(area) <= ERROR_MARGIN)
    {
        return -1;
    }

    if (fabs(sideLengths[0] - sideLengths[1]) <= ERROR_MARGIN && fabs(sideLengths[1] - sideLengths[2]) <= ERROR_MARGIN)
    {
        ret += 32;
    }
    else if (fabs(sideLengths[0] - sideLengths[1]) > ERROR_MARGIN && fabs(sideLengths[1] - sideLengths[2]) > ERROR_MARGIN && fabs(sideLengths[0] - sideLengths[2]) > ERROR_MARGIN)
    {
        ret += 8;
    }
    else
    {
        ret += 16;
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
        ret += 2;
    }
    else if (powf(sideLengths[longSideIndex], 2.0) - (powf(sideLengths[shortSides[0]], 2.0) + powf(sideLengths[shortSides[1]], 2.0)) > ERROR_MARGIN)
    {
        ret += 1;
    }
    else
    {
        ret += 4;
    }

    return ret;
}