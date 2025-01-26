#define IKEV2_H
#ifdef IKEV2_H

#include <stdint.h>

// length is 28 bytes

typedef struct {
  uint64_t initSPI;
  uint64_t respSPI;
  uint8_t nextType;
  uint8_t exchangeType;
  uint32_t msgID;
  uint32_t length;
} IKEHeader;

typedef struct {
  IKEHeader header;
  int hi;
} IKEPacket;

int IKEParseHeader(unsigned char *packet, IKEHeader *header);

int IKEParsePacket(unsigned char *packet, IKEPacket *ike);

#endif // IKEV2_H
