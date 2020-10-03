#include "bshell.h"
#include "bshell_builtin.h"

int bshell_help(char **args) {
  int i;
  printf("BSHELL\n");
  printf("Based on Stephen Brennan's LSH\n");
  printf("Type program names and arguments, and hit enter.\n");
  printf("The following are built-in:\n");

  for (i = 0; i < bshell_num_builtins(); i++) {
    printf("  %s\n", builtin_str[i]);
  }

  printf("Use the man command for information on other programs.\n");
  return 1;
}
