#include <unistd.h>

char *utoa(unsigned int value, char *s, unsigned char radix) {
  char  buf[sizeof(unsigned int) * CHAR_BIT + 1];
  char *s1 = s;
  char *s2 = buf;

  do {
    *s2++ = "0123456789abcdefghijklmnopqrstuvwxyz"[value % radix];
    value /= radix;
  } while (value > 0);

  *s2 = '\0';

  do {
    *s1++ = *--s2;
  } while (s2 > buf);

  *s1 = '\0';

  return s;
}
