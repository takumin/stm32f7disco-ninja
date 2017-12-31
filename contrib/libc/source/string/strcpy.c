#include <string.h>

#if (__STDC_VERSION__ >= 199901L)
#define PTR_RESTRICT *restrict
#else
#define PTR_RESTRICT *
#endif

char *strcpy(char PTR_RESTRICT dest, const char PTR_RESTRICT src) {
  char *save = (char *)dest;

  while ((*dest++ = *src++)) {
  }

  return save;
}
