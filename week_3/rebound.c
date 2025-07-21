#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

void rebound(
    const unsigned int n,
    const unsigned int m,
    const unsigned int x,
    const unsigned int y,
    unsigned char *dir
);
void traverse(unsigned int *x, unsigned int *y, const unsigned char dir);

int main(void) {
  unsigned int n, m, x, y;
  unsigned char dir;
  scanf("%u %u %u %u %hhu", &n, &m, &x, &y, &dir);

  bool **room = (bool **)calloc(n, sizeof(bool *));
  for (unsigned int i = 0; i < n; i++)
    room[i] = (bool *)calloc(m, sizeof(bool));

  unsigned int traversed = 0, seen_streak = 0;
  while (traversed >= seen_streak) {
    if (room[x][y]) {
      seen_streak++;
    } else {
      traversed++;
      seen_streak = 0;
      room[x][y] = true;
    }

    rebound(n, m, x, y, &dir);
    traverse(&x, &y, dir);
  }
  for (unsigned int i = 0; i < n; i++) free(room[i]);
  free(room);

  printf("%u\n", traversed);
  return 0;
}

void total_reflect(unsigned char *dir) { *dir = (*dir + 4) % 8; }

void rebound(
    const unsigned int n,
    const unsigned int m,
    const unsigned int x,
    const unsigned int y,
    unsigned char *dir
) {
  if      (x == 0     && y == 0    ) switch (*dir) { case 6: case 7: case 0: total_reflect(dir); break; }
  else if (x == 0     && y == m - 1) switch (*dir) { case 0: case 1: case 2: total_reflect(dir); break; }
  else if (x == n - 1 && y == m - 1) switch (*dir) { case 2: case 3: case 4: total_reflect(dir); break; }
  else if (x == n - 1 && y == 0    ) switch (*dir) { case 4: case 5: case 6: total_reflect(dir); break; }
  else if (x == 0 && 0 < y && y < m - 1)
    switch (*dir) {
      case 7: *dir = 5; break;
      case 0: *dir = 4; break;
      case 1: *dir = 3; break;
    }
  else if (0 < x && x < n - 1 && y == m - 1)
    switch (*dir) {
      case 1: *dir = 7; break;
      case 2: *dir = 6; break;
      case 3: *dir = 5; break;
    }
  else if (x == n - 1 && 0 < y && y < m - 1)
    switch (*dir) {
      case 3: *dir = 1; break;
      case 4: *dir = 0; break;
      case 5: *dir = 7; break;
    }
  else if (0 < x && x < n - 1 && y == 0)
    switch (*dir) {
      case 5: *dir = 3; break;
      case 6: *dir = 2; break;
      case 7: *dir = 1; break;
    }
}

void traverse(unsigned int *x, unsigned int *y, const unsigned char dir) {
  switch (dir) {
    case 7: case 0: case 1: (*x)--; break;
    case 3: case 4: case 5: (*x)++; break;
  }

  switch (dir) {
    case 1: case 2: case 3: (*y)++; break;
    case 5: case 6: case 7: (*y)--; break;
  }
}
