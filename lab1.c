#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main() {
  char *line = NULL;
  size_t len = 0;

  printf("Enter text: ");

  if (getline(&line, &len, stdin) != -1) {
    char *ptr = NULL;
    char *token = strtok_r(line, " ", &ptr);

    printf("Tokens:\n");

    while (token != NULL) {
      printf("%s\n", token);
      token = strtok_r(NULL, " ", &ptr);
    }
  } else {
    perror("getline failed\n");
    exit(EXIT_FAILURE);
  }

  free(line);
  return 0;
}

// str = getline(lineptr, size, stream);
// printf(strtok_r(str, " ", ptr));
// char *token = " ";
// while (token != NULL) {
// token = strtok_r(NULL, " ", ptr));
// printf(*token);
// }
