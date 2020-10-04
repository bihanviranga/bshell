#include "bshell.h"

int bshell_cd(char **args) {
  if (args[1] == NULL) {
    fprintf(stderr, "bshell : expected argument to \"cd\"\n");
  } else {
    if (chdir(args[1]) != 0) {
      perror("bshell - cd");
    }
  }

  return 1;
}
