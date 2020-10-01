# BSHELL - C shell for Linux

This code was based on the very helpful tutorial found [here](https://brennan.io/2015/01/16/write-a-shell-in-c/).

### Configuration

Supports reading config from a `.bshrc` file located in the same directory as executable (for now).
Currently only 1 setting is supported.

Config is set in a `NAME key=value` format. For some config names, any name can be used for key since only value is read.

PROMPT : Set the shell's prompt by specifying `PROMPT value=user@pc $ ` in the config file.

### Further reading:
[fork vs exec](https://www.geeksforgeeks.org/difference-fork-exec/)

[execv vs execvp](https://www.unix.com/unix-for-dummies-questions-and-answers/22699-execv-vs-execvp.html)

