#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

void ascii(char* buffer, int length) {
    unsigned char buf[length];
    int curr;
    
    for (int i=0; i<length; i++) {
        buf[i] = buffer[i];
        curr = buf[i];

        if ((curr>=0 && curr<=9) || (curr>=11 && curr<=31)) {
            printf(" ");
        } else if (curr>=127) {
            printf("?");
        } else {
            printf("%c", buf[i]);
        }
    }
}

void hex(char* buffer, int length) {
    int hexLength = length*2+1;
    int numRows = length/16;
    unsigned char buf[length];

    if (length%16!=0) {
        numRows = numRows + 1;
    }

    char hex[hexLength];
    char rowNum[numRows*7+1];
    int count=0;
    char lastIndex[8];
    
    //get row numbers in hex
    for (int i=0; i<numRows; i++) {
        sprintf(rowNum+i*7, "%07X", i*16);
    }

    //get ascii values in hex
    for (int i=0; i<length; i++) {
        buf[i] = buffer[i];
        sprintf(hex+i*2, "%02X", buf[i]);
    }

    //print values in correct format
    for (int i=0; i<hexLength; i++) {
        if (i%32==0 && count<numRows) {
            for (int j=0; j<7; j++) {
                printf("%c", rowNum[j+(count*7)]);
            }
            
            printf(" ");
            
            count++;
        }

        printf("%c", hex[i]);

        if ((i+1)%2==0) {
            printf(" ");
        }

        if ((i+1)%16==0) {
            printf(" ");
        }

        if ((i+1)%32==0) {
            printf("\n");
        }
    }

    sprintf(lastIndex, "%07X", length);
    printf("\n%s", lastIndex);
}

int main(void) {
    char menuOption[100];
    char displayMode[100];
    char exitChoice[100];
    int check=0;
    char fileName[FILENAME_MAX];
    int fd;
    ssize_t n;
    char *buf;
    int length;
    int numNewLines=0;

    strcpy(menuOption,"a");
    strcpy(displayMode,"a");

    //keep executing progam until user exits
    while (strcmp(menuOption,"x")!=0) {
        //display current mode
        if (strcmp(displayMode,"a")==0) {
            printf("\nCurrent Mode: Ascii\n");
        } else if (strcmp(displayMode,"h")==0) {
            printf("\nCurrent Mode: Hex\n");
        }
        
        //display menu
        printf("Choose a Menu Option:\n");
        printf("1. Enter filename: press 'o'\n");
        printf("2. Select display mode: press 'd'\n");
        printf("3. Exit: press 'x'\n");
        scanf("%s", menuOption);

        if (strcmp(menuOption,"d")==0) {
            //user chooses display mode
            check = 0;

            while (check==0) {
                printf("\nChoose a Display Mode:\n");
                printf("1. Ascii mode: press 'a'\n");
                printf("2. Hex mode: press 'h'\n");
                scanf("%s", displayMode);

                //error checkig
                if (strcmp(displayMode,"a")==0 || strcmp(displayMode,"h")==0) {
                    check = 1;
                } else {
                    printf("Invalid input\n\n");
                }
            }
        } else if (strcmp(menuOption,"o")==0) {
            //get filename
            printf("Enter a filename: ");
            scanf("%s", fileName);

            //open file and check that it opened
            fd = open(fileName, O_RDONLY);

            if (fd < 0){
                printf("Cannot open file %s\n", fileName);
            } else {
                //read file
                length = lseek(fd, 0, SEEK_END);
                buf = malloc(length);
                lseek(fd, 0, SEEK_SET);

                while ((n = read(fd, buf, length)) > 0){
                    if (n < 0){
                        fprintf(stderr, "Error reading file %s\n", fileName);
                    }
                }

                numNewLines=0;

                for (int i=0; i<length; i++) {
                    if (buf[i]==10) {
                        numNewLines++;
                        buf[length-numNewLines] = '\0';
                    }
                }

                length = length-numNewLines;

                //call function for display mode
                if (strcmp(displayMode,"a")==0) {
                    ascii(buf, length);
                } else if (strcmp(displayMode,"h")==0) {
                    hex(buf, length);
                }
                
                //display menu
                check = 0;
                while (check==0) {
                    printf("\nChoose an Option:\n");
                    printf("1. Return to main menu: press 'm'\n");
                    printf("2. Exit: press 'x'\n");
                    scanf("%s", exitChoice);

                    //error checkig
                    if (strcmp(exitChoice,"m")==0) {
                        close(fd);
                        free(buf);
                        check = 1;
                    } else if (strcmp(exitChoice,"x")==0) {
                        close(fd);
                        free(buf);
                        check = 1;
                        strcpy(menuOption,"x");
                    } else {
                        printf("Invalid input\n\n");
                    }
                }
            }
        } else if (strcmp(menuOption,"x")!=0) {
            //error checking
            printf("Invalid input\n\n");
        }
    }

    return 0;
