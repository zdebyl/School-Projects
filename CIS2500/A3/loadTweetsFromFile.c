#include "headerA3.h"

void loadTweetsFromFile(tweet ** tweetList) {
    //declare variables
    char filename[200];
    char tempLine[200];
    char *line = malloc(sizeof(char)*200);
    char *word = malloc(sizeof(char)*200);
    int ID;
    char username[51];
    char tweetText[141];
    tweet *temp;

    //get user input
    printf("Enter a filename to load from: ");
    scanf("%s", filename);

    //open file for reading
    FILE *filePointer;
    filePointer = fopen(filename, "r");

    //check to ensure file opened correctly
    if (filePointer == NULL) {
        printf("Error with file\n");
    }
    //load tweets from file
    else {
        //go through the whole file
        while (!feof(filePointer)) {
            temp = calloc(1, sizeof(tweet));
            
            //read line from file
            fgets(tempLine, 200, filePointer);
            strcpy(line, tempLine);

            //get id
            word = strtok(line, ",");
            ID = atoi(word);
            temp->id = ID;

            //get username
            word = strtok(NULL, ",");
            strcpy(username, word);
            strcpy(temp->user, username);

            //get tweet
            word = strtok(NULL, "\n");
            strcpy(tweetText, word);
            strcpy(temp->text, tweetText);

            //delete comma
            int i=0;
            while (tweetText[strlen(tweetText)-i] != ',') {
                i++;
            }
            
            tweetText[strlen(tweetText)-i] = '\n';
            strcpy(temp->text, tweetText);
            
            //add node to list
            addNodeToList(tweetList, temp);
        }

        //print message
        printf("Output successful!\n");

        //close file
        fclose(filePointer);
    }
}