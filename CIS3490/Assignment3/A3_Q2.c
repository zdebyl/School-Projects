/*
Name: Zoe Debyl
Date: 2/7/2023
Assignment: Assignment 3
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

//perform string search using brute force algorithm
void brutestringsearch(char* filestring, char* pattern) {
    int count=0;
    int shifts=0;
    int numSame=0;

    //go through filestring
    for (int i=0; i<strlen(filestring)-strlen(pattern)+1; i++) {
        numSame=0;

        //go through pattern
        for (int j=0; j<strlen(pattern); j++) {
            if (filestring[i+j]==pattern[j]) {
                numSame++;
            } else {
                break;
            }
        }

        //pattern found
        if (numSame==strlen(pattern)) {
            count++;
        }

        shifts++;
    }

    printf("Count: %d\n", count);
    printf("Shifts: %d\n", shifts);
}

//get index for shift table using ascii value of character
int shiftTableIndex(int ascii) {
    int index;

    if (ascii>64 && ascii<91) {
        index=ascii-39;
    } else if (ascii>96 && ascii<123) {
        index=ascii-97;
    }

    return index;
}

//perform string search using Horspool's algorithm
void horspools(char* filestring, char* pattern) {
    int shiftTable[52];
    int lengthPattern=strlen(pattern);
    int value=1;
    int index;
    int patternIndex=lengthPattern-1;
    int stringIndex=patternIndex;
    int lastLetterIndex;
    int numSame=0;
    int count=0;
    int shifts=-1;

    //preprocess
    //initialize all values to 0
    for (int i=0; i<52; i++) {
        shiftTable[i] = 0;
    }

    //set values in table from pattern
    for (int i=lengthPattern-2; i>=0; i--) {
        index = shiftTableIndex(pattern[i]);
    
        if (shiftTable[index]==0) {
            shiftTable[index]=value;
        }

        value++;
    }

    //set values in table not from pattern to length
    for (int i=0; i<52; i++) {
        if (shiftTable[i] == 0) {
            shiftTable[i] = lengthPattern;
        }
    }

    //string search
    while (stringIndex<strlen(filestring)) {
        lastLetterIndex = shiftTableIndex(filestring[stringIndex]);
        numSame = 0;

        //compare strings
        for (int i=0; i<lengthPattern; i++) {
            if (filestring[stringIndex-i]!=pattern[patternIndex-i]) {
                break;
            } else {
                numSame++;
            }
        }

        //strng found
        if (numSame==lengthPattern) {
            count++;
        }

        //shift
        stringIndex = stringIndex+shiftTable[lastLetterIndex];
        shifts++;
    }

    printf("Count: %d\n", count);
    printf("Shifts: %d\n", shifts);
}

//perform string search using Boyer-Moore's algorithm
void boyermoore(char* filestring, char* pattern) {
    int badSymbolTable[52];
    int goodSuffixTable[strlen(pattern)-1];
    char newString[strlen(pattern)-1];
    int lengthPattern=strlen(pattern);
    int value=1;
    int index;
    int patternIndex=lengthPattern-1;
    int stringIndex=patternIndex;
    int lastLetterIndex;
    int numSame=0;
    int count=0;
    int shifts=-1;
    int shiftbadsymbol;

    //preprocess
    //bad symbol table
    //initialize all values to 0
    for (int i=0; i<52; i++) {
        badSymbolTable[i] = 0;
    }

    //set values in table from pattern
    for (int i=lengthPattern-2; i>=0; i--) {
        index = shiftTableIndex(pattern[i]);
    
        if (badSymbolTable[index]==0) {
            badSymbolTable[index]=value;
        }

        value++;
    }

    //set values in table not from pattern to length
    for (int i=0; i<52; i++) {
        if (badSymbolTable[i] == 0) {
            badSymbolTable[i] = lengthPattern;
        }
    }

    //good suffix table
    //reset values
    int l=0;
    int m=0;
    int found=0;

    //set values in table
    for (int i=0; i<lengthPattern-1; i++) {
        value=0;

        //get new string
        for (int j=0; j<i+1; j++) {
            newString[i-j] = pattern[lengthPattern-1-j];
        }

        newString[i+1] = '\0';

        //compare new string with pattern
        for (int j=lengthPattern-2; j>=0; j--) {
            numSame=0;
            l=0;

            for (int k=strlen(newString)-1; k>=0; k--) {
                if (newString[k]==pattern[j-l]) {
                    numSame++;
                } else {
                    break;
                }

                l++;
            }

            value++;

            if (numSame==strlen(newString)) {
                break;
            }
        }
        
        if (numSame==strlen(newString)) {
            goodSuffixTable[i] = value;
        } else {   
            l=0;

            //if not found, look for smaller prefix in pattern   
            for (int j=strlen(newString)-2; j>=0; j--) {
                found=0;
                m=0;

                for (int k=strlen(newString)-1; k>l; k--) {
                    if (newString[k]!=pattern[j-m]) {
                        found=1;
                        break;
                    }

                    m++;
                }

                if (found==0) {
                    value = lengthPattern-strlen(newString)+1+l;
                    break;
                }

                l++;
            }

            //set value in table, if still not found set to length
            if (found==0 && strlen(newString)!=1) {
                goodSuffixTable[i] = value;
            } else {
                goodSuffixTable[i] = lengthPattern;
            }
            
        }
    }

    //string search
    while (stringIndex<strlen(filestring)) {
        numSame = 0;

        //compare strings
        for (int i=0; i<lengthPattern; i++) {
            if (filestring[stringIndex-i]!=pattern[patternIndex-i]) {
                break;
            } else {
                numSame++;
            }
        }

        lastLetterIndex = shiftTableIndex(filestring[stringIndex-numSame]);

        //string found and shifts
        if (numSame==lengthPattern) {
            count++;
            stringIndex = stringIndex+goodSuffixTable[lengthPattern-2];
        } else {
            if (numSame==0) {
                stringIndex = stringIndex+badSymbolTable[lastLetterIndex];
            } else {
                //get bad symbol entry
                if ((badSymbolTable[lastLetterIndex]-numSame)>1) {
                    shiftbadsymbol = badSymbolTable[lastLetterIndex]-numSame;
                } else {
                    shiftbadsymbol = 1;
                }

                //check if bad symbol or good suffix shift is larger, and shift by the larger one
                if (shiftbadsymbol>goodSuffixTable[numSame-1]) {
                    stringIndex = stringIndex+badSymbolTable[lastLetterIndex]-numSame;
                } else {
                    stringIndex = stringIndex+goodSuffixTable[numSame-1];
                }
            }
        }

        shifts++;
    }

    printf("Count: %d\n", count);
    printf("Shifts: %d\n", shifts);
}

int main(void) {
    FILE* file;
    char* filestring;
    int length;
    char pattern[100];
    clock_t start, finish;
    double executionTime;

    //open and read file
    file = fopen("data_A3_Q2.txt", "r");

    if (file==NULL) {
        printf("Error reading file.");
    } else {
        fseek(file, 0, SEEK_END);
        length = ftell(file);
        fseek(file, 0, SEEK_SET);
        filestring = malloc(length);

        fread(filestring, length, 1, file);
    }

    //get pattern
    printf("Enter a pattern to search for: ");
    scanf("%s", pattern);

    //brute force
    printf("\nBrute Force:\n");

    start = clock();
    brutestringsearch(filestring, pattern);
    finish = clock();
    
    executionTime = ((double)(finish - start))/CLOCKS_PER_SEC;
    printf("Execution time: %lf seconds\n", executionTime);

    //Horspool's
    printf("\nHorspool's:\n");

    start = clock();
    horspools(filestring, pattern);
    finish = clock();
    
    executionTime = ((double)(finish - start))/CLOCKS_PER_SEC;
    printf("Execution time: %lf seconds\n", executionTime);

    //Boyer-Moore
    printf("\nBoyer-Moore:\n");

    start = clock();
    boyermoore(filestring, pattern);
    finish = clock();
    
    executionTime = ((double)(finish - start))/CLOCKS_PER_SEC;
    printf("Execution time: %lf seconds\n", executionTime);

    //close and free
    free(filestring);
    fclose(file);

    return 0;
}
