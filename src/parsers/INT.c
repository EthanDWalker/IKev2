#include "../../include/parsers/INT.h"
#include <stdint.h>

uint64_t Int64Parse(unsigned char *buffer) {
  return (uint64_t)buffer[0] << 56 | (uint64_t)buffer[1] << 48 |
         (uint64_t)buffer[2] << 40 | (uint64_t)buffer[3] << 32 |
         (uint64_t)buffer[4] << 24 | (uint64_t)buffer[5] << 16 |
         (uint64_t)buffer[6] << 8 | buffer[7];
}

uint32_t Int32Parse(unsigned char *buffer) {
  return (uint32_t)buffer[0] << 24 | (uint32_t)buffer[1] << 16 |
         (uint32_t)buffer[2] << 8 | buffer[3];
}

uint16_t Int16Parse(unsigned char *buffer) {
  return (buffer[0] << 8) + buffer[1];
}

void IntToBuffer(void *n, size_t size, unsigned char *buffer) {
  unsigned char *ptr = (unsigned char *)n;
  for (size_t i = 0; i < size; i++) {
    buffer[i] = ptr[i];
  }
}
