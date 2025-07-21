#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
  unsigned long m, p, n;
  scanf("%lu %lu %lu", &m, &p, &n);

  char *str = (char *)calloc(m + 1, sizeof(char));
  scanf("%s", str);

  char *substr = (char *)calloc(p + 1, sizeof(char));
  scanf("%s", substr);

  char *curr_substr = (char *)calloc(p + 1, sizeof(char));
  char *valid_substrs = (char *)calloc(m + 1, sizeof(char));
  for (unsigned long i = 0; i < m - p + 1; i++) {
    bool valid_substr = true;
    unsigned long n_left = n;
    for (unsigned long j = 0; j < p; j++) {
      const char curr_char = str[i + j];
      char *jth_char = &curr_substr[j];

      if (valid_substrs[i + j] != '\0') {
        valid_substr = false;
        break;
      }
      if (curr_char == substr[j]) {
        *jth_char = curr_char;
      } else {
        if (n_left == 0) {
          valid_substr = false;
          break;
        }
        *jth_char = '?';
        n_left--;
      }
    }

    if (valid_substr) {
      memcpy(valid_substrs + i, curr_substr, p);
    }
  }
  free(substr);
  free(curr_substr);

  for (unsigned long i = 0; i < m;) {
    if (valid_substrs[i] == '\0') {
      putchar(str[i++]);
      continue;
    }

    putchar('[');
    unsigned long j = 0;
    while (j++ < p && i < m) {
      putchar(valid_substrs[i++]);
    }
    putchar(']');
  }
  free(valid_substrs);
  free(str);

  return 0;
}
