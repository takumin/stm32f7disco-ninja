#include <string.h>

#if (__STDC_VERSION__ >= 199901L)
#define PTR_RESTRICT *restrict
#else
#define PTR_RESTRICT *
#endif

void *memcpy(void PTR_RESTRICT dest, const void PTR_RESTRICT src, size_t count) {
  unsigned char PTR_RESTRICT _dest      = (unsigned char PTR_RESTRICT)dest;
  const unsigned char PTR_RESTRICT _src = (const unsigned char PTR_RESTRICT)src;

  while (count--) {
    *_dest++ = *_src++;
  }

  return dest;
}
