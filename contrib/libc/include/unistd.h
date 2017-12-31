#ifndef UNISTD_H
#define UNISTD_H

#include <limits.h>
#include <stddef.h>

extern char *itoa(int value, char *s, unsigned char radix);
extern char *utoa(unsigned int value, char *s, unsigned char radix);

#endif
