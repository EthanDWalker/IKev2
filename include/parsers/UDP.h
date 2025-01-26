#define UDP_H
#ifdef UDP_H

#include <stdint.h>

typedef struct {
  uint16_t sourcePort;  
  uint16_t destPort;  
  uint16_t packetLength;  
  uint16_t checksum;
} UDPHeader;

int UDPParse(unsigned char *packet, UDPHeader *header);

#endif // UDP_H
