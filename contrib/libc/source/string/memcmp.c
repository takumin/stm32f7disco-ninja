#include <string.h>

int memcmp(const void* lhs, const void* rhs, size_t count) {
  const unsigned char* _lhs = (const unsigned char*)lhs;
  const unsigned char* _rhs = (const unsigned char*)rhs;

  while (count--) {
    if (*_lhs != *_rhs) {
      return *_lhs - *_rhs;
    }
    ++_lhs;
    ++_rhs;
  }

  return 0;
}
