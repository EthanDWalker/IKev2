#define INT_H
#ifdef INT_H
#include <stdio.h>
#include <stdint.h>

uint64_t Int64Parse(unsigned char *buffer);

uint32_t Int32Parse(unsigned char *buffer);

uint16_t Int16Parse(unsigned char *buffer);

void IntToBuffer(void *n, size_t size, unsigned char *buffer);

#endif // INT_H
