#include <stdio.h>// for printf(), fgets(), perror()
#include <stdlib.h>// for exit()
#include <string.h>// for strtok(), strcmp()
#include <unistd.h>// for fork(), execvp()
#include <sys/wait.h>// for wait()
#define B_SIZE 2048
#define MAX_WORDS  128

int main(void)
{
    char buffer[B_SIZE];
    char *args[MAX_WORDS];
    char currentDirectory[B_SIZE];

    while (1)
    {   
        printf("mash_shell:%s$", getcwd(currentDirectory, sizeof(currentDirectory)));
        fflush(stdout);
        if (fgets(buffer, B_SIZE, stdin) == NULL)
        {
            perror("Error with fgets");
        }

        char *token;
        int i = 0;
        token = strtok(buffer, " \t\n\r");

        if (strcmp(token, "exit") == 0){
            exit(0);
        }

        if (strcmp(token, "cd") == 0) {
            token = strtok(NULL, " \t\n\r");
            if (chdir(token) == -1) {
                perror("no_dir");
            }
            continue;
        }
        

        while (token != NULL) {
            args[i] = strdup(token);
            if (args[i] == NULL) {
                perror("Error duplicating string");
            }
            token = strtok(NULL, " \t\n\r");
            i++;
        }
        args[i] = NULL;

        pid_t pid = fork();

        if (pid == -1) {
            perror("Fork");
        }

        if (pid == 0) {
            execvp(args[0], args);
            perror("execvp");
            exit(1);
        }
        wait(NULL);
    }
    for (int i = 0; args[i] != NULL; i++) {
        free(args[i]);
    }
}