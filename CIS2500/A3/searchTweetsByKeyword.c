#include "headerA3.h"

int searchTweetsByKeyword(tweet * tweetList) {
    //declare variables
    int matchFound = 0;
    char keyWord[141];

    //get user input
    printf("Enter a keyword to search: ");
    scanf("%s", keyWord);

    //allow for different case
    char keyWord2[141];
    char firstLetter = keyWord[0];

    strcpy(keyWord2, keyWord);

    if (firstLetter >= 97 && firstLetter <= 122) {
        firstLetter = firstLetter - 32;
    }
    else if (firstLetter >= 65 && firstLetter <=90) {
        firstLetter = firstLetter + 32;
    }
    
    keyWord2[0] = firstLetter;

    //check if keyword is in tweet
    tweet *temp = tweetList;

    while (temp!=NULL) {
        if (strstr(temp->text, keyWord) != NULL || strstr(temp->text, keyWord2) != NULL) {
            printf("Match found for '%s': %s wrote: %s", keyWord, temp->user, temp->text);
            matchFound = 1;
        }

        temp=temp->next;
    }

    return matchFound;
}