#include <stdio.h>

#if (__STDC_VERSION__ >= 199901L)
#define PTR_RESTRICT *restrict
#else
#define PTR_RESTRICT *
#endif

int sprintf(char PTR_RESTRICT buffer, const char PTR_RESTRICT format, ...) {
  int     len;
  va_list ap;
  va_start(ap, format);
  len = vsprintf(ap, buffer, format);
  va_end(ap);
  return len;
}
