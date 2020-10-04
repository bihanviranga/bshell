#ifndef __BSHELL_H__
#define __BSHELL_H__

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

/*********************************************************/
/* Forward Declarations */
/*********************************************************/

/* Core functions */
char *bshell_read_line();
char **bshell_split_line(char *line);
void bshell_loop();
int bshell_execute(char **args);
void bshell_initialize();

/*********************************************************/
/* Constant Data */
/*********************************************************/

#define BSHELL_RL_BUFSIZE 1024

#define BSHELL_TOK_BUFSIZE 64
#define BSHELL_TOK_DELIM " \t\r\n\a"

#define BSHELL_SETTINGS_FILE ".bshrc"
#define BSHELL_SETTINGS_DELIM1 " "
#define BSHELL_SETTINGS_DELIM2 "="

extern char bshell_prompt_str[50];

#endif /*__BSHELL_H__ */
