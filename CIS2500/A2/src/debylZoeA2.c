#include "../include/debylZoeA2.h"

char * readFile (char * filename) {
    //declare and initialize variables
    FILE *inputFile;
    char storeLine[100][MAX_LENGTH*MAX_WORDS];
    char *storeFile = malloc(sizeof(char));
    int i=0;
    int check=0;
    int totalSize=0;

    //open file
    inputFile = fopen(filename, "r");

    //check if file is empty
    if(inputFile==NULL) {
        return NULL;
    }
    else {
        //read until end of file
        while(!feof(inputFile)) {
            //read line into string variable
            fgets(storeLine[i], (MAX_WORDS*MAX_LENGTH), inputFile);

            //reallocate size of variable
            totalSize = totalSize + sizeof(char*)*strlen(storeLine[i]);
            storeFile = realloc(storeFile, totalSize);
            
            //check if string is empty and store info in correct variable
            if (check==0) {
                strcpy(storeFile, storeLine[i]);
                check = 1;
            }
            else {
                strcat(storeFile, storeLine[i]);
            }

            i++;
        }
    }

    //close file
    fclose(inputFile);

    //return file
    return storeFile;
}

char * stretchMe (char * aStringToStretch) {
    //declare and initialize variables
    char *newString;
    int numChars;
    int totalChars;
    int k=0;
 
    //get number of characters
    numChars = strlen(aStringToStretch);
 
    int stretchFactor[numChars];
 
    //get integers to stretch word from user
    for (int i=0; i<numChars; i++) {
        scanf("%d", &stretchFactor[i]);
    }
 
    //get total characters
    totalChars = numChars;
 
    for (int j=0; j<numChars; j++) {
        totalChars = totalChars + stretchFactor[j];
    }
 
    //make new string
    newString = malloc(sizeof(char)*totalChars);
 
    for(int i=0; i<numChars; i++) {
        for (int j=0; j<stretchFactor[i]; j++) {
            newString[k]=aStringToStretch[i];
            k++;
        }
    }

    return newString;
}

int splitMe (char * aStringToSplit, char static2D [MAX_WORDS][MAX_LENGTH]) {
    //declare and intialize variables
    int i=0;
    int numWords=0;
    int check=0;
    int letter=0;
    int word=0;
    
    //go through every letter in the string
    while (aStringToSplit[i] != '\0') {
        //if there is a new word
        if (aStringToSplit[i] == ' ' || aStringToSplit[i] == '\n') {
            //check to see if there has already been a space or next line character
            if (check==0) {
                static2D[word][letter] = '\0';
                numWords++;
                word++;
                letter=0;
            }
            check=1;
        }
        //store words in new array
        else {
            static2D[word][letter] = aStringToSplit[i];
            letter++;
            check=0;
        }
        i++;
    }
    
    //if string ends in a space or not
    if (aStringToSplit[i-1] != ' ' && aStringToSplit[i-1] != '\n') {
        static2D[word][letter] = '\0';
        numWords++;
    }
    
    //return the number of words
    return numWords;
}

int shrinkMe (char * aStringToShrink) {
    //declare and initialize variables
    int i=0;
    int numPunctuation=0;
    int temp;
    
    //go through every letter in the string
    while (aStringToShrink[i] != '\0') {
        //check if its a punctuation
        if (aStringToShrink[i]=='.' || aStringToShrink[i]==':' || aStringToShrink[i]==';' || aStringToShrink[i]=='?' || aStringToShrink[i]=='!') {
            numPunctuation++;
            temp = i;

            //remove the punctuation
            while (aStringToShrink[i] != '\0') {
                aStringToShrink[i] = aStringToShrink[i+1];
                i++;
            }
            i = temp;
        }
        i++;
    }

    //return the number of punctuations
    return numPunctuation;
}

bool isItAPalindrome (char * aString) {
    //declare and initialize variables
    char storeWords[MAX_WORDS][MAX_LENGTH];
    int i=0;
    int check=0;
    int numWords=0;
    int letter=0;
    int check2;

    //go through every letter in the string
    while (aString[i] != '\0') {
        //if there is a new word
        if (aString[i] == ' ' || aString[i] == '\n') {
            //check to see if there has already been a space or next line character
            if (check==0) {
                storeWords[numWords][letter] = '\0';
                numWords++;
                letter=0;
            }
            check=1;
        }
        else {
            //remove punctuation and store in new array
            if (aString[i]!='.' && aString[i]!=':' && aString[i]!=';' && aString[i]!='?' && aString[i]!='!') {
                storeWords[numWords][letter] = aString[i];
                letter++;
            }
            check=0;
        }
        i++;
    }
    
    //if string ends in a space or not
    if (aString[i-1] != ' ' && aString[i-1] != '\n') {
        storeWords[numWords][letter] = '\0';
        numWords++;
    }

    //check if every word is a palindrome
    check2=0;
    
    //go through each word
    for (int j=0; j<numWords; j++) {
        //compare letters in the word
        for (int l=0; l<(strlen(storeWords[j]))/2; l++) {
            //if letters don't match (not a palindrome)
            if (storeWords[j][l] != storeWords[j][strlen(storeWords[j])-1-l]) {
                check2=1;
            }
        }
    }
    
    //return if it is a palindrome or not
    if (check2 == 0) {
        return true;
    }
    else {
        return false;
    }
}

void printSuffixes (char * aString, int whichWord, char * desiredSuffix) {
    //declare and initialize variables
    char storeWords[MAX_WORDS][MAX_LENGTH];
    int i=0;
    int check=0;
    int numWords=0;
    int letter=0;

    //go through every letter in the string
    while (aString[i] != '\0') {
        //if there is a new word
        if (aString[i] == ' ' || aString[i] == '\n') {
            //check to see if there has already been a space or next line character
            if (check==0) {
                storeWords[numWords][letter] = '\0';
                numWords++;
                letter=0;
            }
            check=1;
        }
        else {
            //remove punctuation and store in new array
            if (aString[i]!='.' && aString[i]!=':' && aString[i]!=';' && aString[i]!='?' && aString[i]!='!') {
                storeWords[numWords][letter] = aString[i];
            }
            letter++;
            check=0;
        }
        i++;
    }

    //if string ends in a space or not
    if (aString[i-1] != ' ' && aString[i-1] != '\n') {
        storeWords[numWords][letter] = '\0';
        numWords++;
    }

    //print suffixes
    for (int k=0; k<strlen(storeWords[whichWord-1]); k++) {
        printf("%c%s\n", storeWords[whichWord-1][k], desiredSuffix);
    }
}