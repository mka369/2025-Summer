#define _POSIX_C_SOURCE 200809L
#include <errno.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
  while (true) {
    printf("Enter programs to run.\n> ");

    char *line = NULL;
    size_t len = 0;

    if (getline(&line, &len, stdin) == -1) {
      printf("getline failed\n");
      exit(EXIT_FAILURE);
    }

    else {
      line[len - 1] = '\0';

      pid_t pid = fork();
      if (pid == 0) {
        // Child process
        if (execl(line, line, NULL) == -1) {
          printf("exec failed. errno: %d\n", errno);
        }
      }

      else {
        // Parent process
        if (waitpid(pid, NULL, 0) == -1) {
          printf("wait failed\n");
        }
      }
    }
  }

  return 0;
}
