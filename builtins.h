#ifndef _BSHELL_BUILTINS_H
#define _BSHELL_BUILTINS_H

/*********************************************************/
/* Constant Data */
/*********************************************************/

#define BUILTIN_NUM 3

/* List of built-in commands */
char *builtin_str[BUILTIN_NUM];

/* Their corresponding functions */
int (*builtin_func[BUILTIN_NUM]) (char **);


/*********************************************************/
/* Forward Declarations */
/*********************************************************/

int bshell_num_builtins();

/* Built-in shell commands */
int bshell_cd(char **args);
int bshell_help(char **args);
int bshell_exit(char **args);

#endif