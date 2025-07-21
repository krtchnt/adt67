#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define WORD_LEN 50 + 1
#define ALPHABETS 26

void get_freq(const char *str, unsigned long freq[ALPHABETS]) {
  for (unsigned char i = 0; i < ALPHABETS; ++i)
    freq[i] = 0;
  for (unsigned char i = 0; str[i] != '\0'; ++i)
    if (str[i] >= 'a' && str[i] <= 'z')
      ++freq[str[i] - 'a'];
}

bool array_eq(const unsigned long arr1[ALPHABETS],
              const unsigned long arr2[ALPHABETS]) {
  for (unsigned char i = 0; i < ALPHABETS; ++i)
    if (arr1[i] != arr2[i])
      return false;
  return true;
}

int main(void) {
  unsigned long m, n;
  scanf("%lu %lu", &m, &n);

  char **words = (char **)malloc(m * sizeof(char *));
  unsigned long **freqs = (unsigned long **)calloc(m, sizeof(unsigned long *));
  for (unsigned long i = 0; i < m; ++i) {
    words[i] = (char *)malloc(WORD_LEN * sizeof(char));
    scanf("%s", words[i]);
  }

  for (unsigned long _ = 0; _ < n; ++_) {
    char word[WORD_LEN];
    unsigned long freq[ALPHABETS];
    scanf("%s", word);
    get_freq(word, freq);

    for (unsigned long i = 0; i < m; ++i) {
      if (freqs[i] == NULL) {
        freqs[i] = (unsigned long *)malloc(ALPHABETS * sizeof(unsigned long));
        get_freq(words[i], freqs[i]);
      }
      if (array_eq(freq, freqs[i]))
        printf("%s ", words[i]);
    }
    putchar('\n');
  }
  return 0;
}
