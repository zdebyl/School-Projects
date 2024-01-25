#include "headerA3.h"

void saveTweetsToFile(tweet * tweetList) {
    //declare variables
    char filename[200];

    //get user input
    printf("Enter the filename where you would like to store your tweets: ");
    scanf("%s", filename);

    //open file for writing
    FILE *filePointer;
    filePointer = fopen(filename, "w");

    //check to ensure file opened correctly
    if (filePointer == NULL) {
        printf("Error with file\n");
    }
    //save tweets to file
    else {
        tweet *temp = tweetList;

        while (temp!=NULL) {
            fprintf(filePointer, "%d", temp->id);
            fprintf(filePointer, ",");
            fprintf(filePointer, "%s", temp->user);
            fprintf(filePointer, ",");
            fprintf(filePointer, "%s", temp->text);
            temp=temp->next;
        }

        //print message
        printf("Output successful!\n");

        //close file
        fclose(filePointer);
    }
}
