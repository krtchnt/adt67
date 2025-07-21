#include <stdio.h>
#include <string.h>

char buffer[15 + 1];
const char* to_roman(const unsigned short arabic);

int main(void) {
  unsigned char n;
  scanf("%hhu", &n);

  for (int i = 0; i < n; i++) {
    unsigned short arabic;
    scanf("%hu", &arabic);

    to_roman(arabic);
    printf("%s\n", buffer);
  }
}

void to_roman(const unsigned short arabic) {
  memset(buffer, 0, sizeof(buffer));

  const unsigned char m_q = (unsigned char)(arabic / 1000);
  const unsigned short m_r = (arabic % 1000);

  const unsigned char d_q = (unsigned char)(m_r / 500);
  const unsigned short d_r = (m_r % 500);

  const unsigned char c_q = (d_r / 100);
  const unsigned char c_r = (d_r % 100);

  const unsigned char l_q = (c_r / 50);
  const unsigned char l_r = (c_r % 50);

  const unsigned char x_q = (l_r / 10);
  const unsigned char x_r = (l_r % 10);

  const unsigned char v_q = (x_r / 5);

  const unsigned char i_q = (x_r % 5);

  unsigned char i = 0;
  for (unsigned char _ = 0; _ < m_q; _++)
    buffer[i++] = 'M';

  if (c_q == 4) {
    if (d_q) {
      buffer[i++] = 'C';
      buffer[i++] = 'M';
    } else {
      buffer[i++] = 'C';
      buffer[i++] = 'D';
    }
  } else {
    if (d_q)
      buffer[i++] = 'D';
    for (unsigned char _ = 0; _ < c_q; _++)
      buffer[i++] = 'C';
  }

  if (x_q == 4) {
    if (l_q) {
      buffer[i++] = 'X';
      buffer[i++] = 'C';
    } else {
      buffer[i++] = 'X';
      buffer[i++] = 'L';
    }
  } else {
    if (l_q)
      buffer[i++] = 'L';
    for (unsigned char _ = 0; _ < x_q; _++)
      buffer[i++] = 'X';
  }

  if (i_q == 4) {
    if (v_q) {
      buffer[i++] = 'I';
      buffer[i++] = 'X';
    } else {
      buffer[i++] = 'I';
      buffer[i++] = 'V';
    }
  } else {
    if (v_q)
      buffer[i++] = 'V';
    for (unsigned char _ = 0; _ < i_q; _++)
      buffer[i++] = 'I';
  }
}
