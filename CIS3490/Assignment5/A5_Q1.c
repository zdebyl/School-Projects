/*
Name: Zoe Debyl
Date: 4/10/2023
Assignment: Assignment 5
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>

int numdeadends=0;

//get the number of subsets with wanted sum using brute force algorithm
void subsetsumbrute(int set[30], int numints, int wantedsum) {
    int numsubsets;
    int sum=0;
    int numfound=0;
    
    //calculate number of subsets
    numsubsets = pow(2, numints);
    
    //go through each subset
    for (int i=0; i<numsubsets; i++) {
        sum=0;

        for (int j=0; j<numints; j++) {
            if (i & (1<<j)) {
                //calculate sum of subset
                sum = sum + set[j];
            }
        }

        //check if sum is what we want
        if (sum==wantedsum) {
            numfound++;
        }
    }

    //print results
    printf("Number of all the subsets: %d\n", numsubsets);
    printf("Number of the subsets whose sums are %d: %d\n", wantedsum, numfound);
}

//recursive algorithm for backtracking
int backtrack(int set[30], int numinset, int indexToAdd, int wantedsum, int numfound, int sum) {

    //wanted sum found
    if (sum==wantedsum) {
        numdeadends++;
        numfound++;
    }
    //reached a dead end
    else if (sum>wantedsum || indexToAdd>=numinset) {
        numdeadends++;
    } 
    //call function recursively twice, once with next element added in the subset and once without it
    else {
        numfound = backtrack(set, numinset, indexToAdd+1, wantedsum, numfound, sum+set[indexToAdd]);
        numfound = backtrack(set, numinset, indexToAdd+1, wantedsum, numfound, sum);
    }

    return numfound;
}

//get the number of subsets with wanted sum using backtracking algorithm
void subsetsumbacktrack(int set[30], int numints, int wantedsum) {
    int numfound;

    //call recursive algorithm
    numfound = backtrack(set, numints, 0, wantedsum, 0, 0);

    //print results
    printf("Number of dead ends: %d\n", numdeadends);
    printf("Number of the subsets whose sums are %d: %d\n", wantedsum, numfound);
}

//opens file, gets wanted sum, calls both algorithms to solve subset sum problem
int main(void) {
    FILE* file;
    char filename[200];
    int set[30];
    int i=0;
    int sum;
    clock_t start, finish;
    double executionTime;

    //get filename
    printf("Enter a filename: ");
    scanf("%s", filename);

    //open and read file
    file = fopen(filename, "r");

    if (file==NULL) {
        printf("Error reading file.");
    } else {
        while (!feof(file)) {
            fscanf(file, "%d", &set[i]);
            i++;
        }
    }

    i=i-1;

    //get user input for wanted sum
    printf("Enter a subset sum: ");
    scanf("%d", &sum);

    //brute force algorithm
    printf("\nBrute force for subset sum problem\n");
    start = clock();
    subsetsumbrute(set, i, sum);
    finish = clock();

    executionTime = ((double)(finish - start))/CLOCKS_PER_SEC;
    printf("Execution time = %lf seconds\n", executionTime);

    //backtracking algorithm
    printf("\nBacktracking program for subset sum problem\n");
    start = clock();
    subsetsumbacktrack(set, i, sum);
    finish = clock();

    executionTime = ((double)(finish - start))/CLOCKS_PER_SEC;
    printf("Execution time = %lf seconds\n", executionTime);

    return 0;
}
