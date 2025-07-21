#include <stdio.h>
#include <stdlib.h>

#define MAX_NUM 100

int cmp(const void* a, const void* b) {
   return (*(int*)b - *(int*)a);
}

int main(void) {
  unsigned long n;
  scanf("%lu", &n);

  unsigned long* frequencies = (unsigned long*)calloc(MAX_NUM, sizeof(unsigned long));
  unsigned long max_frequency = 0;

  for (unsigned long _ = 0; _ < n; _++) {
    unsigned char i;
    scanf("%hhu", &i);

    frequencies[i]++;
    if (max_frequency < frequencies[i])
      max_frequency = frequencies[i];
  }

  unsigned char* modes = (unsigned char*)calloc(1, sizeof(unsigned char));
  unsigned char len = 0;
  unsigned char cap = 1;

  for (unsigned char i = 0; i < MAX_NUM; i++) {
    if (frequencies[i] != max_frequency)
      continue;

    if (len == cap) {
      cap *= 2;
      modes = (unsigned char*)reallocarray(modes, cap, sizeof(unsigned char));
    }
    modes[len++] = i;
  }
  free(frequencies);

  qsort(modes, len, sizeof(unsigned char), cmp);
  for (unsigned char i = 0; i < len; i++)
    printf("%hhu ", modes[i]);
  free(modes);

  return 0;
}
