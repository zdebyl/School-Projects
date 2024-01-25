#include "headerA3.h"

void addNodeToList(tweet**tweetList,tweet * node) {
    //declare variables
    tweet *temp=NULL;

    //check if list is empty
    if (*tweetList == NULL) {
        //set head
        *tweetList = node;
    }
    else {
        temp = *tweetList;

        //get to the end of the list
        while (temp->next != NULL) {
            temp = temp->next;
        }

        temp->next = node;
    }
}