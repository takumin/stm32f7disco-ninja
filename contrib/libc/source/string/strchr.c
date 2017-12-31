#include <string.h>

char *strchr(const char *str, int ch) {
  char *res;
  while (*str && *str != ch) {
    str++;
  }
  res = &(*((char *)&str));
  if (*str == ch) {
    return res;
  }
  return NULL;
}
