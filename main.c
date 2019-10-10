/*********************************************************/
/* Includes */
/*********************************************************/

#include <sys/wait.h>
// waitpid() and associated macros
#include <unistd.h>
// chdir, fork, exec, pid_t
#include <stdlib.h>
// malloc, realloc, free, exit, execvp, EXIT_SUCCESS, EXIT_FAILURE
#include <stdio.h>
// fprintf, printf, stderr, getchar, perror
#include <string.h>
// strcmp, strtok
#include "builtins.h"

/*********************************************************/
/* Forward Declarations */
/*********************************************************/

/* Core functions */
char *bshell_read_line();
char **bshell_split_line(char *line);
void bshell_loop();
int bshell_execute(char **args);

/*********************************************************/
/* Constant Data */
/*********************************************************/

#define BSHELL_RL_BUFSIZE 1024

#define BSHELL_TOK_BUFSIZE 64
#define BSHELL_TOK_DELIM " \t\r\n\a"

/*********************************************************/
/* Core functions */
/*********************************************************/

int main(int argc, char **argv) {
	// Load config files, if any

	// Run command loop
	bshell_loop();

	// Perform any shutdown/cleanup

	return EXIT_SUCCESS;
}

void bshell_loop() {
	char *line;
	char **args;
	int status;

	do {
		printf("> ");
		line = bshell_read_line();
		args = bshell_split_line(line);
		status = bshell_execute(args);

		free(line);
		free(args);
	} while (status);
}

char *bshell_read_line() {
	int bufsize = BSHELL_RL_BUFSIZE;
	int position = 0;
	char *buffer = malloc(sizeof(char) * bufsize);
	int c;
	// The characters are stored in an integer c, 
	// because otherwise checking for EOF won't work.
	// EOF is an integer.

	if (!buffer) {
		// TODO: Move the error to a different function
		fprintf(stderr, "bshell: allocation error\n");
		exit(EXIT_FAILURE);
	}

	while (1) {
		// Read a character
		c = getchar();

		// If we hit EOF, replace it with a null character and return
		// Iterate through buffer and assign characters as they come from
		// getchar.
		// When the line ends, put a \0 there to denote end.
		if (c == EOF || c == '\n') {
			buffer[position] = '\0';
			return buffer;
		} 
		else {
			buffer[position] = c;
		}
		position++;

		// If we have exceeded the buffer, reallocate.
		if (position >= bufsize) {
			bufsize += BSHELL_RL_BUFSIZE;
			buffer = realloc(buffer, bufsize);
			if (!buffer) {
				fprintf(stderr, "bshell: allocation error\n");
				// TODO: Move the error to a different function
				exit(EXIT_FAILURE);
			}

		}

	}
}


char **bshell_split_line(char *line) {
	int bufsize = BSHELL_TOK_BUFSIZE, position = 0;
	char **tokens = malloc(bufsize * sizeof(char*));
	char *token;

	if (!tokens) {
		// TODO : move the error 
		fprintf(stderr, "bshell: allocation error\n");
		exit(EXIT_FAILURE);
	}

	token = strtok(line, BSHELL_TOK_DELIM);
	while (token != NULL) {
		tokens[position] = token;
		position++;

		if (position >= bufsize) {
			bufsize += BSHELL_TOK_BUFSIZE;
			tokens = realloc(tokens, bufsize * sizeof(char*));
			if (!tokens) {
				// TODO: move the error
				fprintf(stderr, "bshell: allocation error\n");
				exit(EXIT_FAILURE);
			}
		}

		token = strtok(NULL, BSHELL_TOK_DELIM);
		// NULL means strtok uses the previously supplied line
	}
	tokens[position] = NULL;
	return tokens;
}

int bshell_launch(char **args) {
	pid_t pid, wpid;
	int status;

	pid = fork();
	if (pid == 0) {
		// This is the child
		if (execvp(args[0], args) == -1) {
			// This variant of exec expects a program name
			// and an array (vector, which the v stands for)
			// here the first argument has to be the program name.
			// The p means it needs the program name only, not the
			// full path. It will look for the program p in system PATH.
			perror("bshell - execve");
			// perror prints system error messages
			// about the last encountered error.
		}
		exit(EXIT_FAILURE);
	}
	else if (pid < 0) {
		// error in forking. PID = -1 
		perror("bshell - fork");
	}
	else {
		// parent process
		// This waits until the child is either killed 
		// or it exits.
		do {
			wpid = waitpid(pid, &status, WUNTRACED);
		} while (!WIFEXITED(status) && !WIFSIGNALED(status));
	}

	return 1;
}

int bshell_execute(char **args) {
	int i;

	if (args[0] == NULL) {
		// an empty command was entered
		return 1;
	}

	// check if the command is a built-in
	for (i = 0; i < bshell_num_builtins(); i++) {
		if (strcmp(args[0], builtin_str[i]) == 0) {
			return (*builtin_func[i])(args);
		}
	}

	return bshell_launch(args);
}