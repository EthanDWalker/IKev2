#define IPV4_H
#ifdef IPV4_H

#include <stdint.h>
#include <stdbool.h>

typedef struct {
  uint8_t headerLength;
  uint16_t packetLength;
  uint8_t protocol;
  uint8_t sourceIP[4];
  uint8_t destIP[4];
} IPv4Header;

bool IsV4(unsigned char *packet);

int V4Parse(unsigned char *packet, IPv4Header *header);

#endif // IPV4_H
