Student Name: Zoe Debyl 
Student ID: zdebyl
Assignment 3: Dynamic data structures (linked lists); Tweet Manager
Course: CIS*2500
Due Date: April 3, 2022 
Date of last revision: April 1, 2022

I have exclusive control over this submission via my password. 
By including this header comment, I certify that: 
1) I have read and understood the policy on academic integrity. 
2) I have completed Moodle's module on academic integrity. 
3) I have achieved at least 80% on the academic integrity quiz 
I assert that this work is my own. I have appropriate acknowledged 
any and all material that I have used, be it directly quoted or 
paraphrased. Furthermore, I certify that this assignment was written 
by me in its entirety. 

To compile and run:
make
./debylZoeA3

Components Explanation:

Function 1 - createTweet
    This function gets the user input for the username and tweet text, then calculates the ID by adding the ascii value of all the characters
    in the username to the length of the tweet. Then, it ensures that the ID is unique by comparing it to all other IDS and adding random
    numbers to it until it is unique. Then, it creates a node with this information and returns it.
Function 2 - displayTweets
    This function creates a temporary node to traverse the list and as it does, it prints each node in the list.
Function 3 - searchTweetsByKeyword
    This function gets user input of what keyword to search for. Then, it creates another variable with the same word but different
    capitalization, so the search is case-insensitive. Then, it creates a temporary node to traverse the list and checks if the keyword
    is in each tweet as it does. If it is, then it prints a message. The function returns 1 if the keyword is found and 0 if it is not.
Function 4 - countStopWords
    This function creates a temporary node to traverse the list and as it does, it splits up every tweet into its words and stores them in
    an array. After splitting up the tweet, it checks if it contains any stop words by comparing each word to each stop word. Once its done,
    it prints a message with the number of tweets and number of stop words found.
Function 5 - deleteTweet
    This function first checks to ensure that the list isn't empty, and if it is, it prints a message saying that there is nothing to delete
    and returns. If the function isn't empty, then it gets the size of the list and outputs to the user how many tweets it has and gets their
    input for which tweet to delete. First, it checks if that is the first tweet, and changes the head of the list if it is. If its not the
    first tweet, then it traverses the list to find the tweet before and after it, then connects these.
Function 6 - saveTweetsToFile
    This function gets the user input for the name of the file to save to, then it opens this file for writing. It checks to ensure the file
    was opened correctly, and if it wasn't, then it prints an error message and returns. If it does open correctly, then it creates a
    temporary node to traverse the list, and prints the nodes onto the file as it does.
Function 7 - loadTweetsFromFile
    This function gets the user input for the name of the file to read from, then it opens this file for reading. It checks to ensure the file
    was opened correctly, and if it wasn't, then it prints an error message and returns. If it does open correctly, then it creates a
    temporary node to traverse the list, and is it does it reads the tweet. With the tweet, it gets everything before the first comma, which
    is the ID, then everything before the second comma, which is the username, then everything before the next line, which is the tweet. It
    then deletes the comma at the end of the tweet. Lastly, it calls the function addNodeToList, to add the node with all the information
    found, to the list.
Function 8 - sortID
    This function uses the bubble sort algorithm to sort the tweets.
Function 9 - addNodeToList
    This function checks if the list is empty, and if it is assigns the input node to the head. If it is not, it creates a temporary node to
    get traverse the list until it gets to the end. Once at the end, it adds the input node to the list.

Limitations:
One limitation is that countStopWords doesn't work on large number of tweets.

Future Improvements:
A future improvement that I could make is to use a more efficient sorting method than Bubble sort.