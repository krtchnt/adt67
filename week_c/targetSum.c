#include <stdio.h>
#include <stdlib.h>

void get_triplets(long *arr, const unsigned long n, const unsigned long p);

int main(void) {
  unsigned long n, p;
  scanf("%lu %lu", &n, &p);

  long *arr = (long *)malloc(n * sizeof(long));
  for (unsigned long i = 0; i < n; ++i)
    scanf("%ld", arr + i);
  get_triplets(arr, n, p);

  return 0;
}

void merge(long *arr, const unsigned long l, const unsigned long m,
           const unsigned long r) {
  unsigned long i, j, k;
  const unsigned long n1 = m - l + 1;
  const unsigned long n2 = r - m;

  long *L = (long *)malloc(n1 * sizeof(long));
  long *R = (long *)malloc(n2 * sizeof(long));

  for (i = 0; i < n1; i++)
    L[i] = arr[l + i];
  for (j = 0; j < n2; j++)
    R[j] = arr[m + 1 + j];

  i = 0;
  j = 0;
  k = l;
  while (i < n1 && j < n2) {
    if (L[i] <= R[j]) {
      arr[k] = L[i];
      i++;
    } else {
      arr[k] = R[j];
      j++;
    }
    k++;
  }

  while (i < n1) {
    arr[k] = L[i];
    i++;
    k++;
  }

  while (j < n2) {
    arr[k] = R[j];
    j++;
    k++;
  }
}

void merge_sort(long *arr, const unsigned long l, const unsigned long r) {
  if (l >= r)
    return;
  const unsigned long m = l + (r - l) / 2;

  merge_sort(arr, l, m);
  merge_sort(arr, m + 1, r);

  merge(arr, l, m, r);
}

void get_triplets(long *arr, const unsigned long n, const unsigned long p) {
  merge_sort(arr, 0, n - 1);
  for (unsigned long i = 0; i < n - 2; ++i) {
    if (i > 0 && arr[i] == arr[i - 1])
      continue;
    unsigned long l = i + 1;
    unsigned long r = n - 1;
  
    while (l < r) {
      const long sum = arr[i] + arr[l] + arr[r];
  
      if (sum == (long)p) {
        printf("%ld %ld %ld\n", arr[i], arr[l], arr[r]);
  
        while (l < r && arr[l] == arr[l + 1])
          l++;
        while (l < r && arr[r] == arr[r - 1])
          r--;
  
        l++;
        r--;
      } else if (sum < (long)p)
        l++;
      else
        r--;
    }
  }
}


