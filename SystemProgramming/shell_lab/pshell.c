#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<sys/wait.h>
#include<sys/types.h>
#include<unistd.h>
#include<errno.h>

void eval(char*argv[]);
int builtin_command(char**);
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
	printf("execve error: %s\n", strerror(errno));
	exit(1);
}

void eval(char *argv[]){
	int bg;
	pid_t pid;

	if (argv[0] == NULL)
		return;
	if (!builtin_command(argv)){
		if ((pid = Fork()) == 0){
			if (execve(argv[1], argv, __environ) < 0){
				printf("execve error\n");
				exit(0);
			}

			if (!bg){
				int status;
				if (waitpid(pid, &status, 0) < 0)
					unix_error("waitfg: waitpid error\n");
			}
		}
	}
	return;
}

int builtin_command(char **argv){
	if (!strcmp(argv[0], "quit"))
		exit(0);
	if (!strcmp(argv[0], "&"))
		return 1;
	return 0;
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
