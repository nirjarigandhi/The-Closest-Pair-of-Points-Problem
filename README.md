# The-Closest-Pair-of-Points-Problem
Given n points on a 2D plane, find the distance between the closest pair of points.

**The Closest Pair of Points Problem**

Given n points on a 2D plane, find the distance between the closest pair of points.

**Naive (Brute-Force) Approach:**

The naive solution can be implemented in just a few lines, by finding the distance between all pairs of points and returning the distance between the closest pair. This approach requires O(n^2) time.

Recursive Divide-and-Conquer Approach
The problem can be solved in O(nlogn) time using the following recursive divide and conquer approach:

  1. Sort the points in ascending order by their x-coordinates.
  2. Split the list of points into two equal-sized halves. This is like drawing a vertical line through the plane to divide the points into a left-hand-side and right-hand-side, each containing an equal number of points.
  3. Solve the problem recursively on the left and right halves.
  4. Find the distance between the closest pair of points where one point lies on the left-hand-side, and the other point lies on the right-hand-side. This can be done in linear time.
  5. The final answer is the minimum among the:
     1. Distance between the closest pair of points on the left-hand side.
     2. Distance between the closest pair of points on the right-hand side.
     3. Distance between the closest pair of points where one point is on the left-hand-side and the other point is on the right-hand side.
  
**Assignment Structure:**

First, let us go over the files provided in the starter code:

-```Makefile```, which you will notice contains a new flag, -fsanitize=signed-integer-overflow, as well as the -lm flag required for the math library.

-```main.c``` contains the logic to:

    1. Parse command-line arguments
    
    2. Either generate points or read them from a file
    
    3. Optionally save generated points to a file
    
    4. Sort the points with qsort()
    
    5. Call both the single-process and multi-process implementations to find the distance between the closest pair of points
    
    6. Measure the time taken by both the single-process and multi-process implementations
    
-```closest_tests.c``` contains a test case to test the correctness of your implementation. You may use this as a skeleton to add additional test cases.

-```closest_helpers.h```, ```closest_brute.h```, ```closest_serial.h```, and ```closest_parallel.h``` declare all the functions that you will implement.

-```closest_helpers.c```, ```closest_brute.c```, ```closest_serial.c```, and ```closest_parallel.c``` are where your implementations will go.
