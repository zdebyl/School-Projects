#include "headerA3.h"

void displayTweets(tweet * tweetList) {
    //declare and set temporary pointer to move through list
    tweet *temp = tweetList;

    //print list
    while (temp!=NULL) {
        printf("%d: Created by %s: %s", temp->id, temp->user, temp->text);
        temp=temp->next;
    }
}