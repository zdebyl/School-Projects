#include "debylZoeA1.h"

//open file
FILE *openFileForReading(char *fileName) {
    FILE *inputFile;

    inputFile = fopen(fileName, "r");

    if(inputFile==NULL) {
        return NULL;
    }
    else {
        return inputFile;
    }
}

//store movie titles in array
int readMovies(FILE *file, char movieNames[NUMBER_MOVIES][MAX_STR]) {
    int i=0;

    if (file==NULL) {
        return 0;
    }
    else {
        while(!feof(file)) {
            fgets(movieNames[i], MAX_STR, file);
            if(!feof(file)) {
                movieNames[i][strlen(movieNames[i])-1] = '\0';
            }
            i++;
        }

        if(i==NUMBER_MOVIES) {
            return 1;
        }
        else {
            return 0;
        }
    }
}

//store reviews in struct
int readReviews(FILE *file, struct reviewStruct reviews[NUMBER_REVIEWERS]) {
    int i=0;
    char temp;

    if (file==NULL) {
        return 0;
    }
    else {
        while(!feof(file)) {
            fscanf(file, "%s ", reviews[i].reviewer);

            for (int j=0; j<NUMBER_MOVIES; j++) {
                fscanf(file, "%c ", &temp);

                if ((temp=='y')||(temp=='Y')) {
                    reviews[i].feedback[j] = 1;
                }
                else if ((temp=='n')||(temp=='N')) {
                    reviews[i].feedback[j] = 0;
                }
            }

            i++;
        }

        if(i==NUMBER_REVIEWERS) {
            return 1;
        }
        else {
            return 0;
        }
    }

}

//finds most critical reviewers and stores them in array
int getMostCriticalReviewers(struct reviewStruct reviews[NUMBER_REVIEWERS], char mostCriticalReviewers[NUMBER_REVIEWERS][MAX_STR]) {
    int max=0;
    int temp;
    int a=0;

    //finds most number of negative reviews
    for (int i=0; i<NUMBER_REVIEWERS; i++) {
        temp = 0;

        for (int j=0; j<NUMBER_MOVIES; j++) {
            if (reviews[i].feedback[j] == 0) {
                temp++;
            }
        }

        if (temp>max) {
            max = temp;
        }
    }

    //store most critical reviewers
    for (int i=0; i<NUMBER_REVIEWERS; i++) {
        temp = 0;

        for (int j=0; j<NUMBER_MOVIES; j++) {
            if (reviews[i].feedback[j] == 0) {
                temp++;
            }
        }

        if (temp==max) {
            strcpy(mostCriticalReviewers[a], reviews[i].reviewer);
            a++;
        }
    }

    return a;   
}

//finds most recommended movies and stores them in an array
int getMostRecommendedMovies(const char movieNames[NUMBER_MOVIES][MAX_STR], const struct reviewStruct reviews[NUMBER_REVIEWERS], char mostRecommendedMovies[NUMBER_MOVIES][MAX_STR]) {
    int max=0;
    int temp;
    int a=0;

    //finds most number of positive reviews
    for (int i=0; i<NUMBER_MOVIES; i++) {
        temp = 0;

        for (int j=0; j<NUMBER_REVIEWERS; j++) {
            if (reviews[j].feedback[i] == 1) {
                temp++;
            }
        }

        if (temp>max) {
            max = temp;
        }
    }

    //stores most recommended movies
    for (int i=0; i<NUMBER_MOVIES; i++) {
        temp = 0;

        for (int j=0; j<NUMBER_REVIEWERS; j++) {
            if (reviews[j].feedback[i] == 1) {
                temp++;
            }
        }

        if (temp==max) {
            strcpy(mostRecommendedMovies[a], movieNames[i]);
            a++;
        }
    }

    return a;
}

//calculates score of movie
int predictMovie(const char movie[MAX_STR]) {
    char words[MAX_WORDS][MAX_STR];
    int wordCount=0;
    int charCount=0;
    int score=0;
    int check=0;

    //read words and get word count
    for(int i=0; i<strlen(movie); i++) {
        if (movie[i] == ' ') {
            words[wordCount][charCount] = '\0';
            wordCount++;
            charCount = 0;
        }
        else {
            words[wordCount][charCount] = movie[i];
            charCount++;
        }
    }

    wordCount = wordCount + 1;

    //calculate score
    if (wordCount > 2) {
        score = score - 1;
    }
    else if (wordCount == 1) {
        score = score - 2;
    }

    for (int j=0; j<wordCount; j++) {
        if ((strlen(words[j])%2) == 0) {
            check++;
        }
    }
    if (check>=2) {
        score = score + 1; 
    }

    check = 1;

    for (int j=0; j<wordCount-1; j++) {
        if (strlen(words[j]) != strlen(words[j+1])) {
            check = 0;
        }
    }
    if (check==1) {
        score = score + 2; 
    }

    //adjust score if over or under limit
    if (score<-2) {
        score = -2;
    }
    else if (score>2) {
        score = 2;
    }

    return score;
}

//gets word and character count
int enumerateMovie(const char movie[MAX_STR], int charCounts[MAX_WORDS]) {
    int wordCount=0;
    int charCount=0;

    for(int i=0; i<strlen(movie); i++) {
        if (movie[i] == ' ') {
            charCounts[wordCount] = charCount;
            wordCount++;
            charCount = 0;
        }
        else {
            charCount++;
        }
    }

    charCounts[wordCount] = charCount;

    wordCount = wordCount + 1;

    return wordCount;
}