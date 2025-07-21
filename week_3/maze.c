#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

unsigned char n, s_i, s_j, g_i, g_j;
char **maze;
bool **seen, **soln;

bool traverseMaze(const unsigned char i, const unsigned char j) {
  if (i == g_i && j == g_j) return true;
  if (maze[i][j] == '#' || seen[i][j]) return false;
  seen[i][j] = true;
    if (i != 0     && traverseMaze(i - 1, j    )) { soln[i][j] = true; return true; }
    if (i != n - 1 && traverseMaze(i + 1, j    )) { soln[i][j] = true; return true; }
    if (j != 0     && traverseMaze(i    , j - 1)) { soln[i][j] = true; return true; }
    if (j != n - 1 && traverseMaze(i    , j + 1)) { soln[i][j] = true; return true; }
    return false;
}

int main(void) {
  scanf("%hhu", &n); getchar();

  maze = (char **)calloc(n, sizeof(char *));
  seen = (bool **)calloc(n, sizeof(bool *));
  soln = (bool **)calloc(n, sizeof(bool *));
  for (unsigned char i = 0; i < n; i++) {
    maze[i] = (char *)calloc(n, sizeof(char));
    seen[i] = (bool *)calloc(n, sizeof(bool));
    soln[i] = (bool *)calloc(n, sizeof(bool));

    for (unsigned char j = 0; j < n; j++) {
      char c; switch (c = getchar()) {
        case 'S': s_i = i; s_j = j; break;
        case 'G': g_i = i; g_j = j; break;
      }
      maze[i][j] = c;
    } getchar();
  }

  traverseMaze(s_i, s_j);

  for (unsigned char i = 0; i < n; i++) {
    for (unsigned char j = 0; j < n; j++) {
      const char c = maze[i][j];
      putchar((c == ' ' && soln[i][j]) ? '.' : c);
    } putchar('\n');
  }

  for (unsigned char i = 0; i < n; i++) {
    free(maze[i]); free(seen[i]); free(soln[i]);
  } free(maze)   ; free(seen)   ; free(soln)   ;
  return 0;
}
