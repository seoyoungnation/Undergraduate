#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<sys/wait.h>
#include<sys/types.h>
#include<unistd.h>
#include<errno.h>
#include<string.h>
#include<readline/readline.h>

pid_t Fork(void);
void unix_error(char*);
int exe(char* argv[]);

int main(){
	pid_t pid;
	int status;

	char* cmdline;
	char* opt;
	char* argv[100];

	while(1){
		cmdline = readline("$ ");

		opt = strtok(cmdline, " ");
		if (!strcmp(opt, "quit"))
			break;
		
		int i = 0;
		
		while(opt != NULL){
			argv[i] = opt;
			opt = strtok(NULL, " ");
			i++;
		}
		argv[i] = NULL;

		pid = Fork();

		if (pid == 0){
			exe(argv);
		}
		else {
			wait(NULL);
		}
	}
}

int exe(char* argv[]){
	execvp(argv[0], argv);
	unix_error("execvp error:");
}

pid_t Fork(){
	pid_t pid;
	
	if((pid = fork()) < 0){
		unix_error("Fork error");
	}
	return pid;
}

void unix_error(char *msg){
	printf("%s: %s\n", msg, strerror(errno));
	exit(0);
}
