#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NAME_LEN 20 + 1
#define LOAD_FACTOR_THRESHOLD 0.7

typedef struct {
  char *str;
  long dup;
} name_t;

typedef struct {
  name_t *names;
  unsigned long cap;
  unsigned long size;
} hash_t;

unsigned long hash(char *str, const unsigned long cap,
                   const unsigned long dup) {
  unsigned long hash_val = 5381;
  int c;
  while ((c = *str++))
    hash_val = ((hash_val << 5) + hash_val) + c;
  return (hash_val + dup) % cap;
}

unsigned long next_power_of_two(unsigned long num) {
  if (num == 0)
    return 1;
  num--;
  num |= num >> 1;
  num |= num >> 2;
  num |= num >> 4;
  num |= num >> 8;
  num |= num >> 16;
  num |= num >> 32;
  return num + 1;
}

hash_t *new(const unsigned long cap) {
  hash_t *l = (hash_t *)malloc(sizeof(hash_t));
  l->cap = cap;
  l->size = 0;
  l->names = (name_t *)malloc(sizeof(name_t) * cap);
  for (unsigned long i = 0; i < cap; ++i) {
    l->names[i].str = NULL;
    l->names[i].dup = -1;
  }
  return l;
}

long find(hash_t *l, char *name, const unsigned long dup) {
  unsigned long n = next_power_of_two(l->cap) - 1;

  unsigned long idx = hash(name, l->cap, dup);
  unsigned long start_idx = idx;
  if (l->names[idx].str != NULL) {
    if (l->names[idx].dup == dup && strcmp(l->names[idx].str, name) == 0)
      return idx;
    for (unsigned long i = 1; i < n; i++) {
      idx = (start_idx + (i * i + i) / 2) & n;
      if (idx >= l->cap)
        continue;
      if (l->names[idx].str == NULL)
        break;
      if (l->names[idx].dup == dup && strcmp(l->names[idx].str, name) == 0)
        return idx;
    }
  }
  return -1;
}

unsigned long push(hash_t *l, char *name, unsigned long dup);
void resize(hash_t *l) {
  unsigned long new_cap = l->cap * 2;
  hash_t *new_hash = new(new_cap);

  for (unsigned long i = 0; i < l->cap; ++i) {
    if (l->names[i].str != NULL) {
      unsigned long dup = l->names[i].dup;
      char *name = l->names[i].str;
      push(new_hash, name, dup);
    }
  }

  free(l->names);

  l->cap = new_hash->cap;
  l->names = new_hash->names;
  l->size = new_hash->size;
  free(new_hash);
}

unsigned long push(hash_t *l, char *name, unsigned long dup) {
  if (l->size >= LOAD_FACTOR_THRESHOLD * l->cap)
    resize(l);

  unsigned long n = next_power_of_two(l->cap) - 1;

  if (find(l, name, dup) != -1)
    for (dup = 1; dup < l->cap && find(l, name, dup) != -1; dup++)
      ;

  unsigned long idx = hash(name, l->cap, dup);
  unsigned long start_idx = idx;
  if (l->names[idx].str != NULL &&
      (l->names[idx].dup != dup || strcmp(l->names[idx].str, name) != 0)) {
    for (unsigned long i = 1; i < n; i++) {
      idx = (start_idx + (i * i + i) / 2) & n;
      if (idx >= l->cap)
        continue;
      if (l->names[idx].str == NULL)
        break;
    }
  }

  l->names[idx].str = (char *)malloc(sizeof(char) * NAME_LEN);
  strcpy(l->names[idx].str, name);
  l->names[idx].dup = dup;
  l->size++;
  return dup;
}

unsigned long trim(char *str) {
  int len = strlen(str);
  int num, power, i;
  for (num = 0, power = 1, i = len - 1; i >= 0 && isdigit(str[i]);
       num = (str[i] - '0') * power + num, power *= 10, i--)
    ;
  str[i + 1] = '\0';
  return num;
}

int main(void) {
  unsigned long n;
  scanf("%lu", &n);

  hash_t *l = new (n);
  for (unsigned long _ = 0; _ < n; _++) {
    char name[NAME_LEN];
    scanf("%s", name);

    const unsigned long c = trim(name);
    const unsigned long d = push(l, name, c);
    if (c == d)
      printf("OK\n");
    else if (d == 0)
      printf("Change to %s\n", name);
    else
      printf("Change to %s%ld\n", name, d);
  }
  return 0;
}
