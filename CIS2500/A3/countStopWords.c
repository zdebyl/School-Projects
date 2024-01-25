#include "headerA3.h"

void countStopWords(tweet * tweetList) {
    //declare variables
    int numStopWords=0;
    int numTweets=0;
    char tempTweet[141];
    char words[200][200];
    int i, j, k;
    tweet* temp;

    //traverse list
    temp = tweetList;

    while (temp!=NULL) {
        //split string into words
        strcpy(tempTweet, temp->text);
        k=0;
        j=0;

        for (i=0; i<strlen(tempTweet)+1; i++) {
            if (tempTweet[i] != ' ') {
                words[j][k] = tempTweet[i];
                k++;
            }
            else {
                j++;
                k=0;
            }
        }

        words[j][k-2] = '\0';

        //count stop words
        for (i=0; i<j+1; i++) {
            if (strcmp(words[i],"a")==0 || strcmp(words[i],"an")==0 || strcmp(words[i],"and")==0 || strcmp(words[i],"arc")==0 || strcmp(words[i],"as")==0 ||
            strcmp(words[i],"at")==0 || strcmp(words[i],"be")==0 || strcmp(words[i],"by")==0 || strcmp(words[i],"for")==0 || strcmp(words[i],"from")==0 || strcmp(words[i],"has")==0 ||
            strcmp(words[i],"he")==0 || strcmp(words[i],"in")==0 || strcmp(words[i],"is")==0 || strcmp(words[i],"it")==0 || strcmp(words[i],"its")==0 ||
            strcmp(words[i],"of")==0 || strcmp(words[i],"on")==0 || strcmp(words[i],"that")==0 || strcmp(words[i],"the")==0 || strcmp(words[i],"to")==0 ||
            strcmp(words[i],"was")==0 || strcmp(words[i],"were")==0 || strcmp(words[i],"will")==0 || strcmp(words[i],"with")==0) {
                numStopWords++;
            }
        }
        
        //go to next tweet
        temp=temp->next;
        numTweets++;
    }

    //print output message
    printf("Across %d tweets, %d stop words are found.\n", numTweets, numStopWords);
}