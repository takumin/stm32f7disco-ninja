#include <stdio.h>
#include <string.h>
#include <unistd.h>

#if (__STDC_VERSION__ >= 199901L)
#define PTR_RESTRICT *restrict
#else
#define PTR_RESTRICT *
#endif

int vsprintf(va_list ap, char PTR_RESTRICT buffer, const char PTR_RESTRICT format, ...) {
  int          len = 0;
  char*        str;
  size_t       pos;
  signed int   sign;
  unsigned int unsign;

  while (*format) {
    if (*format == '%') {
      format++;
      str    = NULL;
      pos    = 0;
      sign   = 0;
      unsign = 0;

      switch (*format) {
        case 'd':
          sign = va_arg(ap, signed int);
          itoa(sign, buffer, 10);
          pos = strlen(buffer) - 1;
          buffer += pos;
          len += pos;
          format++;
          break;

        case 'u':
          unsign = va_arg(ap, unsigned int);
          utoa(unsign, buffer, 10);
          pos = strlen(buffer) - 1;
          buffer += pos;
          len += pos;
          format++;
          break;

        case 's':
          if ((str = va_arg(ap, char*)) == NULL) {
            str = "(null)";
          }
          while (*str) {
            *(buffer++) = *(str++);
            len++;
          }
          format++;
          break;

        case '%':
          *(buffer++) = *(format++);
          len++;
          break;
      }
    } else {
      *(buffer++) = *(format++);
      len++;
    }
  }

  *(buffer++) = 0;
  len++;

  return len;
}
