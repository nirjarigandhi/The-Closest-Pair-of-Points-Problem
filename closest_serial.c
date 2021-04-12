#include "closest_serial.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
double combine_lr(struct Point P[], size_t n, struct Point mid_point, double d)
{
    struct Point *reduced_points = malloc(sizeof(struct Point) * n);
    int count = 0;
    for (int i = 0; i < n; i++)
    {
        if (abs(P[i].x - mid_point.x) < d)
        {
            reduced_points[count] = P[i];
            count++;
        }
    }
    //sort array
    qsort(reduced_points, count, sizeof(struct Point), compare_y); //sort array in terms of y coordinate

    //For each point in the array p_i, find the distance between it and each subsequent point p_j where p_j.y - p_i.y < d.
    double min_dist = 0.0;
    int dist_check = 0; //tracks if distance has been updated
    for (int i = 0; i < count; i++)
    {
        for (int j = i + 1; j < count && j < i + 8; j++) //loop only runs for atmost 7 next points in the array
        {
            if (reduced_points[j].y - reduced_points[i].y < d)
            {
                double distance = dist(reduced_points[i], reduced_points[j]); //calculate distance between 2 points if condition hold true
                if (dist_check == 0)
                {
                    min_dist = distance;
                    dist_check++;
                }
                else if (distance < min_dist)
                {
                    min_dist = distance; //update min_dist if smaller distance is found
                }
            }
        }
    }
    free(reduced_points); //free the array form heap
    if (dist_check == 0)
    {
        return d;
    }
    return fmin(d, min_dist); //return minimum of d or min_dist found
}
double _closest_serial(struct Point P[], size_t n)
{
    //find mid point of array
    //split array in 2 halves left and right
    //check if length of each half is <=3
    //if it is then call brute_force on the array and if not then recurse on _closest_serial for each half
    //int num_elems = n/sizeof(struct Point);
    if (n <= 3)
    {
        return brute_force(P, n);
    }
    double dl = _closest_serial(P, n / 2); 
    double dr = _closest_serial(&P[n / 2], n - (n / 2));

    return combine_lr(P, n, P[n / 2], fmin(dl, dr));
}
double closest_serial(struct Point P[], size_t n)
{
    qsort(P, n, sizeof(struct Point), compare_x);
    return _closest_serial(P, n);
}
