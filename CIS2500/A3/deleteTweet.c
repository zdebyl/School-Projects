#include "headerA3.h"

void deleteTweet(tweet ** tweetList) {
    //declare variables
    int size=0;
    int tweetToDelete;
    tweet *temp;
    tweet *first;
    tweet *second;
    tweet *here;

    if (*tweetList!=NULL) {
        //get size of list
        temp = *tweetList;

        while (temp!=NULL) {
            size++;
            temp=temp->next;
        }

        printf("Currently there are %d tweets\n", size);

        //get user input
        printf("Which tweet do you wish to delete - enter a value between 1 and %d: ", size);
        scanf("%d", &tweetToDelete);

        //check to ensure tweet is in the size
        if (tweetToDelete <= size && tweetToDelete > 0) {
            //check if its the first element
            if (tweetToDelete == 1) {
                first = *tweetList;
                here = first;
                first = first->next;
                *tweetList = first;
            }
            else {
                //get tweet before one to delete
                first = *tweetList;

                for (int i=0; i<tweetToDelete-2; i++) {
                    first=first->next;
                }

                here = first->next;

                //get tweet after one to delete
                second = *tweetList;

                for (int i=0; i<tweetToDelete; i++) {
                    second=second->next;
                }

                //connect tweets, leaving out the tweet to be deleted
                first->next = second;
            }

            //print tweet that was deleted
            printf("Tweet %d deleted. There are now %d tweets left.\n", here->id, (size-1));
        }
        else {
            printf("Invalid entry.");
        }
    }
    else {
        printf("List is empty - no tweets to delete\n");
    }  
}