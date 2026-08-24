// parses command arguments and expands variables

#include "minish.h"

char *expand_variable(char *token){ //expand an environment variable
	char *value;
	char *result;
	char *start;
	size_t prefix_len;
	size_t value_len;
	size_t suffix_len;

	if (token[0] != '$')
		return (token);

	if (strcmp(token, "$?") == 0){
		return (token);
	}

	start = token + 1;

	if (*start == '\0')
		return (token);

	value = getenv(start);

	if (value == NULL)
		return ("");

	prefix_len = 0;
	value_len = strlen(value);
	suffix_len = 0;

	result = malloc(prefix_len + value_len + suffix_len + 1);

	if (result == NULL){
		perror("minish: malloc");
		return (token);
	}

	memcpy(result, value, value_len);
	result[value_len] = '\0';

	return (result);
}


int parse_command(char *line, char **args){ //parse a command into arguments
	char *p = line;
	char *start;
	char quote;
	int argc = 0;
	char *expanded;

	while (*p != '\0' && argc < MAX_ARGS - 1){
		while (*p == ' ' || *p == '\t' || *p == '\n')
			p++;

		if (*p == '\0')
			break;

		start = p;
		quote = '\0';

		while (*p != '\0'){
			if (quote == '\0' && (*p == '\'' || *p == '"')){
				quote = *p;

				memmove(p, p + 1, strlen(p));
				continue;
			}

			if (quote != '\0' && *p == quote){
				quote = '\0';

				memmove(p, p + 1, strlen(p));
				continue;
			}

			if (quote == '\0' &&
				(*p == ' ' || *p == '\t' || *p == '\n'))
				break;

			p++;
		}

		if (quote != '\0'){
			fprintf(stderr, "minish: unmatched quote\n");
			return (-1);
		}

		if (*p != '\0'){
			*p = '\0';
			p++;
		}

		expanded = expand_variable(start);

		if (expanded != start)
			args[argc] = expanded;
		else
			args[argc] = start;

		argc++;
	}

	args[argc] = NULL;

	return (argc);
}