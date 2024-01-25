#define _POSIX_C_SOURCE 200809L
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <limits.h>
#include <fcntl.h>

int fd[100][2];
int terminatedChildren=0;
int raceCondition=0;

void signalhandler() {
    int child_status;
    pid_t child_pid;
    int read_histogram[26];
    char filename[50];
    int file;
    char str_pid[10];
    char str_count[30000];
    char histogram_char[2];
    int pipe;
    char* towrite;

    //reinstall signal handler
    signal(SIGCHLD, signalhandler);

    //get process id and status of termination
    if (raceCondition==0) {
        child_pid = waitpid(-1, &child_status, WNOHANG);
    } else {
        child_pid = wait(&child_status);
    }

    //terminated normally
    if (WIFEXITED(child_status)) {
        printf("Caught SIGCHILD with pid %d. It exited with status %d\n", child_pid, WEXITSTATUS(child_status));
    }
    //terminated abnormally by a signal
    else if (WIFSIGNALED(child_status)) {
        char* exitSignalStr = strsignal(WTERMSIG(child_status));
        printf("Caught SIGCHILD with pid %d. It exited with status %d (%s)\n", child_pid, WTERMSIG(child_status), exitSignalStr);
    }

    //child exited normally
    if (WIFEXITED(child_status) && WEXITSTATUS(child_status)==0) {
        //get which pipe to read from
        close(fd[0][1]);                
        read(fd[0][0], &pipe, sizeof(pipe));
        
        //parent closes write side of pipe
        close(fd[pipe][1]);                

        //read from child
        read(fd[pipe][0], read_histogram, sizeof(read_histogram));
    
        if (raceCondition==0) {
            sleep(2);
        }
        
        //close read side of pipe
        close(fd[pipe][0]);

        //write to file
        sprintf(str_pid, "%d", child_pid);
        strcpy(filename,"\0");
        strcpy(filename, "file");
        strcat(filename, str_pid);
        strcat(filename, ".hist");

        file = open(filename, O_WRONLY | O_CREAT, 0644);

        if (file < 0){
            perror("opening file");
        } else {
            towrite = malloc(sizeof(char)*312);
            strcpy(towrite,"\0");

            for (int j=0; j<26; j++) {
                sprintf(str_count, "%d", read_histogram[j]);
                sprintf(histogram_char, "%c", j+97);
                strcat(towrite, histogram_char);
                strcat(towrite, " ");
                strcat(towrite, str_count);
                strcat(towrite, "\n");
            }

            write(file, towrite, strlen(towrite));

            free(towrite);
        }

        //close file
        close(file);
    }

    //update number of terminated children
    terminatedChildren++;
}

int main(int argc, char* argv[]) {
    pid_t child_pid[argc-1];
    int numChildren=0;
    int firstChild=0;

    //register signal handler
    signal(SIGCHLD, signalhandler);

    //check for race condition
    if (strcmp(argv[1],"-R")==0) {
        raceCondition = 1;
        numChildren = argc - 2;
        firstChild = 2;
    } else {
        raceCondition = 0;
        numChildren = argc - 1;
        firstChild = 1;
    }

    //create pipes
    for (int i=0; i<numChildren+1; i++) {
        if(pipe(fd[i]) == -1) {
            perror("pipe");
        }
    }

    //no files given
    if (numChildren<1) {
        perror("no files given");
    } else {
        for (int i=0; i<numChildren; i++) {
            child_pid[i] = fork();

            if ((strcmp(argv[i+firstChild], "SIG"))==0) {
                kill(child_pid[i], SIGINT);
                if (raceCondition==0) {
                    sleep(10+(2^i));
                }
            }

            //child
            if (child_pid[i] == 0){
                int file, length;
                int histogram[26];
                char* buf="\0";
                ssize_t n;
                int pipe=0;
                
                if (raceCondition==0) {
                    sleep(2);
                }
                
                //close read side of pipe
                close(fd[0][0]);
                close(fd[i+1][0]);

                //open file
                file = open(argv[i+firstChild], O_RDONLY);

                //file failed to open
                if (file < 0){
                    perror("opening file");

                    //close write side of pipe and exit
                    close(fd[i+1][1]);

                    if (raceCondition==0) {
                        sleep(10+(2^i));
                    }
                    
                    exit(1);
                } else {
                    //read file
                    length = lseek(file, 0, SEEK_END);
                    buf = malloc(length);
                    lseek(file, 0, SEEK_SET);

                    while ((n = read(file, buf, length)) > 0){
                        if (n < 0){
                            perror("reading file");
                        }
                    }

                    //set histogram values to 0
                    for (int j=0; j<26; j++) {
                        histogram[j] = 0;
                    }

                    //get histogram values
                    for (int j=0; j<length; j++) {
                        if (buf[j]>64 && buf[j]<91) {
                            histogram[buf[j]-65]++;
                        } else if (buf[j]>96 && buf[j]<123) {
                            histogram[buf[j]-97]++;
                        }
                    }

                    if (raceCondition==0) {
                        sleep(10+(2^i));
                    }                    

                    //write to parent
                    pipe = i+1;
                    write(fd[0][1], &pipe, (sizeof(pipe)));
                    write(fd[i+1][1], histogram, (sizeof(int)*26));

                    //close write side of pipe
                    close(fd[i+1][1]);

                    //close and exit
                    close(file);
                    free(buf);
                    exit(0);
                }
            }
            //error
            else if (child_pid[i]<0){
                perror("fork");
                exit(1);
            }
        }

        //wait for all children to terminate
        while(terminatedChildren<numChildren) {
            pause();
        }

        //close pipe
        close(fd[0][0]);
        close(fd[0][1]);
    }

    return 1;
}
