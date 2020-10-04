#ifndef __BSHELL_BUILTIN_H__
#define __BSHELL_BUILTIN_H__

/*********************************************************/
/* Forward Declarations */
/*********************************************************/

/* Built-in shell commands */
int bshell_num_builtins();
int bshell_cd(char **args);
int bshell_help(char **args);
int bshell_exit(char **args);
int bshell_reconfigure();

/* Definition of the list of built-in commands */
extern const char *builtin_str[];

/* Definition of the corresponding function pointer array */
extern int (*const builtin_func[])(char **);

#endif /* __BSHELL_BUILTIN_H__ */
