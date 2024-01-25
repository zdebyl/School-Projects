#include "headerA3.h"

int main() {
    //declare variables
    int userChoice;
    int match;
    int exit=0;
    tweet *new=NULL;

    //create empty linked list
    tweet *head=NULL;

    //allow user to keep making choices until they choose to exit
    while (exit == 0) {
        //display menu options
        printf("\n1. Create a new tweet\n");
        printf("2. Display tweets\n");
        printf("3. Search a tweet (by keyword)\n");
        printf("4. Find how many words are 'stop words'\n");
        printf("5. Delete the nth tweet\n");
        printf("6. Save tweets to a file\n");
        printf("7. Load tweets from a file\n");
        printf("8. Sort the given linked list on userid\n");
        printf("9. Exit\n");

        //get users choice
        printf("Choose a menu option: ");
        scanf("%d", &userChoice);
        
        //error checking
        while (userChoice < 1 || userChoice > 9) {
            //print error message
            printf("Invalid choice\n");

            //display menu options
            printf("1. Create a new tweet\n");
            printf("2. Display tweets\n");
            printf("3. Search a tweet (by keyword)\n");
            printf("4. Find how many words are 'stop words'\n");
            printf("5. Delete the nth tweet\n");
            printf("6. Save tweets to a file\n");
            printf("7. Load tweets from a file\n");
            printf("8. Sort the given linked list on userid\n");
            printf("9. Exit\n");

            //get users choice
            printf("Choose a menu option: ");
            scanf("%d", &userChoice);
        }

        //call function depending on user choice
        switch (userChoice) {
            case 1:
                new = createTweet(head);
                addNodeToList(&head, new);
                break;

            case 2:                
                displayTweets(head);
                break;

            case 3:
                match = searchTweetsByKeyword(head);
                if (match==0) {
                    //match not found
                }
                else {
                    //match found
                }
                break;

            case 4:
                countStopWords(head);
                break;

            case 5:
                deleteTweet(&head);
                break;

            case 6:
                saveTweetsToFile(head);
                break;

            case 7:
                loadTweetsFromFile(&head);
                break;

            case 8:
                sortID(&head);
                break;

            case 9:
                exit = 1;
                break;
        }
    }
    
    return 0;
}