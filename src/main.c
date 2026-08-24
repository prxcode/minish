//starts minish and selects interactive or non-interactive mode

#include "minish.h" 

int main(void)
{
	if (isatty(STDIN_FILENO)){ //checking if this is a terminal
		shell_interactive();
	}
	else{
		shell_no_interactive();
	}

	return (0);
}