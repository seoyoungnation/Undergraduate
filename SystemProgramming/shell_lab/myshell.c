#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<sys/wait.h>
#include<sys/types.h>
#include<unistd.h>
#include<errno.h>
#include<string.h>
#include<readline/readline.h>

void eval(char*);
int builtin_command(char**);
pid_t Fork(void);
void unix_error(char*);
int exe(char* argv[]);
int parseline(char*, char**);

int main(){
	pid_t pid;
	int status;

	char* cmdline;
	char* opt;

	while(1){
		cmdline = readline("$ ");
		printf("%s\n", cmdline);

		opt = strtok(cmdline, " \n");
		if (!strcmp(opt, "quit"))
			break;
		
		int i = 0;
		while(token != NULL){
			argv[i] = opt;
			opt = strtok(NULL, " ");
			i++;
		}

		eval(cmdline);

	}
}

int exe(char* argv[]){
	execvp(argv[0], argv);
	printf("execve error: %s\n", strerror(errno));
	exit(1);
}

void eval(char *cmdline){
	int bg;
	pid_t pid;
	char *argv[100];

	bg = parseline(cmdline, argv);

	if (argv[0] == NULL)
		return;

	if (!builtin_command(argv)){
		if ((pid = Fork()) == 0){
			if (execvp(argv[0], argv) < 0){
				printf("execve error\n");
				exit(0);
			}
		
			if (!bg){
				int status;
				if (waitpid(pid, &status, 0) < 0)
					unix_error("waitfg: waitpid error\n");
			}
			else
				printf("%d %s", pid, cmdline);
		}
	}
	return;
}

int parseline(char *buf, char** argv){
	char *delim;
	int argc;
	int bg;

	buf[strlen(buf)-1] = ' ';
	while (*buf && (*buf == ' '))
		buf++;

	argc = 0;
	while ((delim = strchr(buf, ' '))){
		argv[argc++] = buf;
		*delim = '\0';
		buf = delim +1;
		while (*buf && (*buf == ' '))
			buf++;
	}

	if (argc == 0)
		return 1;

	if ((bg = (*argv[argc-1] == '&')) != 0)
		argv[--argc] = NULL;

	return bg;
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
