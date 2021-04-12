#include "closest_helpers.h"
#include <math.h>
#include <stdio.h>

int verbose = 0;

int compare_x(const void *a, const void *b)
{
    //checks if x value for p1 is greater than x value for p2
    //returns 1 if p1.x > p2.x and 0 otherwise
    struct Point *p1 = (struct Point *)a;
    struct Point *p2 = (struct Point *)b;
    return (p1->x) - (p2->x);
}

int compare_y(const void *a, const void *b)
{
    //check if y value for p2 is greater than y value for p2
    //returns 1 if p1.y > p2.y and 0 otherwise
    struct Point *p1 = (struct Point *)a;
    struct Point *p2 = (struct Point *)b;
    return (p1->y) - (p2->y);
}

double dist(struct Point p1, struct Point p2)
{
    //x and y values of struct are in the form of an int
    //cast them to a bouble so now overflow occurs
    double x1 = p1.x;
    double x2 = p2.x;
    double y1 = p1.y;
    double y2 = p2.y;
    double squared_distance = (x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1);
    return sqrt(squared_distance);
}
