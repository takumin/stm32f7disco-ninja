#include <stdio.h>

#if (__STDC_VERSION__ >= 201112L)
int snprintf(char *restrict buffer, size_t bufsz, const char *restrict format, ...) {
  int     len;
  va_list ap;
  va_start(ap, format);
  len = vsnprintf(ap, buffer, bufsz, format);
  va_end(ap);
  return len;
}
#endif
