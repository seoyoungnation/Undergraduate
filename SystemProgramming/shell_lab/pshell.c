#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<sys/wait.h>
#include<sys/types.h>
#include<unistd.h>
#include<errno.h>

pid_t Fork(void);
void unix_error(char*);
int exe(char* argv[]);

int main(int argc, char* argv[]){
	printf("processing..\n");

	pid_t pid;
	int status;

	pid = Fork();

	if (pid == 0){
		exe(argv);
	}
	else {
		wait(NULL);
	}
	printf("completed\n");
}

int exe(char* argv[]){
	execvp(argv[1], argv+1);
	unix_error("execve error:");
	exit(1);
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
