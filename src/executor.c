//parses commands and runs external programs

#include "minish.h"


void execute_command(char *line){ //execute a command entered by the user
	char *args[64];
	char *token;
	char *input_file = NULL;
	char *output_file = NULL;
	char *append_file = NULL;
	int argc = 0;
	int fd;
	pid_t pid;
	int status;

	token = strtok(line, " \n");

	while (token != NULL && argc < 63){
		if (strcmp(token,"<")==0){
			token = strtok(NULL, " \n");
			
			if (token == NULL){
				fprintf(stderr, "minish: missing input file\n");
				return;
			}

			input_file = token;
		}

		else if (strcmp(token, ">") == 0){
			token = strtok(NULL, " \n");

			if (token == NULL){
				fprintf(stderr, "minish: missing output file\n");
				return;
			}

			output_file = token;
		}
		
		else if (strcmp(token, ">>") == 0){
			token = strtok(NULL, " \n");

			if (token == NULL){
				fprintf(stderr, "minish: missing output file\n");
				return;
			}

			append_file = token;
		}

		else{
			args[argc] = token;
			argc++;
		}
		
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
		if (input_file != NULL){
			fd = open(input_file, O_RDONLY);

			if (fd == -1){
				perror("minish");
				exit(EXIT_FAILURE);
			}

			if (dup2(fd, STDIN_FILENO) == -1){
				perror("minish: dup2");
				close(fd);
				exit(EXIT_FAILURE);
			}

			close(fd);
		}

		if (output_file != NULL){
			fd = open(output_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);

			if (fd == -1){
				perror("minish");
				exit(EXIT_FAILURE);
			}

			if (dup2(fd, STDOUT_FILENO) == -1){
				perror("minish: dup2");
				close(fd);
				exit(EXIT_FAILURE);
			}

			close(fd);
		}

		if (append_file != NULL){
			fd = open(append_file, O_WRONLY | O_CREAT | O_APPEND, 0644);

			if (fd == -1){
				perror("minish");
				exit(EXIT_FAILURE);
			}

			if (dup2(fd, STDOUT_FILENO) == -1){
				perror("minish: dup2");
				close(fd);
				exit(EXIT_FAILURE);
			}

			close(fd);
		}

		execvp(args[0], args);

		perror("minish");
		exit(EXIT_FAILURE);
	}

	waitpid(pid, &status, 0);
}