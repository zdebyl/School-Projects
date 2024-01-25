/*
Name: Zoe Debyl
ID: 1186610
Date: 4/10/2023
Assignment: Assignment 5
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int num = 12;
int bestassignment[12];
int max = 0;

//find all possibilities for ordering an array
void possibilities(int values[num][num], int assignment[num], int startindex, int numelements) {
    int temp;

    //got a possibility
    if (startindex==numelements) {
        int sum=0;

        //calculate sum
        for (int i=0; i<numelements; i++) {
            sum = sum + values[assignment[i]][i];
        }
        
        //check if its the maximum sum so far
        if (sum>max) {
            max = sum;

            for (int i=0; i<numelements; i++) {
                bestassignment[i] = assignment[i];
            }
        }

        return;
    }

    //generate possibilities
    for (int i=startindex; i<numelements; i++) {
        temp = assignment[startindex];
        assignment[startindex] = assignment[i];
        assignment[i] = temp;

        possibilities(values, assignment, startindex+1, numelements);

        temp = assignment[i];
        assignment[i] = assignment[startindex];
        assignment[startindex] = temp;
    }
}

//computes assignment problem using brute force algorithm
void assignmentbrute(int values[num][num]) {
    int assignment[num];
    int sum=0;
    int totalpossibilities=1;

    //initialize array to track assignment order
    for (int i=0; i<num; i++) {
        assignment[i] = i;
        bestassignment[i] = 0;
    }

    //call function to generate all possibilities for assignment
    possibilities(values, assignment, 0, num);

    //calculate and display results
    for (int i=1; i<=num; i++) {
        totalpossibilities = totalpossibilities * i;
    }

    printf("The number of all the possible assignments: %d\n", totalpossibilities); 

    printf("The person-job assignment selected:\n");
    for (int i=0; i<num; i++) {
        printf("%d ", bestassignment[i]+1);
        sum = sum + values[bestassignment[i]][i];
    }
    printf("\n");

    printf("The total value: %d\n", sum);
}

//recursively assigns each person a job
void assign(int values[num][num], int person, int jobsavailable[num], int numjobsavailable, int total) {
    if (numjobsavailable==0) {
        return;
    } else {
        int currsum=0;
        int maxsum=0;
        int personsvalue;
        int jobvalue;
        int currhigh;

        //calculate all upper bounds
        for (int i=0; i<numjobsavailable; i++) {
            //assign current person to each available job
            currsum = values[person][jobsavailable[i]] + total;

            //add all other peoples values
            for (int j=person+1; j<num; j++) {
                currhigh = 0;

                //get other peoples highest value
                for (int k=0; k<numjobsavailable; k++) {
                    if (values[j][jobsavailable[k]]>=currhigh && jobsavailable[k]!=jobsavailable[i]) {
                        currhigh = values[j][jobsavailable[k]];
                    }
                }

                currsum = currsum + currhigh;
            }

            //find highest upper bound
            if (i==0) {
                maxsum = currsum;
                personsvalue = values[person][jobsavailable[i]];
                jobvalue = jobsavailable[i];
            } else {
                if (currsum>maxsum) {
                    personsvalue = values[person][jobsavailable[i]];
                    maxsum = currsum;
                    jobvalue = jobsavailable[i];
                }
            }
        }

        printf("Maximum upper bound: %d\n", maxsum);

        //update variables
        bestassignment[jobvalue] = person;

        //add to people already assigned
        total = total + personsvalue;

        //update jobs available
        numjobsavailable = numjobsavailable - 1;

        int jobindex=0;

        for (int i=0; i<numjobsavailable; i++) {
            if (jobsavailable[i]!=jobvalue) {
                jobsavailable[jobindex] = jobsavailable[i];
                jobindex++;
            }
        }

        if (jobindex<numjobsavailable) {
            jobsavailable[jobindex] = jobsavailable[numjobsavailable];
        }

        //call program recursively
        assign(values, person+1, jobsavailable, numjobsavailable, total);
    }
}

//computes assignment problem using branch and bound algorithm
void assignmentbranch(int values[num][num]) {
    int jobsavailable[num];
    int sum=0;

    //initialize all jobs available
    for (int i=0; i<num; i++) {
        jobsavailable[i] = i;
    }

    assign(values, 0, jobsavailable, num, 0);

    //display results
    printf("The person-job assignment selected:\n");
    for (int i=0; i<num; i++) {
        printf("%d ", bestassignment[i]+1);
        sum = sum + values[bestassignment[i]][i];
    }
    printf("\n");

    printf("The total value: %d\n", sum);
}

//opens file, calls both algorithms to solve assignment problem
int main(void) {
    FILE* file;
    char filename[200];
    int jobs[num][num];
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
        for (int i=0; i<num; i++) {
            for (int j=0; j<num; j++) {
                fscanf(file, "%d", &jobs[i][j]);
            }
        }
    }

    //brute force algorithm
    printf("\nBrute force program for assignment problem\n");
    start = clock();
    assignmentbrute(jobs);
    finish = clock();

    executionTime = ((double)(finish - start))/CLOCKS_PER_SEC;
    printf("Execution time = %lf seconds\n", executionTime);

    //branch and bound program
    printf("\nBranch and bound program for assignment problem\n");

    start = clock();
    assignmentbranch(jobs);
    finish = clock();

    executionTime = ((double)(finish - start))/CLOCKS_PER_SEC;
    printf("Execution time = %lf seconds\n", executionTime);

    return 0;
}