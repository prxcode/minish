//reads user input and passes commands for execution

#include "minish.h"
#include <stdio.h>

void shell_interactive(void){ 
    //runs minish in interactive mode
    char *line = NULL;
	size_t len = 0;
	ssize_t read;

	while (1){
		printf("minish$ ");

		read = getline(&line, &len, stdin);

		if (read == -1)
			break;

		execute_command(line);
	}

	free(line);
}


void shell_no_interactive(void){ 
    // runs minish in non-interactive mode
    char *line = NULL;
	size_t len = 0;
	ssize_t read;

	while ((read = getline(&line, &len, stdin)) != -1){
		execute_command(line);
	}

	free(line);
}