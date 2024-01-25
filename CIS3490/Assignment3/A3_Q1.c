/*
Name: Zoe Debyl
Date: 2/7/2023
Assignment: Assignment 3
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct {
    int min;
    int max;
} range;

//compute the number that is in the most intervals and how many intervals it is in using brute force
void maxIntervalBrute(range interval[], int numPoints, int *maxVal, int *maxCount) {
    int min=interval[0].min;
    int max=interval[0].max;
    int intervalCount = 0;
    int maxIntervalCount = -1;
    int maxNum;

    //get min and max values
    for (int i=0; i<numPoints; i++) {
        //min
        if (interval[i].min<min) {
            min = interval[i].min;
        }
        //max
        if (interval[i].max>max) {
            max = interval[i].max;
        }
    }

    //check all values in range for how many intervals they're in
    for (int i=min; i<=max; i++) {
        intervalCount = 0;

        for (int j=0; j<numPoints; j++) {
            if (i>interval[j].min&&i<interval[j].max) {
                intervalCount++;
            }
        }

        if (intervalCount>maxIntervalCount) {
            maxIntervalCount = intervalCount;
            maxNum = i;
        }
    }

    *maxVal = maxNum;
    *maxCount = maxIntervalCount;
}

//merges two sorted arrays into one sorted array
void merge(int leftArray[], int rightArray[], int sortedArray[], int leftArraySize, int rightArraySize) {
    int i=0;
    int j=0;
    int k=0;

    while(i<leftArraySize && j<rightArraySize) {
        //sort and merge elements and count inversions
        if (leftArray[i]>rightArray[j]) {
            sortedArray[k] = rightArray[j];
            j++;
        } else {
            sortedArray[k] = leftArray[i];
            i++;
        }

        k++;
    }

    //add the rest of array leftover to sorted array
    if (i==leftArraySize) {
        for (int l=j; l<rightArraySize; l++) {
            sortedArray[k] = rightArray[l];
            k++;
        }
    } else {
        for (int l=i; l<leftArraySize; l++) {
            sortedArray[k] = leftArray[l];
            k++;
        }
    }
}

//divides an array and sorts it recursively
void mergesort(int arrayNums[], int arraySize) {
    int mid;

    mid = arraySize/2;

    int left[mid];
    int right[arraySize-mid];

    if (arraySize>1) {
        //get left array
        for (int i=0; i<mid; i++) {
            left[i] = arrayNums[i];
        }

        //get right array
        for (int i=0; i<arraySize-mid; i++) {
            right[i] = arrayNums[mid+i];
        }

        //split and sort arrays while counting inversions
        mergesort(left, mid);
        mergesort(right, arraySize-mid);
        merge(left, right, arrayNums, mid, arraySize-mid);
    }
}

//compute the number that is in the most intervals and how many intervals it is using presorting
void maxIntervalPresort(range interval[], int numPoints, int *maxVal, int *maxCount) {
    int sortedmin[numPoints];
    int sortedmax[numPoints];
    int currCount=0;
    int maximumCount=-1;
    int maximumVal;
    int minIndex=0;
    int maxIndex=0;
    int toAdd=0;

    for (int i=0; i<numPoints; i++) {
        sortedmin[i] = interval[i].min;
        sortedmax[i] = interval[i].max;
    }

    //sort min and max values
    mergesort(sortedmin, numPoints);
    mergesort(sortedmax, numPoints);

    //count max number in range
    for (int i=sortedmin[0]; i<sortedmax[numPoints-1]; i++) {
        currCount = currCount + toAdd;
        toAdd = 0;

        while(i==sortedmin[minIndex]) {
            toAdd++;
            minIndex++;
        }

        while(i==sortedmax[maxIndex]) {
            currCount=currCount-1;
            maxIndex++;
        }

        if (currCount>maximumCount) {
            maximumCount = currCount;
            maximumVal = i;
        }
    }

    *maxVal = maximumVal;
    *maxCount = maximumCount;
}

int main(void) {
    FILE* file;
    char filename[200];
    range interval[30000];
    int i=0;
    int maxVal, maxCount;
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
            fscanf(file, "%d %d", &interval[i].min, &interval[i].max);
            i++;
        }
    }

    i=i-1;

    //call brute algorithm
    start = clock();
    maxIntervalBrute(interval, i, &maxVal, &maxCount);
    finish = clock();

    executionTime = ((double)(finish - start))/CLOCKS_PER_SEC;

    printf("\nBrute Force:\n");
    printf("Maximum number of intervals: %d\n", maxCount);
    printf("The intervals include the point: %d\n", maxVal);
    printf("Time for finding the maximum number: %lf seconds\n", executionTime);

    //call recursive algorithm
    start = clock();
    maxIntervalPresort(interval, i, &maxVal, &maxCount);
    finish = clock();

    executionTime = ((double)(finish - start))/CLOCKS_PER_SEC;

    printf("\nPresorting:\n");
    printf("Maximum number of intervals: %d\n", maxCount);
    printf("The intervals include the point: %d\n", maxVal);
    printf("Time for finding the maximum number: %lf seconds\n", executionTime);    

    return 0;
}
