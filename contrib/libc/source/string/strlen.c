#include <string.h>

size_t strlen(const char* str) {
  const char* ptr = str;

  while (*ptr++ != '\0') {
  }

  return (size_t)(ptr - str);
}
