#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main() {
  char *line = NULL;
  size_t len = 0;
  char *inputs[5];

  while (1) {
    printf("Enter text: ");
    if (getline(&line, &len, stdin) == -1) {
      exit(1);
      /*
      how about:
      perror("getline failed\n");
      exit(EXIT_FAILURE);
      */
    }

    if (inputs[4] != NULL) {
      for (int i = 0; i < 4; i++) {
        inputs[i + 1] = inputs[i];
        inputs[4] = line;
      }
    } else {
      for (int i = 0; i < 5; i++) {
        if (inputs[i] == NULL) {
          inputs[i] = line;
          break;
        }
      }
    }

    if (strcmp(line, "print") == 0) {
      for (int i = 0; i < 5; i++) {
        if (inputs[i] != NULL) {
          printf("%s\n", inputs[i]);
        }
      }
    }
  }
  free(line);
  return 0;
}
