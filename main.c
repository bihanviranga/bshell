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

#define BSHELL_RL_BUFSIZE 1024
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

#define BSHELL_TOK_BUFSIZE 64
#define BSHELL_TOK_DELIM " \t\r\n\a"
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
