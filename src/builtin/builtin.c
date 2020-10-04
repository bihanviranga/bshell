#include "bshell_builtin.h"

/* Definition of the extern variables */

const char *builtin_str[] = {"cd", "help", "exit", "reconfigure"};

int (*const builtin_func[])(char **) = {&bshell_cd, &bshell_help, &bshell_exit,&bshell_reconfigure};

/*********************************************************/
/* Utility Functions */
/*********************************************************/

int bshell_num_builtins() {
  return sizeof(builtin_str) / sizeof(char *);
}
