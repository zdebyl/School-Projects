#include "headerA3.h"

void sortID (tweet ** head) {
    //declare variables
    int tempID;
    int size=0;
    tweet* ptr = *head;
    tweet* tempPtr;

    //get size of list
    while (ptr!=NULL) {
        size++;
        ptr=ptr->next;
    }

    //go through list the number of times there
    for (int i=0; i<size-1; i++) {
        ptr = *head;

        for (int j=0; j<size-i-1; j++) {
            tempPtr = ptr;
            ptr = ptr->next;

            if (tempPtr->id > ptr->id) {
                tempID = tempPtr->id;
                tempPtr->id = ptr->id;
                ptr->id = tempID;
            }
        }
    }
}