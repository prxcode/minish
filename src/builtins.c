//implements commands handled directly by minish

#include "minish.h"

int builtin_cd(char **args){ //to change the current working directory
	if (args[1] == NULL){
		fprintf(stderr, "minish: cd: missing argument\n");
		return (1);
	}

	if (chdir(args[1]) == -1){
		perror("minish: cd");
		return (1);
	}

	return (0);
}


int builtin_env(void){ // print environment variables
	extern char **environ;
	int i = 0;

	while (environ[i] != NULL){
		printf("%s\n", environ[i]);
		i++;
	}

	return (0);
}


int handle_builtin(char **args){ //to check and execute shell builtins
	if (args[0] == NULL)
		return (1);

	if (strcmp(args[0], "exit") == 0){
		exit(0);
	}

	if (strcmp(args[0], "cd") == 0){
		builtin_cd(args);
		return (1);
	}

	if (strcmp(args[0], "env") == 0){
		builtin_env();
		return (1);
	}

	return (0);
}