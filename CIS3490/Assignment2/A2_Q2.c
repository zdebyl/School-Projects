/*
Name: Zoe Debyl
ID: 1186610
Date: 2/7/2023
Assignment: Assignment 2
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include <limits.h>

//gets the points in  the convex hull from a set of points using brute force
int convexHullBrute(double xPoints[], double yPoints[], double convexHullXPoints[], double convexHullYPoints[], int numPoints) {
    int hullIndex = 0;
    int pointsInHull[numPoints];

    for (int i=0; i<numPoints; i++) {
        for (int j=i+1; j<numPoints; j++) {
            if (xPoints[i]!=xPoints[j] || yPoints[i]!=yPoints[j]) {
                double a, b, c;
                int numPositive = 0;
                int numNegative = 0;

                //check each pair of points
                a = yPoints[j] - yPoints[i];
                b = xPoints[i] - xPoints[j];
                c = (xPoints[i]*yPoints[j]) - (yPoints[i]*xPoints[j]);

                //compare line between pair of points with all other points
                for (int k=0; k<numPoints; k++) {
                    double sign;

                    sign = (a*xPoints[k]) + (b*yPoints[k]) - c;

                    if (sign>0.000001) {
                        numPositive++;
                        if (numNegative>0) {
                            break;
                        }
                    } else if (sign<-0.000001) {
                        numNegative++;
                        if (numPositive>0) {
                            break;
                        }
                    }
                }

                //check if all other points are on one side of line
                if (numPositive==0 || numNegative==0) {
                    int check1=0;
                    int check2=0;

                    //check if points are already in hull
                    for (int l=0; l<hullIndex; l++) {
                        if (i==pointsInHull[l]) {
                            check1=1;
                        }
                        if (j==pointsInHull[l]) {
                            check2=1;
                        }
                    }

                    //add points to hull
                    if (check1==0) {
                        pointsInHull[hullIndex] = i;
                        convexHullXPoints[hullIndex] = xPoints[i];
                        convexHullYPoints[hullIndex] = yPoints[i];

                        printf("(%.1lf,%.1lf)\n", convexHullXPoints[hullIndex], convexHullYPoints[hullIndex]);

                        hullIndex++;
                    }
                    if (check2==0) {
                        pointsInHull[hullIndex] = j;
                        convexHullXPoints[hullIndex] = xPoints[j];
                        convexHullYPoints[hullIndex] = yPoints[j];

                        printf("(%.1lf,%.1lf)\n", convexHullXPoints[hullIndex], convexHullYPoints[hullIndex]);

                        hullIndex++;
                    }
                }
            }
        }
    }

    return hullIndex;
}

//finds the shortest path from 2 points entered from the user using points in an array (which are points in a convex hull)
void shortestPath(double xPoints[], double yPoints[], int numPoints) {
    double x1, y1, x2, y2;
    double a,b,c,sign;
    int pathOne[numPoints];
    int pathTwo[numPoints];
    int pathOneIndex=0;
    int pathTwoIndex=0;
    double totalDistanceOne = 0;
    double totalDistanceTwo = 0;
    double currentX;
    double currentY;
    double tempDistance;
    double minDistance;
    int minPoint;
    int pointsInPathOne[numPoints];
    int pointsInPathTwo[numPoints];
    int check;

    //get coordinates to find distance between
    printf("Enter the x and y coordinates of s1: ");
    scanf("%lf %lf", &x1, &y1);
    printf("Enter the x and y coordinates of s2: ");
    scanf("%lf %lf", &x2, &y2);

    //find line connecting points
    a = y2-y1;
    b = x1-x2;
    c = (x1*y2)-(y1*x2);

    //check what side of line all other points are on and separate them into paths
    for (int i=0; i<numPoints; i++) {
        sign = (a*xPoints[i]) + (b*yPoints[i]) - c;

        if (sign>0.000001) {
            pathOne[pathOneIndex] = i;
            pathOneIndex++;
        } else if (sign<-0.000001) {
            pathTwo[pathTwoIndex] = i;
            pathTwoIndex++;
        }
    }

    //calculate distance of path one
    currentX = x1;
    currentY = y1;

    for (int i=0; i<pathOneIndex; i++) {
        minDistance = INT_MAX;
        minPoint = -1;

        for (int j=0; j<pathOneIndex; j++) {
            //check if point is already counted
            check=0;
            for (int k=0; k<i; k++) {
                if (pointsInPathOne[k]==pathOne[j]) {
                    check = 1;
                }
            }

            //if point is not already counted, check its distance to the current point
            if (check==0) {
                tempDistance = sqrt((double)(((currentX-xPoints[pathOne[j]])*(currentX-xPoints[pathOne[j]])) + ((currentY-yPoints[pathOne[j]])*(currentY-yPoints[pathOne[j]]))));

                if (tempDistance < minDistance) {
                    minDistance = tempDistance;
                    minPoint = pathOne[j];
                }
            }
        }

        //update variables
        totalDistanceOne = totalDistanceOne + minDistance;
        pointsInPathOne[i] = minPoint;
        currentX = xPoints[minPoint];
        currentY = yPoints[minPoint];
    }

    minDistance = sqrt((double)(((currentX-x2)*(currentX-x2)) + ((currentY-y2)*(currentY-y2))));
    totalDistanceOne = totalDistanceOne + minDistance;

    //calculate distance of path two
    currentX = x1;
    currentY = y1;

    for (int i=0; i<pathTwoIndex; i++) {
        minDistance = INT_MAX;
        minPoint = -1;

        for (int j=0; j<pathTwoIndex; j++) {
            //check if point is already counted
            check=0;
            for (int k=0; k<i; k++) {
                if (pointsInPathTwo[k]==pathTwo[j]) {
                    check = 1;
                }
            }

            //if point is not already counted, check its distance to the current point
            if (check==0) {
                tempDistance = sqrt((double)(((currentX-xPoints[pathTwo[j]])*(currentX-xPoints[pathTwo[j]])) + ((currentY-yPoints[pathTwo[j]])*(currentY-yPoints[pathTwo[j]]))));

                if (tempDistance < minDistance) {
                    minDistance = tempDistance;
                    minPoint = pathTwo[j];
                }
            }
        }

        //update variables
        totalDistanceTwo = totalDistanceTwo + minDistance;
        pointsInPathTwo[i] = minPoint;
        currentX = xPoints[minPoint];
        currentY = yPoints[minPoint];
    }

    minDistance = sqrt((double)(((currentX-x2)*(currentX-x2)) + ((currentY-y2)*(currentY-y2))));
    totalDistanceTwo = totalDistanceTwo + minDistance;

    //print output
    if (x1==x2&&y1==y2) {
        printf("Points in shortest path:\n");
        printf("(%.1lf,%.1lf)\n", x1,y1);
        printf("Number of points: 1\n");
        printf("Distance: 0\n");
    } else {
        if (totalDistanceOne<totalDistanceTwo) {
            printf("Points in shortest path:\n");
            printf("(%.1lf,%.1lf)\n", x1,y1);
            for (int i=0; i<pathOneIndex; i++) {
                printf("(%.1lf,%.1lf)\n", xPoints[pointsInPathOne[i]], yPoints[pointsInPathOne[i]]);
            }
            printf("(%.1lf,%.1lf)\n", x2,y2);

            printf("Number of points: %d\n", pathOneIndex+2);
            printf("Distance: %.1lf\n", totalDistanceOne);
        } else if (totalDistanceOne>totalDistanceTwo) {
            printf("Points in shortest path:\n");
            printf("(%.1lf,%.1lf)\n", x1,y1);
            for (int i=0; i<pathTwoIndex; i++) {
                printf("(%.1lf,%.1lf)\n", xPoints[pointsInPathTwo[i]], yPoints[pointsInPathTwo[i]]);
            }
            printf("(%.1lf,%.1lf)\n", x2,y2);

            printf("Number of points: %d\n", pathTwoIndex+2);
            printf("Distance: %.1lf\n", totalDistanceTwo);
        } else {
            printf("Points in shortest path:\n");
            printf("(%.1lf,%.1lf)\n", x1,y1);
            for (int i=0; i<pathOneIndex; i++) {
                printf("(%.1lf,%.1lf)\n", xPoints[pointsInPathOne[i]], yPoints[pointsInPathOne[i]]);
            }
            printf("(%.1lf,%.1lf)\n", x2,y2);

            printf("Number of points: %d\n", pathOneIndex+2);
            printf("Distance: %.1lf\n", totalDistanceOne);

            printf("OR\n");

            printf("Points in shortest path:\n");
            printf("(%.1lf,%.1lf)\n", x1,y1);
            for (int i=0; i<pathTwoIndex; i++) {
                printf("(%.1lf,%.1lf)\n", xPoints[pointsInPathTwo[i]], yPoints[pointsInPathTwo[i]]);
            }
            printf("(%.1lf,%.1lf)\n", x2,y2);

            printf("Number of points: %d\n", pathTwoIndex+2);
            printf("Distance: %.1lf\n", totalDistanceTwo);            
        }
    }
}

//recursively gets the points in the convex hull
int quickHull(double xLeft, double yLeft, double xRight, double yRight, double xPoints[], double yPoints[], int numPoints, double convexHullXPoints[], double convexHullYPoints[], int convexHullIndex) {    
    
    //base case
    if (numPoints==1) {
        convexHullXPoints[convexHullIndex] = xPoints[0];
        convexHullYPoints[convexHullIndex] = yPoints[0];
        
        printf("(%.1lf,%.1lf)\n", convexHullXPoints[convexHullIndex], convexHullYPoints[convexHullIndex]);

        convexHullIndex++;

        return convexHullIndex;
    } else if (numPoints>1) {
        double maxArea=0;
        double tempArea;
        double furthestX, furthestY;
        double xPointsLeft[numPoints];
        double yPointsLeft[numPoints];
        double xPointsRight[numPoints];
        double yPointsRight[numPoints];
        int leftPointsIndex=0;
        int rightPointsIndex=0;
        double a,b,c,sign;
        double centroidX,centroidY,signLeft,signRight;

        //find furthest point away from line (point that makes max area of triangle)
        for (int i=0; i<numPoints; i++) {
            tempArea = abs(xLeft*yRight + xPoints[i]*yLeft + xRight*yPoints[i] - xPoints[i]*yRight - xRight*yLeft - xLeft*yPoints[i]);

            if (tempArea>=maxArea) {
                maxArea = tempArea;
                furthestX = xPoints[i];
                furthestY = yPoints[i];
            }
        }

        //add point to convexHull
        convexHullXPoints[convexHullIndex] = furthestX;
        convexHullYPoints[convexHullIndex] = furthestY;

        printf("(%.1lf,%.1lf)\n", convexHullXPoints[convexHullIndex], convexHullYPoints[convexHullIndex]);

        convexHullIndex++;

        //find centroid of triangle
        centroidX = (xLeft+furthestX+xRight)/3;
        centroidY = (yLeft+furthestY+yRight)/3;

        //get new left points
        a = furthestY - yLeft;
        b = xLeft - furthestX;
        c = (xLeft*furthestY) - (yLeft*furthestX);
        signLeft = (a*centroidX) + (b*centroidY) - c;

        for (int i=0; i<numPoints; i++) {
            sign = (a*xPoints[i]) + (b*yPoints[i]) - c;
            if (signLeft<-0.000001) {
                if (sign>0.000001) {
                    xPointsLeft[leftPointsIndex] = xPoints[i];
                    yPointsLeft[leftPointsIndex] = yPoints[i];
                    leftPointsIndex++;
                }
            } else {
                if (sign<-0.000001) {
                    xPointsLeft[leftPointsIndex] = xPoints[i];
                    yPointsLeft[leftPointsIndex] = yPoints[i];
                    leftPointsIndex++;
                }
            }
            
        }

        //get new right points
        a = furthestY - yRight;
        b = xRight - furthestX;
        c = (xRight*furthestY) - (yRight*furthestX);
        signRight = (a*centroidX) + (b*centroidY) - c;

        for (int i=0; i<numPoints; i++) {
            sign = (a*xPoints[i]) + (b*yPoints[i]) - c;
            
            if (signRight>0.000001) {
                if (sign<-0.000001) {
                    xPointsRight[rightPointsIndex] = xPoints[i];
                    yPointsRight[rightPointsIndex] = yPoints[i];
                    rightPointsIndex++;
                }
            } else {
                if (sign>0.000001) {
                    xPointsRight[rightPointsIndex] = xPoints[i];
                    yPointsRight[rightPointsIndex] = yPoints[i];
                    rightPointsIndex++;
                }
            }
            
        }

        //call quickHull
        convexHullIndex = quickHull(xLeft,yLeft,furthestX,furthestY,xPointsLeft,yPointsLeft,leftPointsIndex,convexHullXPoints,convexHullYPoints,convexHullIndex);
        convexHullIndex = quickHull(furthestX,furthestY,xRight,yRight,xPointsRight,yPointsRight,rightPointsIndex,convexHullXPoints,convexHullYPoints,convexHullIndex);
    }

    return convexHullIndex;
}

//gets the points in teh convex hull from a set of points using recursion
int convexHullRecursive(double xPoints[], double yPoints[], double convexHullXPoints[], double convexHullYPoints[], int numPoints) {
    double minX;
    double minY;
    double maxX;
    double maxY;
    double a,b,c,sign;
    double upperHullX[numPoints];
    double upperHullY[numPoints];
    double lowerHullX[numPoints];
    double lowerHullY[numPoints];
    int upperHullIndex=0;
    int lowerHullIndex=0;
    int convexHullIndex=0;

    //get points with min and max x value
    minX = xPoints[0];
    minY = yPoints[0];
    maxX = xPoints[0];
    maxY = yPoints[0];
    
    for (int i=0; i<numPoints; i++) {
        if (xPoints[i]<=minX) {
            minX = xPoints[i];
            minY = yPoints[i];
        }
        if (xPoints[i]>=maxX) {
            maxX = xPoints[i];
            maxY = yPoints[i];
        }
    }

    //add to convexHull
    convexHullXPoints[convexHullIndex] = minX;
    convexHullYPoints[convexHullIndex] = minY;

    printf("(%.1lf,%.1lf)\n", convexHullXPoints[convexHullIndex], convexHullYPoints[convexHullIndex]);

    convexHullIndex++;
    
    convexHullXPoints[convexHullIndex] = maxX;
    convexHullYPoints[convexHullIndex] = maxY;

    printf("(%.1lf,%.1lf)\n", convexHullXPoints[convexHullIndex], convexHullYPoints[convexHullIndex]);

    convexHullIndex++;

    //find what side of the line all points are on
    a = maxY - minY;
    b = minX - maxX;
    c = (minX*maxY) - (minY*maxX);

    for (int i=0; i<numPoints; i++) {
        sign = (a*xPoints[i]) + (b*yPoints[i]) - c;

        if (sign>0.000001) {
            lowerHullX[lowerHullIndex] = xPoints[i];
            lowerHullY[lowerHullIndex] = yPoints[i];
            lowerHullIndex++;
        } else if (sign<-0.000001) {
            upperHullX[upperHullIndex] = xPoints[i];
            upperHullY[upperHullIndex] = yPoints[i];
            upperHullIndex++;
        }
    }
    
    //call quickHull
    convexHullIndex = quickHull(minX, minY, maxX, maxY, upperHullX, upperHullY, upperHullIndex, convexHullXPoints, convexHullYPoints, convexHullIndex);
    convexHullIndex = quickHull(minX, minY, maxX, maxY, lowerHullX, lowerHullY, lowerHullIndex, convexHullXPoints, convexHullYPoints, convexHullIndex);

    return convexHullIndex;
}

int main(void) {
    FILE* file;
    double xPoints[30000];
    double yPoints[30000];
    int i=0;
    int numConvexPoints, numConvexPoints2;
    double convexHullXPoints[30000];
    double convexHullYPoints[30000];
    double convexHullXPoints2[30000];
    double convexHullYPoints2[30000];
    double executionTimeBrute;
    double executionTimeRecursive;
    clock_t start, finish;

    //open and read file
    file = fopen("data_A2_Q2.txt", "r");

    if (file==NULL) {
        printf("Error reading file.");
    } else {
        while (!feof(file)) {
            fscanf(file, "%lf %lf", &xPoints[i], &yPoints[i]);
            i++;
        }
    }

    i=i-1;

    //call brute force algorithm for finding convex hull
    printf("Running Brute Force:\n");
    start = clock();
    numConvexPoints = convexHullBrute(xPoints, yPoints, convexHullXPoints, convexHullYPoints, i);
    finish = clock();

    executionTimeBrute = ((double)(finish - start))/CLOCKS_PER_SEC;
    
    printf("\nBrute Force Results:\n");
    for (int j=0; j<numConvexPoints; j++) {
        printf("(%.1lf,%.1lf)\n", convexHullXPoints[j], convexHullYPoints[j]);
    }
    printf("execution time = %lf seconds\n\n", executionTimeBrute);


    //call algorithm for finding shortest path
    printf("Shortest Path:\n");
    shortestPath(convexHullXPoints, convexHullYPoints, numConvexPoints);


    //call recursive algorithm for finding convex hull
    printf("\nRunning Recursive:\n");
    start = clock();
    numConvexPoints2 = convexHullRecursive(xPoints, yPoints, convexHullXPoints2, convexHullYPoints2, i);
    finish = clock();

    executionTimeRecursive = ((double)(finish - start))/CLOCKS_PER_SEC;

    printf("\nRecursive Results:\n");
    for (int j=0; j<numConvexPoints2; j++) {
        printf("(%.1lf,%.1lf)\n", convexHullXPoints2[j], convexHullYPoints2[j]);
    }
    printf("execution time = %lf seconds\n\n", executionTimeRecursive);


    //call algorithm for finding shortest path
    printf("Shortest Path:\n");
    shortestPath(convexHullXPoints2, convexHullYPoints2, numConvexPoints2);


    //close file
    fclose(file);

    return 0;
}