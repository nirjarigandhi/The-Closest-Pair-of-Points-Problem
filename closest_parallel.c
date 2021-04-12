#include "closest_parallel.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

int curr_depth = 0;

double _closest_parallel(struct Point P[], size_t n, int pdmax, int *pcount)
{
    if (n <= 3 || pdmax == 0)
    {
        return _closest_serial(P, n);
    }
    else
    {
        static int num_forks = 0;

        int fd_l[2]; //create pipe for left child
        int fd_r[2];

        double left_min_dist = 0;
        double right_min_dist = 0;

        if (pipe(fd_l) == -1)
        {
            perror("pipe");
        }

        int result_left = fork(); //fork will return child's pid or -1 if the process wasn't able to create child
        int result_right = 0;

        //for the child process fork will return 0
        //child process is writing to the pipe so we need to close the read fd for child

        if (result_left == -1)
        {
            perror("fork");
            exit(1);
        }
        if (result_left > 0)
        {
            close(fd_l[1]); //close writing for parent
            int exit_status;

            int fd_r[2]; //create pipe for right child

            if (pipe(fd_r) == -1)
            {
                perror("pipe");
            }

            result_right = fork(); //fork will return child's pid or -1 if the process wasn't able to create child

            if (result_right == 0){
                goto jump;
            }

            while (waitpid(result_left, &exit_status, 0) < 0) //waits until child process is completed to read
            {
                perror("error with waitpid");
            }
            read(fd_l[0], &left_min_dist, sizeof(double)); //read the minimum distance from pipe connecting to child
            num_forks += WEXITSTATUS(exit_status) + 1;     //exit status represents number of descendents of children of so add it to total number of child processes
            close(fd_l[0]);                                //close reading for parent
        }
        else if (result_left == 0)
        {
            curr_depth++;
            close(fd_l[0]); //close reading for child process
            num_forks = 0;  //make num_forks equalt o 0 to tell child that they start off with 0 children

            left_min_dist = _closest_parallel(P, n / 2, pdmax - 1, pcount); //recurse through left half array to find min dist

            if (write(fd_l[1], &left_min_dist, sizeof(double)) == -1) //write to parent
            {
                perror("write to pipe");
                exit(1);
            }
            close(fd_l[1]);  //close writing for child process
            exit(num_forks); //exit with number status representing number of forks created within this child process
        }

        jump:
        //for the child process fork will return 0
        //child process is writing to the pipe so we need to close the read fd for child

        if (result_right == -1)
        {
            perror("fork");
            exit(1);
        }
        if (result_right > 0)
        {
            close(fd_r[1]); //closes writing for parent
            int exit_status;
            while (waitpid(result_right, &exit_status, 0) < 0) //waits until child process is terminated
            {
                perror("error with waitpid");
            }
            read(fd_r[0], &right_min_dist, sizeof(double)); //read min distance from pipe connecting to child
            num_forks += WEXITSTATUS(exit_status) + 1;      //exit status represents number of descendents of children of so add it to total number of child processes
            close(fd_r[0]);                                 //close reading for parent
        }
        else if (result_right == 0)
        {
            curr_depth++;
            close(fd_r[0]); //close reading for child
            num_forks = 0;  //make num_forks equalt o 0 to tell child that they start off with 0 children

            right_min_dist = _closest_parallel(&P[n / 2], n - (n / 2), pdmax - 1, pcount); //recurse through right half of array to find min dist
            //send return value back to parent using write function

            if (write(fd_r[1], &right_min_dist, sizeof(double)) == -1) //write to parent
            {
                perror("write to pipe");
                exit(1);
            }
            close(fd_r[1]);
            exit(num_forks); //exit with number status representing number of forks created within this child process
        }
        double min_l_r = fmin(right_min_dist, left_min_dist);

        *pcount = num_forks;
        return combine_lr(P, n, P[n / 2], min_l_r);
    }
}

double closest_parallel(struct Point P[], size_t n, int pdmax, int *pcount)
{
    //The closest_parallel() function should first sort the points, using qsort(), in ascending order by their x-coordinates. It should then call _closest_parallel().
    qsort(P, n, sizeof(struct Point), compare_x);
    return _closest_parallel(P, n, pdmax, pcount);
}
