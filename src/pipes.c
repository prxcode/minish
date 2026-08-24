// connects multiple cmds using Unix pipes for inter process communication

#include "minish.h"


void execute_pipeline(char *line){ //execute commands connected by pipes
	char *commands[64];
	char *command;
	char *token;
	char *args[64];
	int pipefd[2];
	int prev_fd = -1;
	int command_count = 0;
	int argc;
	int i;
	pid_t pid;
	pid_t pids[64];
	int status;

	command = strtok(line, "|");

	while (command != NULL && command_count < 64){
		commands[command_count] = command;
		command_count++;
		command = strtok(NULL, "|");
	}

	if (command_count < 2)
		return;

	for (i = 0; i < command_count; i++){
		argc = 0;

		token = strtok(commands[i], " \n");

		while (token != NULL && argc < 63){
			args[argc] = token;
			argc++;
			token = strtok(NULL, " \n");
		}

		args[argc] = NULL;

		if (argc == 0)
			continue;

		if (i < command_count - 1){
			if (pipe(pipefd) == -1){
				perror("minish: pipe");
				return;
			}
		}

		pid = fork();

		if (pid == -1){
			perror("minish: fork");
			return;
		}

		if (pid == 0){
			if (prev_fd != -1){
				if (dup2(prev_fd, STDIN_FILENO) == -1){
					perror("minish: dup2");
					exit(EXIT_FAILURE);
				}

				close(prev_fd);
			}

			if (i < command_count - 1){
				if (dup2(pipefd[1], STDOUT_FILENO) == -1){
					perror("minish: dup2");
					exit(EXIT_FAILURE);
				}

				close(pipefd[0]);
				close(pipefd[1]);
			}

			execvp(args[0], args);

			perror("minish");
			exit(EXIT_FAILURE);
		}

		pids[i] = pid;

		if (prev_fd != -1)
			close(prev_fd);

		if (i < command_count - 1){
			close(pipefd[1]);
			prev_fd = pipefd[0];
		}
	}

	if (prev_fd != -1)
		close(prev_fd);

	for (i = 0; i < command_count; i++)
		waitpid(pids[i], &status, 0);
}