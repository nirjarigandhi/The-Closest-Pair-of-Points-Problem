#include "closest_brute.h"

double brute_force(struct Point P[], size_t n)
{
    //int num_elems = n/sizeof(struct Point);
    double min_dist = 0.0; //keeps track of mininimum distance
    int count = 0; //check if minimum distance has been updates from initial value
    for (int i = 0; i < n; i++)
    {
        for (int j = i + 1; j < n; j++)
        {

            double distance = dist(P[i], P[j]); //calculates distance between 2 points
            if (count == 0)
            {
                min_dist = distance;
                count++;
            }
            if (distance < min_dist)
            {
                min_dist = distance; //updates minimum distance is smaller one is found
            }
        }
    }
    return min_dist;
}
