// handles signals received by minish

#include "minish.h"

static void handle_sigint(int signum){ // handle Ctrl-C
	(void)signum;
	write(STDOUT_FILENO, "\nminish$ ", 9);
}


void setup_signals(void){ //configure signals for the shell
	struct sigaction sa;

	memset(&sa, 0, sizeof(sa));

	sa.sa_handler = handle_sigint;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART;

	sigaction(SIGINT, &sa, NULL);

	sa.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &sa, NULL);
}