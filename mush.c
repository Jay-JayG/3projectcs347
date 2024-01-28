#include <stdio.h>// for printf(), fgets(), perror()
#include <stdlib.h>// for exit()
#include <string.h>// for strtok(), strcmp()
#include <unistd.h>// for fork(), execvp()
#include <sys/wait.h>// for wait()
#define B_SIZE 2048

int main(void)
{
    char buffer[B_SIZE];
    while (1)
    {
        if (fgets(buffer, B_SIZE, stdin) == NULL)
        {
            perror("Error with fgets");
        } else {
            printf("%s", buffer);
        }
    }

}