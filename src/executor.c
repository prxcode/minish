//parses commands and runs external programs

#include "minish.h"


void execute_command(char *line){ //execute a command entered by the user
	char *args[64];
	char *token;
	int argc = 0;
	pid_t pid;
	int status;

	token = strtok(line, " \n");

	while (token != NULL && argc < 63){
		args[argc] = token;
		argc++;
		token = strtok(NULL, " \n");
	}

	args[argc] = NULL;

	if (argc == 0)
		return;

	if (handle_builtin(args))
		return;

	pid = fork();

	if (pid == -1){
		perror("minish");
		return;
	}

	if (pid == 0){
		execvp(args[0], args);

		perror("minish");
		exit(EXIT_FAILURE);
	}

	waitpid(pid, &status, 0);
}