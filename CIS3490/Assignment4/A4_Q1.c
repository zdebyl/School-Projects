/*
Name: Zoe Debyl
Date: 3/27/2023
Assignment: Assignment 4
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//struct for node in optimal bst
typedef struct node {
    double probability;
    char word[50000];
    struct node* leftchild;
    struct node* rightchild;
} node;

//creates node in optimal bst for dynamic programming algorithm
node* createnodedynamic(double* probabilities, char** words, double** ctable, int** rtable, int left, int right, int total) {
    if (left>right) {
        return NULL;
    } else {
        node* root = (node*)malloc(sizeof(node));
        int rootvalue;

        //get root value
        rootvalue = rtable[left][right];

        //set values
        root->probability = ctable[left][right];
        strcpy(root->word, words[rootvalue]);

        //get left and right subtrees
        root->leftchild = createnodedynamic(probabilities, words, ctable, rtable, left, (rootvalue-1), total);
        root->rightchild = createnodedynamic(probabilities, words, ctable, rtable, (rootvalue+1), right, total);

        return root;
    }
}

//creates and searches optimal bst using dynamic programming algorithm
void bstdynamic(double* probabilities, char** userwords, int total) {
    double** ctable;
    int** rtable;
    double minval;
    int kmin;
    double prob[total+1];
    char* words[total+1];
    double sum;
    int j;
    char key[50000];
    char wordcheck[50000];
    int left, right;
    int found=0;

    //change so arrays start at index 1
    for (int i=total; i>0; i--) {
        prob[i] = probabilities[i-1];
        words[i] = userwords[i-1];
    }

    /*Create average number table and root table*/
    //initialize tables
    rtable = (int**)malloc(sizeof(int*)*(total+2));
    ctable = (double**)malloc(sizeof(double*)*(total+2));

    for (int i=0; i<total+2; i++) {
        rtable[i] = (int*)malloc(sizeof(int)*(total+1));
        ctable[i] = (double*)malloc(sizeof(double)*(total+1));

        for (int j=0; j<total+1; j++) {

            rtable[i][j]=0;
            ctable[i][j]=0;
        }
    }

    //set up first diagonal in rtable, and first two diagonals in ctable
    for (int i=1; i<=total; i++) {
        ctable[i][i-1] = 0;
        ctable[i][i] = prob[i];
        rtable[i][i] = i;
    }

    ctable[total+1][total] = 0;

    //calculate all other values in the table
    for (int d=1; d<=total-1; d++) {
        for (int i=1; i<=total-d; i++) {
            j = i + d;
            minval = 100000;

            for (int k=i; k<=j; k++) {
                if ((ctable[i][k-1] + ctable[k+1][j])<minval) {
                    minval = ctable[i][k-1] + ctable[k+1][j];
                    kmin = k;
                }
            }

            rtable[i][j] = kmin;
            sum = prob[i];

            for (int s=i+1; s<=j; s++) {
                sum = sum + prob[s];
            }

            ctable[i][j] = minval + sum;
        }
    }

    /*Create tree*/
    //set original values
    left = 1;
    right = total;
    node* root = createnodedynamic(probabilities, words, ctable, rtable, left, right, total);
    
    /*Search*/
    //get key from user
    printf("Enter a key: ");
    scanf("%s", key);
    
    while (root!=NULL) {
        strcpy(wordcheck, root->word);

        //found string
        if (strcmp(wordcheck, key)==0) {
            printf("Compared with %s (%.3lf), found.\n", wordcheck, root->probability);
            found=1;
            break;
        }
        //left subtree
        else if (strcmp(wordcheck, key)>0) {
            printf("Compared with %s (%.3lf), go left subtree.\n", wordcheck, root->probability);
            root = root->leftchild;
        }
        //right subtree
        else {
            printf("Compared with %s (%.3lf), go right subtree.\n", wordcheck, root->probability);
            root = root->rightchild;
        }
    }

    //not found
    if (found==0) {
        printf("Not found.\n");
    }

    /*Free memory*/
    for (int i=0; i<total+2; i++) {
        free(rtable[i]);
        free(ctable[i]);
    }

    free(rtable);
    free(ctable);
}

//creates node in optimal bst for greedy technique algorithm
node* createnodegreedy(double* probabilities, char** words, int total) {
    if (total==0) {
        return NULL;
    } else {
        node* root = (node*)malloc(sizeof(node));
        double max=0;
        int maxIndex=-1;

        //find highest probability and set it to current parent
        for (int i=0; i<total; i++) {
            if (probabilities[i]>max) {
                max = probabilities[i];
                maxIndex = i;
            }
        }

        //set values
        root->probability = max;
        strcpy(root->word, words[maxIndex]);
        
        //get left and right subtree values
        int totalLeft = maxIndex;
        int totalRight = total - maxIndex - 1;

        double probabilitiesLeft[totalLeft];
        double probabilitiesRight[totalRight];

        char* wordsLeft[totalLeft];
        char* wordsRight[totalRight];

        for (int i=0; i<totalLeft; i++) {
            probabilitiesLeft[i] = probabilities[i];
            wordsLeft[i] = malloc(sizeof(char)*strlen(words[i]));
            strcpy(wordsLeft[i], words[i]);
        }

        for (int i=0; i<totalRight; i++) {
            probabilitiesRight[i] = probabilities[maxIndex+1+i];
            wordsRight[i] = malloc(sizeof(char)*strlen(words[maxIndex+1+i]));
            strcpy(wordsRight[i], words[maxIndex+1+i]);
        }

        //get left and right subtrees
        root->leftchild = createnodegreedy(probabilitiesLeft, wordsLeft, totalLeft);
        root->rightchild = createnodegreedy(probabilitiesRight, wordsRight, totalRight);

        return root;
    }
}

//creates and searches optimal bst using greedy technique algorithm
void bstgreedy(double* probabilities, char** words, int total) {
    node* root;
    char key[50000];
    char wordcheck[50000];
    int found=0;

    /*Create BST*/
    root = createnodegreedy(probabilities, words, total);

    /*Search*/
    //get key from user
    printf("Enter a key: ");
    scanf("%s", key);
    
    while (root!=NULL) {
        strcpy(wordcheck, root->word);

        //found string
        if (strcmp(wordcheck, key)==0) {
            printf("Compared with %s (%.3lf), found.\n", wordcheck, root->probability);
            found=1;
            break;
        }
        //left subtree
        else if (strcmp(wordcheck, key)>0) {
            printf("Compared with %s (%.3lf), go left subtree.\n", wordcheck, root->probability);
            root = root->leftchild;
        }
        //right subtree
        else {
            printf("Compared with %s (%.3lf), go right subtree.\n", wordcheck, root->probability);
            root = root->rightchild;
        }
    }

    //not found
    if (found==0) {
        printf("Not found.\n");
    }
}

//reads file, gets probabilities, sorts words alphabetically and calls both algorithms for optimal bst
int main(void) {
    FILE* file;
    char* filestring;
    int length;
    char* split;
    char* words[2045];
    int i=0;
    char* diffwords[2045];
    double probabilities[2045];
    int diffwordsIndex=0;
    int found=0;
    char* temp="\0";
    double tempnum=0;

    /*Open and read file*/
    file = fopen("data_A4_Q1.txt", "r");

    if (file==NULL) {
        printf("Error reading file.");
    } else {
        fseek(file, 0, SEEK_END);
        length = ftell(file);
        fseek(file, 0, SEEK_SET);
        filestring = malloc(length);

        fread(filestring, length, 1, file);
    }

    /*Get probabilities*/
    //split string into words
    split = strtok(filestring, " \n");

    while(split!=NULL) {
        words[i] = malloc(sizeof(char)*strlen(split));
        strcpy(words[i], split);
        i++;
        split = strtok(NULL, " \n");
    }

    //initialize probabilities array
    for (int j=0; j<i; j++) {
        probabilities[j] = 1;
    }

    //combine common words and calculate number of occurences
    for (int j=0; j<i; j++) {
        found=0;

        for (int k=0; k<j; k++) {
            if (strcmp(words[j], words[k])==0) {
                found=1;
            }
        }

        if (found==0) {
            diffwords[diffwordsIndex] = malloc(sizeof(char)*strlen(words[j]));
            strcpy(diffwords[diffwordsIndex], words[j]);
            diffwordsIndex++;
        } else {
            for (int l=0; l<diffwordsIndex; l++) {
                if (strcmp(diffwords[l], words[j])==0) {
                    probabilities[l]++;
                    break;
                }
            }
        }
    }

    //calculate probabilities
    for (int j=0; j<diffwordsIndex; j++) {
        probabilities[j] = probabilities[j] / i;
    }

    /*Sort alphabetically*/
    for (int j=0; j<diffwordsIndex; j++) {
        for (int k=j+1; k<diffwordsIndex; k++) {
            if(strcmp(diffwords[j], diffwords[k])>0) {
                temp = malloc(sizeof(char)*strlen(diffwords[j]));
                strcpy(temp, diffwords[j]);
                strcpy(diffwords[j], diffwords[k]);
                strcpy(diffwords[k], temp);

                tempnum = probabilities[j];
                probabilities[j] = probabilities[k];
                probabilities[k] = tempnum;
            }
        }
    }
    
    /*Dynamic programming algorithm for bst*/
    printf("Dynamic programming algorithm:\n");
    bstdynamic(probabilities, diffwords, diffwordsIndex);

    /*Greedy technique algorithm for bst*/
    printf("\nGreedy algorithm:\n");
    bstgreedy(probabilities, diffwords, diffwordsIndex);

    /*Free memory*/
    free(filestring);
    free(temp);

    for (int j=0; j<i; j++) {
        free(words[j]);
    }

    for (int j=0; j<diffwordsIndex; j++) {
        free(diffwords[j]);
    }

    return 0;
}
