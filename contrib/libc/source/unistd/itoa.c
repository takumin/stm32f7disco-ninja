#include <unistd.h>

char *itoa(int value, char *s, unsigned char radix) {
  unsigned int t  = (unsigned int)value;
  char *       ss = s;

  if (value < 0 && radix == 10) {
    *ss++ = '-';
    t     = -t;
  }

  utoa(t, ss, radix);

  return s;
}
