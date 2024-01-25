/*
Name: Zoe Debyl
Date: 3/27/2023
Assignment: Assignment 4
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//performs the Gale-Shapley algorithm on the given nxn preference matrices and displays a matrix to show the matches
void stablemarriage(int mensPrefer[5][5], int womensPrefer[5][5], int num) {
    int matches[5][5];
    int full=0;
    int freeMan=0;
    int freeWoman=0;
    int womenPropose;
    int replace=0;
    int womenCurrentMatch;

    //initialize matches
    for (int i=0; i<num; i++) {
        for (int j=0; j<num; j++) {
            matches[i][j] = 0;
        }
    }

    //keep iterating until all men are matched
    while (full<num) {
        //go through all men
        for (int i=0; i<num; i++) {
            freeMan=0;

            //check if man is free
            for (int j=0; j<num; j++) {
                if (matches[i][j]==1) {
                    freeMan=1;
                }
            }

            //if man is not free, match him
            if (freeMan==0) {
                //go through women, if preferred are taken
                for (int j=0; j<num; j++) {
                    freeWoman = 0;

                    womenPropose = mensPrefer[i][j];

                    //check if women is free
                    for (int k=0; k<num; k++) {
                        if (matches[k][womenPropose-1]==1) {
                            freeWoman = 1;
                            womenCurrentMatch = k+1;
                        }
                    }

                    //women is free, match with man and exit loop
                    if (freeWoman==0) {
                        matches[i][womenPropose-1] = 1;

                        break;
                    }
                    //women is not free, check if she prefers this man over her current match
                    else {
                        replace = 0;

                        for (int k=0; k<num; k++) {
                            if (womensPrefer[womenPropose-1][k]==i+1) {
                                replace=1;
                                break;
                            }

                            if (womensPrefer[womenPropose-1][k]==womenCurrentMatch) {
                                replace=0;
                                break;
                            }
                        }

                        //women prefers new man, get rid of old match, make new match and exit loop
                        if (replace==1) {
                            matches[womenCurrentMatch-1][womenPropose-1]=0;
                            matches[i][womenPropose-1]=1;

                            full--;

                            break;
                        }
                    }
                }

                full++;
            }
        }        
    }

    //display results
    for (int i=0; i<num; i++) {
        for (int j=0; j<num; j++) {
            printf("%d ", matches[i][j]);
        }
        printf("\n");
    }
}

//reads file and calls algorithm
int main(void) {
    FILE* file;
    char filename[1000];
    int numPeople;
    int mensPrefer[5][5];
    int womensPrefer[5][5];

    //get filename
    printf("Enter a filename: ");
    scanf("%s", filename);

    //open and read file
    file = fopen(filename, "r");

    if (file==NULL) {
        printf("Error reading file.");
    } else {
        //get number of people
        fscanf(file, "%d", &numPeople);

        //get mens preferences
        for (int i=0; i<numPeople; i++) {
            for (int j=0; j<numPeople; j++) {
                fscanf(file, "%d", &mensPrefer[i][j]);
            }
        }

        //get womens preferences
        for (int i=0; i<numPeople; i++) {
            for (int j=0; j<numPeople; j++) {
                fscanf(file, "%d", &womensPrefer[i][j]);
            }
        }

        //call stable marriage algorithm
        stablemarriage(mensPrefer, womensPrefer, numPeople);
    }

    return 0;
}
