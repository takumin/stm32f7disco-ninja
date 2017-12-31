#ifndef STRING_H
#define STRING_H

#include <stddef.h>

extern int memcmp(const void *lhs, const void *rhs, size_t count);

#if (__STDC_VERSION__ >= 199901L)
extern void *memcpy(void *restrict dest, const void *restrict src, size_t count);
#else
extern void *memcpy(void *dest, const void *src, size_t count);
#endif

extern void *memset(void *dest, int ch, size_t count);

#if (__STDC_VERSION__ >= 199901L)
extern char *strcpy(char *restrict dest, const char *restrict src);
#else
extern char *strcpy(char *dest, const char *src);
#endif

extern size_t strlen(const char *str);

extern char *strchr(const char *str, int ch);

#endif
