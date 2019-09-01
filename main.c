
/*********************************************************/
/* Forward Declarations */
/*********************************************************/

/* Built-in shell commands */
int bshell_cd(char **args);
int bshell_help(char **args);
int bshell_exit(char **args);

/*********************************************************/
/* Constant Data */
/*********************************************************/

#define BSHELL_RL_BUFSIZE 1024

#define BSHELL_TOK_BUFSIZE 64
#define BSHELL_TOK_DELIM " \t\r\n\a"

/* List of built-in commands */
char *builtin_str[] = {
	"cd",
	"help",
	"exit"
};

/* Their corresponding functions */
int (*builtin_func[]) (char **) = {
	&bshell_cd,
	&bshell_help,
	&bshell_exit
};

/*********************************************************/
/* Utility Functions */
/*********************************************************/

int bshell_num_builtins() {
	return sizeof(builtin_str) / sizeof(char *);
}

/*********************************************************/
/* Built-in function implementations */
/*********************************************************/

int bshell_cd(char **args) {
	if (args[1] == NULL) {
		fprintf(stderr, "bshell : expected argument to \"cd\"\n");
	}
	else {
		if (chdir(args[1]) != 0) {
			perror("bshell - cd");
		}
	}

	return 1;
}

int bshell_help(char **args) {
	int i;
	printf("BSHELL\n");
	printf("Based on Stephen Brennan's LSH\n");
	printf("Type program names and arguments, and hit enter.\n");
	printf("The following are built-in:\n");

	for (i = 0; i < bshell_num_builtins(); b++) {
		printf("  %s\n", builtin_str[i]);
	}

	printf("Use the man command for information on other programs.\n");
	return 1;
}

int bshell_exit(char **args) {
	return 0;
}

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
