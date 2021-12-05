#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>
#include<errno.h>
#include<string.h>
#include<stdlib.h>
#include<sys/wait.h>
#include<readline/readline.h>


int main(int argc, char* argv[])
{
    pid_t pid;
    int status;

    char* cmdline;
    char* opt;


    while(1) {
        cmdline = readline("$ ");
        printf("%s\n", cmdline);

        opt = strtok(cmdline, " \n");   
        if(!strcmp(opt, "quit"))
            break;
    } 



    return 0;
}

