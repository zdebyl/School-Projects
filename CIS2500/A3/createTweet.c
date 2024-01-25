#include "headerA3.h"

tweet * createTweet( tweet * tweetList){
    //declare variables
    tweet *new=NULL;
    tweet *temp=NULL;
    char userName[51];
    char userTweet[141];
    int userID=0;

    //get user input
    printf("Enter a username: ");
    scanf("%s", userName);

    while (strlen(userName) > 51) {
        printf("Invalid. Please try again\n");
        printf("Enter a username: ");
        scanf("%s", userName);
    }

    printf("Enter the user's tweet: ");
    getchar();
    fgets(userTweet, 141, stdin);

    while (strlen(userTweet) > 141) {
        printf("Invalid. Please try again\n");
        printf("Enter the user's tweet: ");
        getchar();
        fgets(userTweet, 141, stdin);
    }

    //calculate user ID
    userID = strlen(userTweet)-1;

    for (int i=0; i<strlen(userName); i++) {
        userID = userID + userName[i];
    }

    //make user ID unique
    temp = tweetList;

    while (temp!=NULL) {
        if (userID == temp->id) {
            userID = userID + (rand() % 1000);
            temp = tweetList;
        }

        temp=temp->next;
    }

    //print user ID
    printf("\nYour computer-generated userid is: %d\n", userID);

    //create node
    new = malloc(sizeof(tweet));
    new->id = userID;
    strcpy(new->user, userName);
    strcpy(new->text, userTweet);
    new->next = NULL;
    
    //return node
    return new;
}