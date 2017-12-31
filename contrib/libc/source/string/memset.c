#include <string.h>

void *memset(void *dest, int ch, size_t count) {
  const unsigned char _ch = (unsigned char)ch;
  unsigned char *_dest = (unsigned char *)dest;

  while (count--) {
    *_dest++ = _ch;
  }

  return dest;
}
