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

//counts the number of inversions in an array using brute force
int countInversionsBruteForce(int arrayNums[], int arraySize) {
    int numInversions = 0;

    //count inversions
    for (int i=0; i<arraySize; i++) {
        for (int j=i+1; j<arraySize; j++) {
            if (arrayNums[i]>arrayNums[j]) {
                numInversions++;
            }
        }
    }

    return numInversions;
}

//merges two sorted arrays into one sorted array and counts the inversions
int count(int leftArray[], int rightArray[], int sortedArray[], int leftArraySize, int rightArraySize) {
    int i=0;
    int j=0;
    int k=0;
    int numInversions=0;

    while(i<leftArraySize && j<rightArraySize) {
        //sort and merge elements and count inversions
        if (leftArray[i]>rightArray[j]) {
            numInversions = numInversions + leftArraySize - i;
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

    return numInversions;
}

//counts the number of inversions in an array using recursion
int countInversionsRecursive(int arrayNums[], int arraySize) {
    int numInversions = 0;
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
        numInversions = countInversionsRecursive(left, mid);
        numInversions = numInversions + countInversionsRecursive(right, arraySize-mid);
        numInversions = numInversions + count(left, right, arrayNums, mid, arraySize-mid);
    }

    return numInversions;
}

int main(void) {
    FILE* file;
    char filename[200];
    int arrayNums[50000];
    int i=0;
    int numInversionsBrute;
    int numInversionsRecursive;
    double executionTimeBrute;
    double executionTimeRecursive;
    clock_t start, finish;

    //get filename
    printf("Enter a filename: ");
    scanf("%s", filename);

    //open and read file
    file = fopen(filename, "r");

    if (file==NULL) {
        printf("Error reading file.");
    } else {
        while (!feof(file)) {
            fscanf(file, "%d", &arrayNums[i]);
            i++;
        }
    }

    i=i-1;

    //call brute force algorithm and print number of inversions and execution time
    start = clock();
    numInversionsBrute = countInversionsBruteForce(arrayNums, i);
    finish = clock();

    executionTimeBrute = ((double)(finish - start))/CLOCKS_PER_SEC;

    printf("Brute Force:\nnumber of inverions = %d\nexecution time = %lf seconds\n\n", numInversionsBrute, executionTimeBrute);

    //call recursive algorithm and print number of inversions and execution time
    start = clock();
    numInversionsRecursive = countInversionsRecursive(arrayNums, i);
    finish = clock();

    executionTimeRecursive = ((double)(finish - start))/CLOCKS_PER_SEC;

    printf("Recursive:\nnumber of inverions = %d\nexecution time = %lf seconds\n\n", numInversionsRecursive, executionTimeRecursive);

    //close file
    fclose(file);

    return 0;
}